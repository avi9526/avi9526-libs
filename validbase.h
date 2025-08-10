
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

#ifndef VALIDBASE_H
#define VALIDBASE_H

#include "common.h"

class Valid_base
{
protected:
  Valid_base(){};

public:
  virtual ~Valid_base() = 0;

  virtual bool Valid() const = 0;
  virtual void Reset() = 0;
};

inline Valid_base::~Valid_base() {}

#endif
