
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

#ifndef RANGE_CPP
#define RANGE_CPP

#include "range.h"

template <class Value_type>
Range_type<Value_type>::Range_type() : Parent_type(), _Start(), _End() {}

template <class Value_type>
Range_type<Value_type>::Range_type(const Value_weighted &VStart,
                                   const Value_weighted &VEnd)
    : Parent_type(), _Start(VStart), _End(VEnd) {}

template <class Value_type> Range_type<Value_type>::~Range_type() {}

template <class Value_type> bool Range_type<Value_type>::Valid() const {
  return Start() <= End();
}

template <class Value_type> void Range_type<Value_type>::Reset() {
  Start().Reset();
  End().Reset();
}

template <class Value_type>
typename Range_type<Value_type>::Value_weighted
Range_type<Value_type>::Relative_end() const {
  return End() - Start();
}

template <class Value_type>
typename Range_type<Value_type>::Value_weighted
Range_type<Value_type>::Size() const {
  return End() - Start() + 1;
}

template <class Value_type>
void Range_type<Value_type>::End_from_relative_end(
    const Value_weighted &VEnd_relative) {
  End() = Start() + VEnd_relative;
}

template <class Value_type>
void Range_type<Value_type>::End_from_size(const Value_weighted &VSize) {
  End() = Start() + (VSize - 1);
}

template <class Value_type>
void Range_type<Value_type>::Start_from_relative_end(
    const Value_weighted &VEnd_relative) {
  Start() = End() - VEnd_relative;
}

template <class Value_type>
typename Range_type<Value_type>::Value_weighted &
Range_type<Value_type>::Start() {
  return _Start;
}

template <class Value_type>
const typename Range_type<Value_type>::Value_weighted &
Range_type<Value_type>::Start() const {
  return _Start;
}

template <class Value_type>
void Range_type<Value_type>::Start(const Value_weighted &VStart) {
  _Start = VStart;
}

template <class Value_type>
typename Range_type<Value_type>::Value_weighted &Range_type<Value_type>::End() {
  return _End;
}

template <class Value_type>
const typename Range_type<Value_type>::Value_weighted &
Range_type<Value_type>::End() const {
  return _End;
}

template <class Value_type>
void Range_type<Value_type>::End(const Value_weighted &VEnd) {
  _End = VEnd;
}

template <class Value_type>
bool Range_type<Value_type>::Does_contain(const Value_weighted &V) const {
  return (Start() <= V) && (V <= End());
}

template <class Value_type>
bool Range_type<Value_type>::Does_contain(const Range_type &V) const {
  return Does_contain(V.Start()) && Does_contain(V.End());
}

template <class Value_type>
Range_type<Value_type> &
Range_type<Value_type>::operator()(const Value_weighted &VStart,
                                   const Value_weighted &VEnd) {
  Start() = VStart;
  End() = VEnd;
  return *this;
}

template <class Value_type>
Range_type<Value_type> operator&(const Range_type<Value_type> &V1,
                                 const Range_type<Value_type> &V2) {
  Range_type<Value_type> Result;
  Result.Start() = Biggest(V1.Start(), V2.Start());
  Result.End() = Smallest(V1.End(), V2.End());
  return Result;
}

template <class Value_type>
bool operator==(const Range_type<Value_type> &V1,
                const Range_type<Value_type> &V2) {
  return (V1.Start() == V2.Start()) && (V1.End() == V2.End());
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator+(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2) {
  return Range_type<Value_type>(V1.Start() + V2.Start(), V1.End() + V2.End());
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator+(Range_type<Value_type> V1, Numeric_type V2) {
  return Range_type<Value_type>(V1.Start() + V2, V1.End() + V2);
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> &operator+=(Range_type<Value_type> &V1,
                                   const Numeric_type &V2) {
  V1.Start() += V2;
  V1.End() += V2;
  return V1;
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator-(const Range_type<Value_type> &V1,
                                 const Range_type<Value_type> &V2) {
  return Range_type<Value_type>(V1.Start() - V2.Start(), V1.End() - V2.End());
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator-(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2) {
  return Range_type<Value_type>(V1.Start() - V2, V1.End() - V2);
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> &operator-=(Range_type<Value_type> &V1,
                                   const Numeric_type &V2) {
  V1.Start() -= V2;
  V1.End() -= V2;
  return V1;
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator*(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2) {
  return Range_type<Value_type>(V1.Start() * V2, V1.End() * V2 + (V2 - 1));
}

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator/(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2) {
  return Range_type<Value_type>(V1.Start() / V2, (V1.End() - (V2 - 1)) / V2);
}

template <class Value_type, class AnotherValue_type>
Range_type<Value_type> operator>>(const Range_type<Value_type> &V1,
                                  const Range_type<AnotherValue_type> &V2) {
  return Range_type<Value_type>(V1.Start() + V2.Start(), V1.End() + V2.Start());
}

template <class Value_type, class AnotherValue_type>
Range_type<Value_type> operator<<(const Range_type<Value_type> &V1,
                                  const Range_type<AnotherValue_type> &V2) {
  return Range_type<Value_type>(V1.Start() - V2.Start(), V1.End() - V2.Start());
}

#endif
