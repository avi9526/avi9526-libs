
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

#ifndef RANGE_H
#define RANGE_H

#include "common.h"
#include "weighted.h"

template <class Value_type> class Range_type : public Valid_base {
public:
  using Value_weighted = Weighted_type<Value_type, bool>;
  using Parent_type = Valid_base;

  Range_type();
  Range_type(const Value_weighted &VStart, const Value_weighted &VEnd);
  ~Range_type();

  virtual bool Valid() const override;
  virtual void Reset() override;

  Value_weighted Relative_end() const;
  Value_weighted Size() const;
  void End_from_relative_end(const Value_weighted &VEnd_relative);
  void End_from_size(const Value_weighted &VSize);
  void Start_from_relative_end(const Value_weighted &VEnd_relative);

  Value_weighted &Start();
  const Value_weighted &Start() const;
  void Start(const Value_weighted &VStart);

  Value_weighted &End();
  const Value_weighted &End() const;
  void End(const Value_weighted &VEnd);

  bool Does_contain(const Value_weighted &V) const;
  bool Does_contain(const Range_type &V) const;

  Range_type<Value_type> &operator()(const Value_weighted &VStart,
                                     const Value_weighted &VEnd);

private:
  Value_weighted _Start;
  Value_weighted _End;
};

template <class Value_type>
Range_type<Value_type> operator&(const Range_type<Value_type> &V1,
                                 const Range_type<Value_type> &V2);

template <class Value_type>
bool operator==(const Range_type<Value_type> &V1,
                const Range_type<Value_type> &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator+(const Range_type<Value_type> &V1,
                                 const Range_type<Value_type> &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator+(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> &operator+=(Range_type<Value_type> &V1,
                                   const Numeric_type &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator-(const Range_type<Value_type> &V1,
                                 const Range_type<Value_type> &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator-(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> &operator-=(Range_type<Value_type> &V1,
                                   const Numeric_type &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator*(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2);

template <class Value_type, class Numeric_type>
Range_type<Value_type> operator/(const Range_type<Value_type> &V1,
                                 const Numeric_type &V2);

template <class Value_type, class AnotherValue_type>
Range_type<Value_type> operator>>(const Range_type<Value_type> &V1,
                                  const Range_type<AnotherValue_type> &V2);

template <class Value_type, class AnotherValue_type>
Range_type<Value_type> operator<<(const Range_type<Value_type> &V1,
                                  const Range_type<AnotherValue_type> &V2);

#include "range.cpp"

#endif
