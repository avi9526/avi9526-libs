
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

#ifndef Array_of_CPP
#define Array_of_CPP

#include "array_of.h"

template <class Value_type>
Array_of<Value_type>::Array_of()
    : Weighted_base<bool>(), _Memory_range(), _Index_end(),
      _Element_size(sizeof(Value_type)) {}

template <class Value_type>
template <class Some_type>
Array_of<Value_type>::Array_of(const Some_type &StaticArrayReference)
    : Weighted_base<bool>(), _Memory_range(), _Index_end(),
      _Element_size(sizeof(Value_type)) {
  Adopt(StaticArrayReference);
}

template <class Value_type> Array_of<Value_type>::~Array_of() {
  Free_or_abandon();
}

template <class Value_type>
bool Array_of<Value_type>::Allocate(const Weighted_size &Size) {
  if (_Memory_range.Free_or_abandon()) {
    _Index_end.Reset();
  }
  auto Result = _Memory_range.Allocate(
      _Index_to_memory_zero_base(Range_of_size(0, Size - 1)).Relative_end());
  if (Result) {
    _Memory_range.Wipe_with_zero_all();
  }
  Valid(Result);
  return Result;
}

template <class Value_type>
bool Array_of<Value_type>::Allocate_append_init(const Weighted_size &Size) {
  auto Result = Allocate(Size);
  Append_init(Size);
  Valid_and(Result);
  return Result;
}

template <class Value_type>
bool Array_of<Value_type>::Reallocate(const Weighted_size &Size) {
  auto Result = _Memory_range.Reallocate(
      _Index_to_memory_zero_base(Range_of_size(0, Size - 1)).Relative_end());
  Valid(Result);
  return Result;
}

template <class Value_type>
template <class Some_type>
bool Array_of<Value_type>::Adopt(const Some_type &Pointer,
                                 const size_t &Size_in_bytes,
                                 const bool Is_allocated) {
  auto Result = false;
  if (_Memory_range.Free_or_abandon()) {
    _Index_end.Reset();
  }
  Range_of_size Memory;
  Memory.Start(reinterpret_cast<size_t>(&Pointer));
  Memory.End_from_size(Size_in_bytes);
  Weighted_size NewIndexEnd = _Memory_to_index_zero_base(Memory).Relative_end();
  if (NewIndexEnd.Valid()) {
    Result = _Memory_range.Adopt(Memory, Is_allocated);
    if (Result) {
      _Memory_range.Wipe_with_zero_all();
    }
  }
  Valid(Result);
  return Result;
}

template <class Value_type>
template <class Some_type>
bool Array_of<Value_type>::Adopt(const Some_type &StaticArray) {
  return Adopt(StaticArray, sizeof(StaticArray), false);
}

template <class Value_type> void Array_of<Value_type>::Free() {
  Delete_elements(All());
  _Memory_range.Wipe_with_zero_all();
  _Memory_range.Free();
}

template <class Value_type>
void Array_of<Value_type>::Abandon(const bool &DestroyElements) {
  if (DestroyElements) {
    Delete_elements(All());
  }
  _Memory_range.Abandon();
}

template <class Value_type> void Array_of<Value_type>::Free_or_abandon() {
  Delete_elements(All());
  _Memory_range.Free_or_abandon();
}

template <class Value_type>
Weighted_size Array_of<Value_type>::Max_end() const {
  return ((_Memory_range.Range() << _Memory_range.Range()) / _Element_size)
      .End();
}

template <class Value_type> Weighted_size Array_of<Value_type>::End() const {
  return _Index_end;
}

template <class Value_type> Weighted_size Array_of<Value_type>::Size() const {
  return _Index_end + 1;
}

template <class Value_type> Range_of_size Array_of<Value_type>::All() const {
  return Range_of_size(Weighted_size(0), _Index_end);
}

template <class Value_type>
Value_type &Array_of<Value_type>::operator[](const Weighted_size &Index) {
  auto Range =
      _Index_to_memory_check_element_exist(Range_of_size(Index, Index));
  if (Range.Valid()) {
    return *reinterpret_cast<Value_type *>(Range.Start().Value());
  }
  return *reinterpret_cast<Value_type *>(0);
}

template <class Value_type>
const Value_type &
Array_of<Value_type>::operator[](const Weighted_size &Index) const {
  auto Range =
      _Index_to_memory_check_element_exist(Range_of_size(Index, Index));
  if (Range.Valid()) {
    return *reinterpret_cast<Value_type *>(Range.Start().Value());
  }
  return *reinterpret_cast<Value_type *>(0);
}

template <class Value_type>
Value_type &Array_of<Value_type>::operator()(const Weighted_size &Index) {
  auto Range =
      _Index_to_memory_check_element_exist(Range_of_size(Index, Index));
  if (Range.Valid()) {
    return *reinterpret_cast<Value_type *>(Range.Start().Value());
  }
  return *reinterpret_cast<Value_type *>(0);
}

template <class Value_type>
const Value_type &
Array_of<Value_type>::operator()(const Weighted_size &Index) const {
  auto Range =
      _Index_to_memory_check_element_exist(Range_of_size(Index, Index));
  if (Range.Valid()) {
    return *reinterpret_cast<Value_type *>(Range.Start().Value());
  }
  return *reinterpret_cast<Value_type *>(0);
}

template <class Value_type> Value_type &Array_of<Value_type>::Last() {
  return operator[](End());
}

template <class Value_type>
bool Array_of<Value_type>::Iterate_with(Weighted_size &Index) const {
  if (Index.Valid()) {
    ++Index;
  } else {
    Index = 0;
  }
  return (Index <= _Index_end);
}

template <class Value_type>
bool Array_of<Value_type>::Iterate_with_within(
    Weighted_size &Index, const Range_of_size &Range) const {
  if (Index.Valid()) {
    ++Index;
  } else {
    Index = Range.Start();
  }
  return Range.Does_contain(Index) && (Index <= _Index_end);
}

template <class Value_type>
Weighted_size Array_of<Value_type>::Element_size() const {
  return _Element_size;
}

template <class Value_type>
bool Array_of<Value_type>::Element_size(Weighted_size New_element_size) {
  auto Result = false;
  if (New_element_size.Valid() && !_Memory_range.Allocated_or_adopted()) {
    _Element_size = New_element_size;
    Result = true;
  }
  Valid_and(Result);
  return Result;
}

template <class Value_type>
Range_of_size
Array_of<Value_type>::Append_empty(const Weighted_size &Relative_end) {
  Range_of_size Result;
  Weighted_size AvailableEnd;
  if (_Index_end.Valid()) {
    AvailableEnd = Max_end() - _Index_end - 1;
  } else {
    AvailableEnd = Max_end();
  }
  if (Relative_end <= AvailableEnd) {
    if (_Index_end.Valid()) {
      _Index_end += 1;
    } else {
      _Index_end = 0;
    }
    Result.Start() = _Index_end;
    _Index_end += Relative_end;
    Result.End() = _Index_end;
  }
  Valid_and(Result.Valid());
  return Result;
}

template <class Value_type> Weighted_size Array_of<Value_type>::Append_empty() {
  return Append_empty(0).Start();
}

template <class Value_type>
Range_of_size
Array_of<Value_type>::Append_init(const Weighted_size &Relative_end) {
  Range_of_size New_element_indexRange = Append_empty(Relative_end);
  Weighted_size Index;
  while (Iterate_with_within(Index, New_element_indexRange)) {
    new (&operator[](Index)) Value_type();
  }
  return New_element_indexRange;
}

template <class Value_type> Weighted_size Array_of<Value_type>::Append_init() {
  return Append_init(0).Start();
}

template <class Value_type>
Weighted_size Array_of<Value_type>::Append(const Value_type &Value) {
  auto Result(Append_empty());
  if (Result.Valid()) {
    new (&operator[](Result)) Value_type(Value);
  }
  return Result;
}

template <class Value_type>
template <size_t Count>
Range_of_size
Array_of<Value_type>::Append(const Value_type (&Value_array)[Count]) {
  Range_of_size Result(Append_empty(Count - 1));
  {
    Weighted_size Index;
    Weighted_size Index_for_input_array(0);
    while (Iterate_with_within(Index, Result)) {
      new (&operator[](Index))
          Value_type(Value_array[Index_for_input_array.Value()]);
      ++Index_for_input_array;
    }
  }
  return Result;
}

template <class Value_type>
Weighted_size Array_of<Value_type>::Append_move(Value_type &&Value) {
  Weighted_size New_element_index = Append_empty();
  if (New_element_index.Valid()) {
    new (&operator[](New_element_index)) Value_type(Move_RValue(Value));
  }
  Valid_and(New_element_index.Valid());
  return New_element_index;
}

template <class Value_type>
bool Array_of<Value_type>::Drop_elements(const Range_of_size &Range) {
  auto Result = false;
  if (Index_valid(Range)) {
    _Memory_range.Wipe_with_zero(_Index_to_memory_no_exist_check(Range));
    Range_of_size Elements_after(Range.End() + 1, _Index_end);
    if (Elements_after.Valid()) {
      Range_of_size Elements_after_move_to;
      Elements_after_move_to.Start(Range.Start());
      Elements_after_move_to.End_from_relative_end(
          Elements_after.Relative_end());
      _Memory_range.Shift_exchange(
          _Index_to_memory_no_exist_check(Elements_after),
          _Index_to_memory_no_exist_check(Elements_after_move_to));
      _Index_end = Elements_after_move_to.End();
    } else {
      _Index_end = Range.Start() - 1;
      // When Range.Start()==0 the Range.Start() - 1 will be invalid
      // because of overflow on most platforms, but lets make sure
      _Index_end.Valid(Range.Start() >= Weighted_size(1));
    }
    Result = true;
  } else {
    Valid_and(!Range.Valid()); // invalid range should not invalidate array)
  }
  return Result;
}

template <class Value_type>
bool Array_of<Value_type>::Delete_elements(const Range_of_size &Range) {
  Weighted_size Index;
  while (Iterate_with_within(Index, Range)) {
    operator[](Index).~Value_type();
  }
  return Drop_elements(Range);
}

template <class Value_type> bool Array_of<Value_type>::Is_empty() const {
  return _Index_end.Valid();
}

template <class Value_type> bool Array_of<Value_type>::Delete_all_elements() {
  return Delete_elements(All());
}

template <class Value_type>
const Range_of_size Array_of<Value_type>::_Index_to_memory_zero_base(
    const Range_of_size &Index_range) const {
  return Index_range * _Element_size;
}

template <class Value_type>
const Range_of_size Array_of<Value_type>::_Index_to_memory_no_exist_check(
    const Range_of_size &Index_range) const {
  auto Result =
      _Index_to_memory_zero_base(Index_range) >> _Memory_range.Range();
  if (!_Memory_range.Range().Does_contain(Result)) {
    Result.Reset();
  }
  return Result;
}

template <class Value_type>
const Range_of_size Array_of<Value_type>::_Index_to_memory_no_exist_check(
    const Weighted_size &Index) const {
  return _Index_to_memory_no_exist_check(Range_of_size(Index, Index));
}

template <class Value_type>
bool Array_of<Value_type>::Index_valid(const Range_of_size &Index_range) const {
  return Range_of_size(0, _Index_end).Does_contain(Index_range);
}

template <class Value_type>
bool Array_of<Value_type>::Index_valid(const Weighted_size &Index) const {
  return Range_of_size(0, _Index_end).Does_contain(Index);
}

template <class Value_type>
const Range_of_size Array_of<Value_type>::_Index_to_memory_check_element_exist(
    const Range_of_size &Index_range) const {
  Range_of_size Result;
  if (Index_valid(Index_range)) {
    Result = _Index_to_memory_no_exist_check(Index_range);
  }
  return Result;
}

template <class Value_type>
const Range_of_size Array_of<Value_type>::_Memory_to_index_zero_base(
    const Range_of_size &Given_memory_range,
    const Weighted_size &GivenElement_size) const {
  Range_of_size Result;
  if ((Given_memory_range.Size() / GivenElement_size > 0)) {
    Result = Given_memory_range / GivenElement_size;
  }
  return Result;
}

template <class Value_type>
const Range_of_size Array_of<Value_type>::_Memory_to_index_zero_base(
    const Range_of_size &Given_memory_range) const {
  return _Memory_to_index_zero_base(Given_memory_range, _Element_size);
}

template <class Value_type>
const Range_of_size Array_of<Value_type>::_Memory_to_index(
    const Range_of_size &Given_memory_range) const {
  Range_of_size Result;
  if (_Memory_range.Range().Does_contain(Given_memory_range)) {
    Result =
        _Memory_to_index_zero_base(Given_memory_range << _Memory_range.Range());
  }
  return Result;
}

template <class Value_type>
template <size_t Count>
bool Array_of<Value_type>::Is_equal_at_to(
    Weighted_size &Position, const Value_type (&Value_array)[Count],
    const bool &Increment_position) const {
  bool Result = false;
  Weighted_size Index;
  size_t Second_array_index = 0;
  Range_of_size This_array_range;
  This_array_range.Start(Position);
  This_array_range.End_from_size(Count);
  while (Iterate_with_within(Index, This_array_range)) {
    if (operator[](Index) == Value_array[Second_array_index]) {
      Result = true;
    } else {
      Result = false;
      break;
    }
    Second_array_index++;
  }
  if (Result && Increment_position) {
    Position = This_array_range.End() + 1;
  }
  return Result;
}

#endif
