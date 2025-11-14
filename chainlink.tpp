
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

#ifndef Chainlink_TPP
#define Chainlink_TPP

#ifndef Chainlink_H
#include "chainlink.h"
#endif

template<class Functor>
void
Chain_link::For_each(Functor F)
{
  Link_pointer First = Get_first();
  auto Current = First;
  while (Current.Valid()) {
    F(Current.Value());
    Current = Current.Value()->Downlink();
    if (Current == First) {
      break; // Prevent loop
    }
  }
}

template<class Functor>
void
Chain_link::For_each_down(Functor F)
{
  Link_pointer Current = Downlink();
  while (Current.Valid()) {
    if (Current.Value() == this) {
      break; // Prevent loop
    }
    F(Current.Value());
    Current = Current.Value()->Downlink();
  }
}

template<class Child_class>
Weighted_type<Child_class*, bool>
Chain_link::As_child_of_class(const Link_pointer& Link)
{
  Weighted_type<Child_class*, bool> Result;
  if (Link.Valid()) {
    auto Child = dynamic_cast<Child_class*>(Link.Value());
    if (Child) {
      Result = Child;
    }
  }
  return Result;
}

template<class Child_class>
Weighted_type<Child_class*, bool>
Chain_link::As_child_of_class()
{
  return As_child_of_class<Child_class>(Link_pointer(this));
}

#endif
