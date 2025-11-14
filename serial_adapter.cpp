//    Copyright (C) 2025
//    Andrew V. Dromaretsky <dromaretsky@gmail.com> aka avi9526

//    This program is free software: you can redistribute it and/or modify it
//    under the terms of the GNU Lesser General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or (at your
//    option) any later version.

//    This program is distributed in the hope that it will be useful, but
//    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
//    or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
//    License for more details.

//    You should have received a copy of the GNU Lesser General Public License
//    along with this program. If not, see <https://www.gnu.org/licenses/>.

#ifndef Serial_adapter_type_CPP
#define Serial_adapter_type_CPP

#include "serial_adapter.h"

Serial_adapter_type::Serial_adapter_type()
  : Valid_base()
  , _Port_name()
  , _File_descriptor()
{
}

Serial_adapter_type::Serial_adapter_type(const string& Port)
  : Valid_base()
  , _Port_name(Port)
  , _Locked(false)
  , _File_descriptor()
{
  Serial_adapter_type::Open();
}

Serial_adapter_type::~Serial_adapter_type()
{
  Serial_adapter_type::Reset();
}

bool
Serial_adapter_type::Valid() const
{
  return (_File_descriptor.Valid() && _Locked && _Terminal_accessible);
}
void
Serial_adapter_type::Reset()
{
  Serial_adapter_type::Close();
}

void
Serial_adapter_type::_Check()
{
  if (_File_descriptor.Valid()) {
    if (fcntl(_File_descriptor.Value(), F_GETFD) != -1) {
      _File_descriptor.Reset();
    }
  } else {
    _Locked = false;
    _Terminal_accessible = false;
  }
}

void
Serial_adapter_type::_Configure()
{
  if (_File_descriptor.Valid() && _Locked) {
    termios Serial_terminal;
    _Terminal_accessible =
      tcgetattr(_File_descriptor.Value(), &Serial_terminal) == 0;

    if (_Terminal_accessible) {
      cfsetospeed(&Serial_terminal, B115200);
      cfsetispeed(&Serial_terminal, B115200);

      Serial_terminal.c_cflag |=
        (CLOCAL | CREAD); // enable receiver, local mode
      Serial_terminal.c_cflag &= ~CSIZE;
      Serial_terminal.c_cflag |= CS8;      // 8 data bits
      Serial_terminal.c_cflag &= ~PARENB;  // no parity
      Serial_terminal.c_cflag &= ~CSTOPB;  // 1 stop bit
      Serial_terminal.c_cflag &= ~CRTSCTS; // no flow control

      Serial_terminal.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // raw mode
      Serial_terminal.c_iflag &=
        ~(IXON | IXOFF | IXANY);         // no software flow control
      Serial_terminal.c_oflag &= ~OPOST; // raw output

      _Terminal_accessible =
        tcsetattr(_File_descriptor.Value(), TCSANOW, &Serial_terminal) == 0;
    }
  }
}

void
Serial_adapter_type::_Lock()
{
  if (_File_descriptor.Valid() && !_Locked) {
    flock File_lock;
    File_lock.l_type = F_WRLCK;
    File_lock.l_whence = SEEK_SET;
    File_lock.l_start = 0;
    File_lock.l_len = 0;
    _Locked = fcntl(_File_descriptor.Value(), F_SETLK, &File_lock) != -1;
  }
}

void
Serial_adapter_type::_Unlock()
{
  if (_File_descriptor.Valid() && _Locked) {
    flock File_lock;
    File_lock.l_type = F_UNLCK;
    File_lock.l_whence = SEEK_SET;
    File_lock.l_start = 0;
    File_lock.l_len = 0;
    _Locked = false;
  }
}

void
Serial_adapter_type::Open()
{
  Serial_adapter_type::_Check();
  auto Result = Serial_adapter_type::Valid();
  if (Result) {
    Serial_adapter_type::Reset();
  } else {
    auto New_port = open(_Port_name.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK);
    _File_descriptor(New_port != -1, New_port);
    Result = _File_descriptor.Valid();
    Serial_adapter_type::_Lock();
    Result = Result && _Locked;
    Serial_adapter_type::Flush();
    Serial_adapter_type::_Configure();
    Result = Result && _Terminal_accessible;
    if (!Result) {
      Serial_adapter_type::Reset();
    }
  }
}

void
Serial_adapter_type::Open(const string& New_port)
{
  Serial_adapter_type::Port(New_port);
  Serial_adapter_type::Open();
}

void
Serial_adapter_type::Close()
{
  Serial_adapter_type::_Check();
  if (_File_descriptor.Valid()) {
    _Terminal_accessible = false;
    if (_Locked) {
      Serial_adapter_type::_Unlock();
    }
    close(_File_descriptor.Value());
    _File_descriptor.Reset();
  }
}

const Serial_adapter_type::File_descriptor_type
Serial_adapter_type::File_descriptor() const
{
  return _File_descriptor;
}

const string
Serial_adapter_type::Port() const
{
  return _Port_name;
}

void
Serial_adapter_type::Port(const string& New_port)
{
  _Port_name = New_port;
}

void
Serial_adapter_type::Flush()
{
  if (Serial_adapter_type::Valid() && _Locked) {
    tcflush(_File_descriptor, TCIOFLUSH);
  }
}

#endif
