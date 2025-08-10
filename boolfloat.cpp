
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

#include "boolfloat.h"

BoolFloatNormalized::BoolFloatNormalized()
{
  _Threshold = Normalize(0.5);
  Value(false);
}

BoolFloatNormalized::BoolFloatNormalized(const float V)
{
  _Threshold = Normalize(0.5);
  Value(V);
}

BoolFloatNormalized::BoolFloatNormalized(const bool B)
{
  Value(B);
}

BoolFloatNormalized::BoolFloatNormalized(const BoolFloatNormalized& V)
{
  _Value = V._Value;
  _Threshold = V._Threshold;
}

BoolFloatNormalized::~BoolFloatNormalized() {}

float
BoolFloatNormalized::Value() const
{
  return _Value;
}

void
BoolFloatNormalized::Value(const float Value)
{
  _Value = Normalize(Value);
}

void
BoolFloatNormalized::Value(const bool B)
{
  if (B) {
    _Value = Normalize(1);
  } else {
    _Value = Normalize(0);
  }
}

void
BoolFloatNormalized::False()
{
  Value(false);
}

void
BoolFloatNormalized::True()
{
  Value(true);
}

bool
BoolFloatNormalized::Valid()
{
  return (_Value >= _Threshold);
}

float
BoolFloatNormalized::Normalize(float Value)
{
  if (Value < 0) {
    Value = 0;
  } else if (Value > 1) {
    Value = 1;
  }
  return Value;
}

float
BoolFloatNormalized::Threshold()
{
  return _Threshold;
}

void
BoolFloatNormalized::Threshold(const float Threshold)
{
  _Threshold = Normalize(Threshold);
}

BoolFloatNormalized
operator&&(BoolFloatNormalized V1, BoolFloatNormalized V2)
{
  BoolFloatNormalized V;
  V.Value(V1._Value * V2._Value);
  return V;
}

BoolFloatNormalized
operator&&(BoolFloatNormalized V1, bool V2)
{
  return (V1 && BoolFloatNormalized(V2));
}

BoolFloatNormalized
operator&&(bool V1, BoolFloatNormalized V2)
{
  return (BoolFloatNormalized(V1) && V2);
}

BoolFloatNormalized
operator||(BoolFloatNormalized V1, BoolFloatNormalized V2)
{
  BoolFloatNormalized V;
  V.Value(V1._Value + V2._Value - V1._Value * V2._Value);
  return V;
}

BoolFloatNormalized
operator^(BoolFloatNormalized V1, BoolFloatNormalized V2)
{
  BoolFloatNormalized V;
  V.Value(V1._Value + V2._Value - 2 * V1._Value * V2._Value);
  return V;
}

BoolFloatNormalized
operator!(BoolFloatNormalized V1)
{
  V1.Value(1 - V1._Value);
  return V1;
}

BoolFloatNormalized&
BoolFloatNormalized::operator=(BoolFloatNormalized B)
{
  if (this == &B) {
    return *this;
  }
  Value(B.Value());
  Threshold(B.Threshold());
  return *this;
}

BoolFloatNormalized&
BoolFloatNormalized::operator=(bool V)
{
  Value(V);
  return *this;
}

BoolFloatNormalized&
BoolFloatNormalized::operator=(float V)
{
  Value(V);
  return *this;
}

BoolFloatNormalized::operator float()
{
  return Value();
}

BoolFloatNormalized::operator bool()
{
  return Valid();
}
