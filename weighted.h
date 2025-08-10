
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

#ifndef WEIGHTED_H
#define WEIGHTED_H

#include "common.h"
#include "weightedbase.h"

// WeigthType must be bool-compatible
template <class Value_type, class Weight_type>
class Weighted_type : public Weighted_base<Weight_type> {
public:
  using Parent_type = Weighted_base<Weight_type>;

  Weighted_type();

  Weighted_type(const Weighted_type<Value_type, Weight_type> &Val);

  Weighted_type(Value_type Value);
  Weighted_type(Weight_type Weight, Value_type Value);

  ~Weighted_type();

  Value_type &Value();
  const Value_type &Value() const;

  virtual void Reset() override;

  Value_type Value_mult_weight();

  Value_type Value_and_weight();

  void Average_from(Weighted_type<Value_type, Weight_type> W1,
                    Weighted_type<Value_type, Weight_type> W2);

  Weighted_type<Value_type, Weight_type> &
  operator=(const Weighted_type<Value_type, Weight_type> &Val);

  operator Value_type();

  void operator()(Weight_type Weight, Value_type Value);

private:
  Value_type _Value;
};
//------------------------------------------------------------------------------
template <class Value_type, class Weight_type, class Another_type>
bool operator<(const Weighted_type<Value_type, Weight_type> &V1,
               const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type>
bool operator<(const Weighted_type<Value_type, Weight_type> &V1,
               const Value_type &V2);

template <class Value_type, class Weight_type, class Another_type>
bool operator<=(const Weighted_type<Value_type, Weight_type> &V1,
                const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type>
bool operator<=(const Weighted_type<Value_type, Weight_type> &V1,
                const Value_type &V2);

template <class Value_type, class Weight_type, class Another_type>
bool operator==(const Weighted_type<Value_type, Weight_type> &V1,
                const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type>
bool operator==(const Weighted_type<Value_type, Weight_type> &V1,
                const Value_type &V2);

template <class Value_type, class Weight_type, class Another_type>
bool operator!=(const Weighted_type<Value_type, Weight_type> &V1,
                const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type>
bool operator!=(const Weighted_type<Value_type, Weight_type> &V1,
                const Value_type &V2);

template <class Value_type, class Weight_type, class Another_type>
bool operator>(const Weighted_type<Value_type, Weight_type> &V1,
               const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type>
bool operator>(const Weighted_type<Value_type, Weight_type> &V1,
               const Value_type &V2);

template <class Value_type, class Weight_type, class Another_type>
bool operator>=(const Weighted_type<Value_type, Weight_type> &V1,
                const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type>
bool operator>=(const Weighted_type<Value_type, Weight_type> &V1,
                const Value_type &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator+(const Weighted_type<Value_type, Weight_type> &V1,
          const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator+(const Weighted_type<Value_type, Weight_type> &V1,
          const Another_type &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type> &
operator+=(Weighted_type<Value_type, Weight_type> &V1, const Another_type &V2);

template <class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type> &
operator++(Weighted_type<Value_type, Weight_type> &V1);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator-(const Weighted_type<Value_type, Weight_type> &V1,
          const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator-(const Weighted_type<Value_type, Weight_type> &V1,
          const Another_type &V2);

template <class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type> &
operator--(Weighted_type<Value_type, Weight_type> &V1);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type> &
operator-=(Weighted_type<Value_type, Weight_type> &V1, const Another_type &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator*(const Weighted_type<Value_type, Weight_type> &V1,
          const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator*(const Weighted_type<Value_type, Weight_type> &V1, Another_type &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator/(const Weighted_type<Value_type, Weight_type> &V1,
          const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator/(const Weighted_type<Value_type, Weight_type> &V1,
          const Another_type &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator%(const Weighted_type<Value_type, Weight_type> &V1,
          const Weighted_type<Another_type, Weight_type> &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator%(const Weighted_type<Value_type, Weight_type> &V1,
          const Another_type &V2);

template <class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>
operator&&(const Weighted_type<Value_type, Weight_type> &V1,
           const Weighted_type<Value_type, Weight_type> &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator&&(const Weighted_type<Value_type, Weight_type> &V1,
           const Another_type &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator&&(const Another_type &V1,
           const Weighted_type<Value_type, Weight_type> &V2);

template <class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>
operator||(const Weighted_type<Value_type, Weight_type> &V1,
           const Weighted_type<Value_type, Weight_type> &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator||(const Weighted_type<Value_type, Weight_type> &V1,
           const Another_type &V2);

template <class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator||(const Another_type &V1,
           const Weighted_type<Value_type, Weight_type> &V2);

// template<class Value_type, class Weight_type>
// std::ostream&
// operator<<(std::ostream& os, Weighted_type<Value_type, Weight_type>& Val)
// {
//   os << typeid(Val).name() << ": Weight=" <<
//   static_cast<bool>(Val.Weight())
//      << ", Value=" << 10;
//   return os;
// }
//------------------------------------------------------------------------------
// Basic types
//------------------------------------------------------------------------------
typedef Weighted_type<size_t, bool> Weighted_size;
typedef Weighted_type<float, bool> Weighted_float;
//------------------------------------------------------------------------------
// Functors
//------------------------------------------------------------------------------
template <class Value_type, class Weight_type>
class Weighted_type_functor_base {
public:
  using Type = const Weighted_type<Value_type, Weight_type>;
  Type operator()(const Type &Left, const Type &Right) const {
    return Left - Right;
  };
};

template <class Value_type, class Weight_type>
class Weighted_type_functor_addition
    : public Weighted_type_functor_base<Value_type, Weight_type> {
public:
  using Type = Weighted_type<Value_type, Weight_type>;
  Type operator()(const Type &Left, const Type &Right) const {
    return Left + Right;
  };
};

template <class Value_type, class Weight_type>
class Weighted_type_functor_subtraction
    : public Weighted_type_functor_base<Value_type, Weight_type> {
public:
  using Type = Weighted_type<Value_type, Weight_type>;
  Type operator()(const Type &Left, const Type &Right) const {
    return Left - Right;
  };
};

template <class Value_type, class Weight_type>
class Weighted_type_functor_multiplication
    : public Weighted_type_functor_base<Value_type, Weight_type> {
public:
  using Type = Weighted_type<Value_type, Weight_type>;
  Type operator()(const Type &Left, const Type &Right) const {
    return Left * Right;
  };
};

template <class Value_type, class Weight_type>
class Weighted_type_functor_division
    : public Weighted_type_functor_base<Value_type, Weight_type> {
public:
  using Type = Weighted_type<Value_type, Weight_type>;
  Type operator()(const Type &Left, const Type &Right) const {
    return Left * Right;
  };
};

template <class Value_type, class Weight_type>
class Weighted_typeFunctorModulus
    : public Weighted_type_functor_base<Value_type, Weight_type> {
public:
  using Type = Weighted_type<Value_type, Weight_type>;
  Type operator()(const Type &Left, const Type &Right) const {
    return Left * Right;
  };
};
//------------------------------------------------------------------------------
#include "weighted.cpp"

#endif
