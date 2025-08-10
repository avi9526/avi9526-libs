
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

#ifndef STD_PARTS_H
#define STD_PARTS_H
//------------------------------------------------------------------------------
// Same class comparison
//------------------------------------------------------------------------------
template<class Type1, class Type2>
class SameClassBase
{
public:
  typedef void Result;
  static const bool Value = false;
};

template<class Type>
class SameClassBase<Type, Type>
{
public:
  typedef Type Result;
  static const bool Value = true;
};

template<class Type1, class Type2>
static const bool SameClass = SameClassBase<Type1, Type2>::Value;

// Is float

template<class Type1>
static const bool IsFloat =
  SameClass<Type1, float> || SameClass<Type1, double> ||
  SameClass<Type1, long double>;
//------------------------------------------------------------------------------
// Remove reference
//------------------------------------------------------------------------------
template<class T>
class Dereference_Base
{
public:
  typedef T Type;
  static const bool IsReference = false;
};

template<class T>
class Dereference_Base<T&>
{
public:
  typedef T Type;
  static const bool IsReference = true;
};

template<class T>
class Dereference_Base<const T&>
{
public:
  typedef T Type;
  static const bool IsReference = false;
};

template<class T>
class Dereference_Base<const T&&>
{
public:
  typedef const T&& Type;
  static const bool IsReference = false;
};

template<class T>
using Dereference = typename Dereference_Base<T>::Type;

template<class T>
static const bool IsReferenceType = Dereference_Base<T>::IsReference;
//------------------------------------------------------------------------------
// Make pointer TYPE if reference TYPE given
//------------------------------------------------------------------------------
template<class T>
class PointerIfReference_Base
{
public:
  typedef T Type;
};

template<class T>
class PointerIfReference_Base<T&>
{
public:
  typedef T* Type;
};

template<class T>
class PointerIfReference_Base<const T&>
{
public:
  typedef const T Type;
};

template<class T>
using PointerIfReferenceType = typename PointerIfReference_Base<T>::Type;
//------------------------------------------------------------------------------
// Make reference TYPE if reference TYPE given
//------------------------------------------------------------------------------
template<class T>
class ReferenceIfReference_Base
{
public:
  typedef T Type;
};

template<class T>
class ReferenceIfReference_Base<T&>
{
public:
  typedef T& Type;
};

template<class T>
class ReferenceIfReference_Base<const T&>
{
public:
  typedef const T Type;
};

template<class T>
using ReferenceIfReferenceType = typename ReferenceIfReference_Base<T>::Type;
//------------------------------------------------------------------------------
// Make pointer VARIABLE if reference VARIABLE given
//------------------------------------------------------------------------------
template<class T>
static T*
PointerIfReference(T& Variable)
{
  return &Variable;
};

template<class T>
static const T&
PointerIfReference(const T& Variable)
{
  return Variable;
};
//------------------------------------------------------------------------------
// Auto dereference for pointers to avoid . and -> confusion in templates
//------------------------------------------------------------------------------
template<class T>
T&
DereferenceIfPointer(T* Variable)
{
  return *Variable;
};

template<class T>
T&
DereferenceIfPointer(T& Variable)
{
  return Variable;
};
//------------------------------------------------------------------------------
// Move
//------------------------------------------------------------------------------
template<class Type>
Dereference<Type>&&
Move_RValue(Type&& Value)
{
  return static_cast<Dereference<Type>&&>(Value);
}
//------------------------------------------------------------------------------

#endif
