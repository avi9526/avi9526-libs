
//    Copyright (C) 2022
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

#ifndef Wait_for_pin_H
#define Wait_for_pin_H

#include <Arduino.h>

class T_Wait_for_pin {
public:
  T_Wait_for_pin(const uint8_t &Input_pin_number, const bool &Invert = false,
                 const bool &Pull_up = false);
  ~T_Wait_for_pin();
  void operator()();

private:
  uint8_t _Input_pin_number;
  bool _Invert;
};

#endif
