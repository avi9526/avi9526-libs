
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

#ifndef Array_of_H
#define Array_of_H

#include "common.h"
#include "memoryrange.h"
#include "range.h"
#include "weighted.h"
#include "weightedbase.h"

template <class Value_type> class Array_of : public Weighted_base<bool> {
public:
  Array_of();
  template <class Some_type> Array_of(const Some_type &StaticArrayReference);
  ~Array_of();

  bool Allocate(const Weighted_size &Size);
  bool Allocate_append_init(const Weighted_size &Size);
  bool Reallocate(const Weighted_size &Size);
  template <class Some_type>
  bool Adopt(const Some_type &Pointer, const size_t &Size_in_bytes,
             const bool Is_allocated = false);
  template <class Some_type> bool Adopt(const Some_type &StaticArray);
  void Adopt_array_end(const Weighted_size& New_end);
  void Free();
  void Abandon(const bool &DestroyElements = false);
  void Free_or_abandon();

  Weighted_size Max_end() const;
  Weighted_size End() const;
  Weighted_size Size() const;
  Range_of_size All() const;

  Value_type &operator[](const Weighted_size &Index);
  const Value_type &operator[](const Weighted_size &Index) const;
  Value_type &operator()(const Weighted_size &Index);
  const Value_type &operator()(const Weighted_size &Index) const;
  Value_type &Last();
  bool Index_valid(const Range_of_size &Index_range) const;
  bool Index_valid(const Weighted_size &Index) const;
  bool Iterate_with(Weighted_size &Index) const;
  bool Iterate_with_within(Weighted_size &Index,
                           const Range_of_size &Range) const;

  Weighted_size Element_size() const;
  bool Element_size(Weighted_size New_element_size);

  Range_of_size Append_empty(const Weighted_size &Relative_end);
  Weighted_size Append_empty();
  Range_of_size Append_init(const Weighted_size &Relative_end);
  Weighted_size Append_init();
  Weighted_size Append(const Value_type &Value);
  template <size_t Count>
  Range_of_size Append(const Value_type (&Value_array)[Count]);
  Weighted_size Append_move(Value_type &&Value);

  bool Drop_elements(const Range_of_size &Range);
  bool Delete_elements(const Range_of_size &Range);
  bool Delete_all_elements();

  template <size_t Count>
  bool Is_equal_at_to(Weighted_size &Position,
                      const Value_type (&Value_array)[Count],
                      const bool &Increment_position = true) const;

  // virtual void Reset() = 0; // Reset has different meaning in parent type

  bool Is_empty() const;

protected:
private:
  const Range_of_size
  _Index_to_memory_zero_base(const Range_of_size &Index_range) const;
  const Range_of_size
  _Index_to_memory_no_exist_check(const Range_of_size &Index_range) const;
  const Range_of_size
  _Index_to_memory_no_exist_check(const Weighted_size &Index) const;
  const Range_of_size
  _Index_to_memory_check_element_exist(const Range_of_size &Index_range) const;

  const Range_of_size
  _Memory_to_index_zero_base(const Range_of_size &Given_memory_range,
                             const Weighted_size &GivenElement_size) const;
  const Range_of_size
  _Memory_to_index_zero_base(const Range_of_size &Given_memory_range) const;
  const Range_of_size
  _Memory_to_index(const Range_of_size &Given_memory_range) const;

  Memory_range_type _Memory_range;
  Weighted_size _Index_end;
  Weighted_size _Element_size;
};

#include "array_of.cpp"

#endif
