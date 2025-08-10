
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

#ifndef WEIGHTEDBASE_CPP
#define WEIGHTEDBASE_CPP

#include "weightedbase.h"

template <class Weight_type>
Weighted_base<Weight_type>::Weighted_base()
    : _Weight(false) // don't change this to true, it will affect big chunk of a
                     // code somewhere
{}

template <class Weight_type>
Weighted_base<Weight_type>::Weighted_base(const Weight_type &V) : _Weight(V) {}

template <class Weight_type> Weighted_base<Weight_type>::~Weighted_base() {}

template <class Weight_type> Weight_type &Weighted_base<Weight_type>::Weight() {
  return _Weight;
}

template <class Weight_type>
const Weight_type &Weighted_base<Weight_type>::Weight() const {
  return _Weight;
}

template <class Weight_type>
void Weighted_base<Weight_type>::Weight(const Weight_type &V) {
  _Weight = V;
}

template <class Weight_type> bool Weighted_base<Weight_type>::Valid() const {
  return _Weight;
}

template <class Weight_type>
void Weighted_base<Weight_type>::Valid(const bool &V) {
  _Weight = V;
}

template <class Weight_type>
void Weighted_base<Weight_type>::Valid_and(const bool &V) {
  _Weight = _Weight && V;
}

template <class Weight_type> void Weighted_base<Weight_type>::Reset() {
  Valid(false);
}

#endif
