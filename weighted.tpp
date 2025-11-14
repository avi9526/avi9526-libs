
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

#ifndef WEIGHTED_CPP
#define WEIGHTED_CPP

#include "weighted.h"

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>::Weighted_type()
  : Weighted_base<Weight_type>()
  , _Value(){};

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>::Weighted_type(
  const Weighted_type<Value_type, Weight_type>& Val)
  : Weighted_base<Weight_type>(Val.Weight())
  , _Value(Val._Value){

  };

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>::Weighted_type(Value_type Value)
  : Weighted_base<Weight_type>(true)
  , _Value(Value){};
template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>::Weighted_type(Weight_type Weight,
                                                      Value_type Value)
  : Weighted_base<Weight_type>(Weight)
  , _Value(Value){};

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>::~Weighted_type(){};

template<class Value_type, class Weight_type>
Value_type&
Weighted_type<Value_type, Weight_type>::Value()
{
  return _Value;
};

template<class Value_type, class Weight_type>
const Value_type&
Weighted_type<Value_type, Weight_type>::Value() const
{
  return _Value;
}

template<class Value_type, class Weight_type>
void
Weighted_type<Value_type, Weight_type>::Reset()
{
  // Value() = static_cast<Value_type>(0);
  Parent_type::Reset();
};

template<class Value_type, class Weight_type>
Value_type
Weighted_type<Value_type, Weight_type>::Value_mult_weight()
{
  return (_Value *
          static_cast<Value_type>(Weighted_base<Weight_type>::Weight()));
};

template<class Value_type, class Weight_type>
Value_type
Weighted_type<Value_type, Weight_type>::Value_and_weight()
{
  return (_Value &&
          static_cast<Value_type>(Weighted_base<Weight_type>::Weight()));
};

template<class Value_type, class Weight_type>
void
Weighted_type<Value_type, Weight_type>::Average_from(
  Weighted_type<Value_type, Weight_type> W1,
  Weighted_type<Value_type, Weight_type> W2)
{
  Weighted_base<Weight_type>::Weight() = W1 * W2;
  _Value = (W1._Value * W1._Weight() + W2._Value * W2._Weight()) /
           (W1._Weight() + W2._Weight());
};

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>&
Weighted_type<Value_type, Weight_type>::operator=(
  const Weighted_type<Value_type, Weight_type>& Val)
{
  _Value = Val._Value;
  Weighted_base<Weight_type>::Weight() = Val.Weight();
  return *this;
};

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>::operator Value_type()
{
  return _Value;
}

template<class Value_type, class Weight_type>
void
Weighted_type<Value_type, Weight_type>::operator()(Weight_type Weight,
                                                   Value_type Value)
{
  _Value = Value;
  Weighted_base<Weight_type>::Weight() = Weight;
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator<(const Weighted_type<Value_type, Weight_type>& V1,
          const Weighted_type<Another_type, Weight_type>& V2)
{
  return V1.Weight() && V2.Weight() &&
         (V1.Value() < static_cast<Value_type>(V2.Value()));
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator<(const Weighted_type<Value_type, Weight_type>& V1,
          const Another_type& V2)
{
  return V1.Weight() && (V1.Value() < V2);
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator<=(const Weighted_type<Value_type, Weight_type>& V1,
           const Weighted_type<Another_type, Weight_type>& V2)
{
  return V1.Weight() && V2.Weight() &&
         (V1.Value() <= static_cast<Value_type>(V2.Value()));
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator<=(const Weighted_type<Value_type, Weight_type>& V1,
           const Another_type& V2)
{
  return V1.Weight() && (V1.Value() <= V2);
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator==(const Weighted_type<Value_type, Weight_type>& V1,
           const Weighted_type<Another_type, Weight_type>& V2)
{
  return V1.Weight() && V2.Weight() &&
         (V1.Value() == static_cast<Value_type>(V2.Value()));
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator==(const Weighted_type<Value_type, Weight_type>& V1,
           const Another_type& V2)
{
  return V1.Weight() && (V1.Value() == V2);
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator!=(const Weighted_type<Value_type, Weight_type>& V1,
           const Weighted_type<Another_type, Weight_type>& V2)
{
  return V1.Weight() && V2.Weight() &&
         (V1.Value() != static_cast<Value_type>(V2.Value()));
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator!=(const Weighted_type<Value_type, Weight_type>& V1,
           const Another_type& V2)
{
  return V1.Weight() && (V1.Value() != V2);
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator>(const Weighted_type<Value_type, Weight_type>& V1,
          const Weighted_type<Another_type, Weight_type>& V2)
{
  return V1.Weight() && V2.Weight() &&
         (V1.Value() > static_cast<Value_type>(V2.Value()));
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator>(const Weighted_type<Value_type, Weight_type>& V1,
          const Another_type& V2)
{
  return V1.Weight() && (V1.Value() > V2);
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator>=(const Weighted_type<Value_type, Weight_type>& V1,
           const Weighted_type<Another_type, Weight_type>& V2)
{
  return V1.Weight() && V2.Weight() &&
         (V1.Value() >= static_cast<Value_type>(V2.Value()));
};

template<class Value_type, class Weight_type, class Another_type>
bool
operator>=(const Weighted_type<Value_type, Weight_type>& V1,
           const Another_type& V2)
{
  return V1.Weight() && (V1.Value() >= V2);
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator+(const Weighted_type<Value_type, Weight_type>& V1,
          const Weighted_type<Another_type, Weight_type>& V2)
{
  Value_type Result = V1.Value() + static_cast<Value_type>(V2.Value());
  bool ResultValid = ((V2.Value() >= 0) && (Result >= V1.Value())) ||
                     ((V2.Value() <= 0) && (Result <= V1.Value()));
  return Weighted_type<Value_type, Weight_type>(
    V1.Weight() && V2.Weight() && static_cast<Weight_type>(ResultValid),
    Result);
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator+(const Weighted_type<Value_type, Weight_type>& V1,
          const Another_type& V2)
{
  return (V1 + static_cast<Weighted_type<Value_type, Weight_type>>(V2));
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>&
operator+=(Weighted_type<Value_type, Weight_type>& V1, const Another_type& V2)
{
  V1 = V1 + V2;
  return V1;
};

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>&
operator++(Weighted_type<Value_type, Weight_type>& V1)
{
  return V1 = V1 + 1;
}

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator-(const Weighted_type<Value_type, Weight_type>& V1,
          const Weighted_type<Another_type, Weight_type>& V2)
{
  Value_type Result = V1.Value() - static_cast<Value_type>(V2.Value());
  bool ResultValid = ((V2.Value() >= 0) && (Result <= V1.Value())) ||
                     ((V2.Value() <= 0) && (Result >= V1.Value()));
  return Weighted_type<Value_type, Weight_type>(
    V1.Weight() && V2.Weight() && static_cast<Weight_type>(ResultValid),
    Result);
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator-(const Weighted_type<Value_type, Weight_type>& V1,
          const Another_type& V2)
{
  return (V1 - static_cast<Weighted_type<Value_type, Weight_type>>(V2));
};

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>&
operator--(Weighted_type<Value_type, Weight_type>& V1)
{
  return V1 = V1 - 1;
}

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>&
operator-=(Weighted_type<Value_type, Weight_type>& V1, const Another_type& V2)
{
  V1 = V1 - V2;
  return V1;
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator*(const Weighted_type<Value_type, Weight_type>& V1,
          const Weighted_type<Another_type, Weight_type>& V2)
{
  Weighted_type<Value_type, Weight_type> Temp;
  Temp.Weight() = V1.Weight() && V2.Weight();
  Temp.Value() = V1.Value() * static_cast<Value_type>(V2.Value());
  if ((V1.Value() != static_cast<Value_type>(0)) &&
      (V2.Value() != static_cast<Another_type>(0))) {
    // FIXME: IsFloat<Value_type> is not enough, it can be class that operates
    // with float
    if constexpr (!IsFloat<Value_type>) {
      Temp.Weight() =
        Temp.Weight() &&
        (Temp.Value() / static_cast<Value_type>(V2.Value()) == V1.Value());
    } else {
      // FIXME: check float as well
    }
  }
  return Temp;
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator*(const Weighted_type<Value_type, Weight_type>& V1,
          const Another_type& V2)
{
  return (V1 * static_cast<Weighted_type<Value_type, Weight_type>>(V2));
};

// template<class Value_type, class Weight_type, class Another_type>
// Weighted_type<Value_type, Weight_type>
// operator*(Another_type V1, Weighted_type<Value_type, Weight_type> V2)
//{
//   return (Weighted_type<Value_type, Weight_type>(V1) * V2);
// };

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator/(const Weighted_type<Value_type, Weight_type>& V1,
          const Weighted_type<Another_type, Weight_type>& V2)
{
  Weighted_type<Value_type, Weight_type> V;
  if (V2.Value() != static_cast<Value_type>(0)) {
    V.Value() = V1.Value() / V2.Value();
    // FIXME: IsFloat<Value_type> is not enough, it can be class that operates
    // with float
    if constexpr (!IsFloat<Value_type>) {
      V.Weight() =
        V1.Weight() && V2.Weight() &&
        (V2.Value() != static_cast<Value_type>(0)) &&
        (V.Value() * static_cast<Value_type>(V2.Value()) == V1.Value());
    } else {
      // FIXME: check float as well
      V.Weight() = V1.Weight() && V2.Weight();
    }
  }
  return V;
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator/(const Weighted_type<Value_type, Weight_type>& V1,
          const Another_type& V2)
{
  return (V1 / static_cast<Weighted_type<Value_type, Weight_type>>(V2));
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator%(const Weighted_type<Value_type, Weight_type>& V1,
          const Weighted_type<Another_type, Weight_type>& V2)
{
  Weighted_type<Value_type, Weight_type> V;
  if (V2.Value() != static_cast<Value_type>(0)) {
    V.Value() = V1.Value() % static_cast<Value_type>(V2.Value());
    V.Weight() =
      V1.Weight() && V2.Weight() &&
      (V2.Value() != static_cast<Value_type>(0)) &&
      ((V1.Value() - V.Value()) % static_cast<Value_type>(V2.Value()) == 0);
  }
  return V;
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator%(const Weighted_type<Value_type, Weight_type>& V1,
          const Another_type& V2)
{
  return (V1 % static_cast<Weighted_type<Value_type, Weight_type>>(V2));
};

// template<class Value_type, class Weight_type, class Another_type>
// Weighted_type<Value_type, Weight_type>
// operator/(Another_type V1, Weighted_type<Value_type, Weight_type> V2)
//{
//   return (Weighted_type<Value_type, Weight_type>(V1) / V2);
// };

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>
operator&&(const Weighted_type<Value_type, Weight_type>& V1,
           const Weighted_type<Value_type, Weight_type>& V2)
{
  return Weighted_type<Value_type, Weight_type>(V1.Weight() && V2.Weight(),
                                                V1.Value() && V2.Value());
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator&&(const Weighted_type<Value_type, Weight_type>& V1,
           const Another_type& V2)
{
  return (V1 && static_cast<Weighted_type<Value_type, Weight_type>>(V2));
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator&&(const Another_type& V1,
           const Weighted_type<Value_type, Weight_type>& V2)
{
  return (static_cast<Weighted_type<Value_type, Weight_type>>(V1) && V2);
};

template<class Value_type, class Weight_type>
Weighted_type<Value_type, Weight_type>
operator||(const Weighted_type<Value_type, Weight_type>& V1,
           const Weighted_type<Value_type, Weight_type>& V2)
{
  return Weighted_type<Value_type, Weight_type>(V1.Weight() && V2.Weight(),
                                                V1.Value() && V2.Value());
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator||(const Weighted_type<Value_type, Weight_type>& V1,
           const Another_type& V2)
{
  return (V1 || static_cast<Weighted_type<Value_type, Weight_type>>(V2));
};

template<class Value_type, class Weight_type, class Another_type>
Weighted_type<Value_type, Weight_type>
operator||(const Another_type& V1,
           const Weighted_type<Value_type, Weight_type>& V2)
{
  return (static_cast<Weighted_type<Value_type, Weight_type>>(V1) || V2);
};

// template<class Value_type, class Weight_type>
// std::ostream&
// operator<<(std::ostream& os, Weighted_type<Value_type, Weight_type>& Val)
// {
//   os << typeid(Val).name() << ": Weight=" <<
//   static_cast<bool>(Val.Weight())
//      << ", Value=" << 10;
//   return os;
// }

#endif
