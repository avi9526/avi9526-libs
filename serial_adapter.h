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

#ifndef Serial_adapter_type_H
#define Serial_adapter_type_H

#include "weighted.h"
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

using namespace std;

class Serial_adapter_type : public Valid_base
{
public:
  using Base_class = Valid_base;
  using File_descriptor_type = Weighted_type<int, bool>;

  Serial_adapter_type();
  Serial_adapter_type(const string& Port);
  virtual ~Serial_adapter_type();

  virtual bool Valid() const override;
  virtual void Reset() override;

  virtual void Open();
  virtual void Open(const string& New_port);
  virtual void Close();

  virtual const File_descriptor_type File_descriptor() const;

  virtual const string Port() const;
  virtual void Port(const string& New_port);

  virtual void Flush();

protected:
  virtual void _Lock();
  virtual void _Unlock();
  virtual void _Check();
  virtual void _Configure();

private:
  string _Port_name;
  bool _Locked;
  bool _Terminal_accessible;
  File_descriptor_type _File_descriptor;
};

#endif // Serial_adapter_type_H
