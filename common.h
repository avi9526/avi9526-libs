
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

#ifndef COMMON_H
#define COMMON_H
// #include <QDebug>
// #include <algorithm>
// #include <cassert>
// #include <cstdarg>
// #include <cstddef>
#include <cstdint>
// #include <iostream>
// #include <limits>
#include <math.h>
// #include <numeric>
// #include <type_traits>
// #include <typeinfo>
#include "std_parts.h"
//#include <Arduino.h>
#include <new>

template <class Numeric_type> Numeric_type GCD(Numeric_type A, Numeric_type B) {
  while (B != 0) {
    auto C = A;
    A = B;
    B = C % B;
  }
  return A;
}

template <class Numeric_type> Numeric_type Biggest(Numeric_type A, Numeric_type B) {
  if (A > B) {
    return A;
  } else {
    return B;
  }
}

template <class Numeric_type>
Numeric_type Smallest(Numeric_type A, Numeric_type B) {
  if (A < B) {
    return A;
  } else {
    return B;
  }
}

#endif // COMMON_H
