
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

#ifndef Chainlink_CPP
#define Chainlink_CPP

#include "chainlink.h"

void
Chain_link::Create(Chain_link& Connect_to)
{
  auto New = new Chain_link;
  New->Connect(Connect_to);
  New->Suicidal(true);
}

Chain_link::Chain_link()
  : _Up()
  , _Down()
  , _Suicidal(false)
{
}

Chain_link::~Chain_link()
{
  Suicidal(false); // Without this double free might happen
  Chain_link::Reset();
}

bool
Chain_link::Valid() const
{
  return (_Suicidal && Uplink().Valid()) ||
         (Uplink().Valid() || Downlink().Valid());
}

void
Chain_link::Reset()
{
  Disconnect();
}

void
Chain_link::Connect(Chain_link& To)
{
  auto Last = Get_last();
  if (To.Downlink().Valid()) {
    To.Downlink().Value()->Uplink(Last);
    Last.Value()->Downlink(To.Downlink());
  }

  To.Downlink(this);
  Uplink(&To);
}

void
Chain_link::Connect_last(Chain_link& To)
{
  auto Last = To.Get_last();
  if (Last.Valid()) {
    Connect(*(Last.Value()));
  }
}

void
Chain_link::Disconnect()
{
  Disconnect_uplink();
  Disconnect_downlink();
}

void
Chain_link::Disconnect_eject()
{
  if (Uplink().Valid() && Downlink().Valid()) {
      Uplink().Value()->Downlink(Downlink().Value());
      Downlink().Value()->Uplink(Uplink().Value());
      Forget_downlink();
      Forget_uplink();
      Suicide_if_abandoned();
  } else {
    Disconnect();
  }
}

void
Chain_link::Disconnect_uplink()
{
  if (Uplink().Valid()) {
    Uplink().Value()->Forget_downlink();
    Uplink().Value()->Suicide_if_abandoned();
    Forget_uplink();
    Suicide_if_abandoned();
  }
}

void
Chain_link::Disconnect_downlink()
{
  if (Downlink().Valid()) {
    Downlink().Value()->Forget_uplink();
    Downlink().Value()->Suicide_if_abandoned();
    Forget_downlink();
    Suicide_if_abandoned();
  }
}

const Chain_link::Link_pointer&
Chain_link::Uplink() const
{
  return _Up;
}

void
Chain_link::Uplink(const Link_pointer& New_uplink)
{
  _Up = New_uplink;
}

void
Chain_link::Forget_uplink()
{
  _Up.Reset();
}

const Chain_link::Link_pointer&
Chain_link::Downlink() const
{
  return _Down;
}

void
Chain_link::Downlink(const Link_pointer& New_downlink)
{
  _Down = New_downlink;
}

void
Chain_link::Forget_downlink()
{
  _Down.Reset();
}

Chain_link::Link_pointer
Chain_link::Get_first()
{
  Link_pointer Last = this;
  while (Last.Value()->Uplink().Valid()) {
    Last = Last.Value()->Uplink();
    if (Last == this) {
      break; // Prevent loop
    }
  }
  return Last;
}

Chain_link::Link_pointer
Chain_link::Get_last()
{
  Link_pointer Last = this;
  while (Last.Value()->Downlink().Valid()) {
    Last = Last.Value()->Downlink();
    if (Last == this) {
      break; // Prevent loop
    }
  }
  return Last;
}

void
Chain_link::Suicidal(const bool& New_suicidal)
{
  _Suicidal = New_suicidal;
}

void
Chain_link::Suicide_if_abandoned()
{
  if (_Suicidal && (!Uplink().Valid())) {
    delete this;
  }
}

#endif
