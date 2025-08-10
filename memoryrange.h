
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

#ifndef MEMORYRANGE_H
#define MEMORYRANGE_H

#include "common.h"
#include "range.h"
#include "weighted.h"

typedef Range_type<size_t> Range_of_size;

class Memory_range_type {
public:
  Memory_range_type();
  ~Memory_range_type();

  Range_of_size &Range();
  const Range_of_size &Range() const;

  bool Allocated() const;
  bool Adopted() const;
  bool Allocated_or_adopted() const;

  bool Allocate(const Weighted_size &Relative_end);
  bool Reallocate(Weighted_size Relative_end);
  bool Adopt(Range_of_size New_range, bool Is_allocated = false);
  bool Free();
  Range_of_size Abandon();
  bool Free_or_abandon();

  bool Shift_exchange(Range_of_size Source, Range_of_size Destination);
  bool Wipe_with_zero(Range_of_size Destination);
  bool Wipe_with_zero_all();

protected:
  void Allocated(const bool &VAllocated);

private:
  Range_of_size _Range;
  bool _Allocated;
};

#endif // MEMORYRANGE_H
