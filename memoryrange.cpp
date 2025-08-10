
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

#ifndef MEMORYRANGE_CPP
#define MEMORYRANGE_CPP

#include "memoryrange.h"

Memory_range_type::Memory_range_type() : _Range(), _Allocated(false) {
  // assert(sizeof(size_t) == sizeof(void*));
}

Memory_range_type::~Memory_range_type() { Free_or_abandon(); }

bool Memory_range_type::Allocated() const {
  return _Allocated && _Range.Start().Valid();
}

bool Memory_range_type::Adopted() const {
  return !_Allocated && _Range.Valid();
}

bool Memory_range_type::Allocated_or_adopted() const {
  return Allocated() || Adopted();
}

void Memory_range_type::Allocated(const bool &VAllocated) {
  _Allocated = VAllocated;
}

bool Memory_range_type::Allocate(const Weighted_size &Relative_end) {
  auto Result = false;
  if (!Allocated_or_adopted() && Relative_end.Valid()) {
    Range().Start() = reinterpret_cast<size_t>(malloc(Relative_end + 1));
    Range().Start().Weight() = Range().Start().Value() != 0;
    Range().End_from_relative_end(Relative_end);
    Result = Range().Start().Weight();
    Allocated(Result);
  }
  return Result;
}

bool Memory_range_type::Reallocate(Weighted_size Relative_end) {
  auto Result = false;
  if (Allocated() && Relative_end.Valid() &&
      Relative_end != Range().Relative_end()) {
    Range().Start() = reinterpret_cast<size_t>(realloc(
        reinterpret_cast<void *>(Range().Start().Value()), Relative_end + 1));
    Range().Start().Weight() = Range().Start().Value() != 0;
    Range().End_from_relative_end(Relative_end);
    Result = Range().Start().Weight();
    Allocated(Result);
  }
  return Result;
}

bool Memory_range_type::Adopt(Range_of_size New_range, bool Is_allocated) {
  auto Result = false;
  if (!Allocated_or_adopted() && New_range.Valid()) {
    Range() = New_range;
    Allocated(Is_allocated);
    Result = true;
  }
  return Result;
}

bool Memory_range_type::Free() {
  auto Result = false;
  if (Allocated()) {
    free(reinterpret_cast<void *>(Range().Start().Value()));
    Range().Reset();
    Allocated(false);
    Result = true;
  }
  return Result;
}

Range_of_size Memory_range_type::Abandon() {
  auto Result = Range();
  Allocated(false);
  Range().Reset();
  return Result;
}

bool Memory_range_type::Free_or_abandon() {
  auto Result = false;
  if (Allocated()) {
    Free();
  } else {
    Abandon().Valid();
  }
  return Result;
}

Range_of_size &Memory_range_type::Range() { return _Range; }

const Range_of_size &Memory_range_type::Range() const { return _Range; }

template <class TemplateClass>
bool _MemoryWipe_with_zeroBufferRaw(size_t &Start, size_t End) {
  if ((Start <= End) && (End - Start >= (sizeof(TemplateClass) - 1))) {
    const TemplateClass Buffer = 0;
    auto CurrentStart = Start;
    const auto StartMax = End - (sizeof(TemplateClass) - 1);
    while (CurrentStart <= StartMax) {
      *reinterpret_cast<TemplateClass *>(CurrentStart) = Buffer;
      if (CurrentStart < StartMax) {
        CurrentStart += sizeof(TemplateClass);
      } else {
        return true;
      }
    }
    Start = CurrentStart;
  }
  return false;
}

void _MemoryWipe_with_zeroRaw(size_t Start, size_t End) {
  auto Finished = _MemoryWipe_with_zeroBufferRaw<size_t>(Start, End);
  if constexpr (sizeof(size_t) > sizeof(uint64_t)) {
    if (!Finished) {
      Finished = _MemoryWipe_with_zeroBufferRaw<uint64_t>(Start, End);
    }
  }
  if constexpr (sizeof(size_t) > sizeof(uint32_t)) {
    if (!Finished) {
      Finished = _MemoryWipe_with_zeroBufferRaw<uint32_t>(Start, End);
    }
  }
  if constexpr (sizeof(size_t) > sizeof(uint16_t)) {
    if (!Finished) {
      Finished = _MemoryWipe_with_zeroBufferRaw<uint16_t>(Start, End);
    }
  }
  if constexpr (sizeof(size_t) > sizeof(uint8_t)) {
    if (!Finished) {
      _MemoryWipe_with_zeroBufferRaw<uint8_t>(Start, End);
    }
  }
}

bool Memory_range_type::Wipe_with_zero(Range_of_size Destination) {
  auto Result = false;
  if (Range().Does_contain(Destination)) {
    _MemoryWipe_with_zeroRaw(Destination.Start().Value(),
                             Destination.End().Value());
    Result = true;
  }
  return Result;
}

bool Memory_range_type::Wipe_with_zero_all() { return Wipe_with_zero(Range()); }

template <class TemplateClass>
void _MemoryShiftUpWithBufferRaw(size_t &CurrentSourceStart, size_t SourceEnd,
                                 size_t &CurrentDestinationStart,
                                 size_t StepForward, size_t StepBack,
                                 size_t &BufferSizeLeft) {
  TemplateClass BufferSource = 0;
  TemplateClass BufferDestination = 0;

  size_t BufferCount = BufferSizeLeft / sizeof(TemplateClass);
  BufferSizeLeft = BufferSizeLeft % sizeof(TemplateClass);

  size_t BufferIndex = 0;
  while (BufferIndex < BufferCount) {
    auto CurrentSource = CurrentSourceStart;
    auto CurrentDestination = CurrentDestinationStart;
    BufferSource = *reinterpret_cast<TemplateClass *>(CurrentSource);
    while (CurrentDestination != CurrentSourceStart) {
      if (CurrentSource <= SourceEnd) {
        CurrentDestination = CurrentSource + StepForward;
      } else {
        CurrentDestination = CurrentSource - StepBack;
      }
      BufferDestination =
          *reinterpret_cast<TemplateClass *>(CurrentDestination);
      *reinterpret_cast<TemplateClass *>(CurrentDestination) = BufferSource;
      BufferSource = BufferDestination;
      CurrentSource = CurrentDestination;
    }
    BufferIndex++;
    CurrentSourceStart += sizeof(TemplateClass);
    CurrentDestinationStart += sizeof(TemplateClass);
  }
}

// Raw move up function
// Valid only when SourceStart <= SourceEnd, SourceStart < DestinationStart
void _MemoryShiftUpRaw(size_t SourceStart, size_t SourceEnd,
                       size_t DestinationStart) {
  auto StepForward = DestinationStart - SourceStart;
  auto StepBack = SourceEnd - SourceStart + 1;

  auto BufferSizeLeft = GCD(StepForward, StepBack);

  auto CurrentSourceStart = SourceStart;
  auto CurrentDestinationStart = DestinationStart;
  _MemoryShiftUpWithBufferRaw<size_t>(CurrentSourceStart, SourceEnd,
                                      CurrentDestinationStart, StepForward,
                                      StepBack, BufferSizeLeft);
  if constexpr (sizeof(size_t) > sizeof(uint64_t)) {
    _MemoryShiftUpWithBufferRaw<uint64_t>(CurrentSourceStart, SourceEnd,
                                          CurrentDestinationStart, StepForward,
                                          StepBack, BufferSizeLeft);
  }
  if constexpr (sizeof(size_t) > sizeof(uint32_t)) {
    _MemoryShiftUpWithBufferRaw<uint32_t>(CurrentSourceStart, SourceEnd,
                                          CurrentDestinationStart, StepForward,
                                          StepBack, BufferSizeLeft);
  }
  if constexpr (sizeof(size_t) > sizeof(uint16_t)) {
    _MemoryShiftUpWithBufferRaw<uint16_t>(CurrentSourceStart, SourceEnd,
                                          CurrentDestinationStart, StepForward,
                                          StepBack, BufferSizeLeft);
  }
  if constexpr (sizeof(size_t) > sizeof(uint8_t)) {
    _MemoryShiftUpWithBufferRaw<uint8_t>(CurrentSourceStart, SourceEnd,
                                         CurrentDestinationStart, StepForward,
                                         StepBack, BufferSizeLeft);
  }
}

bool Memory_range_type::Shift_exchange(Range_of_size Source,
                                       Range_of_size Destination) {
  auto Result =
      Range().Does_contain(Source) && Range().Does_contain(Destination) &&
      (Source.Relative_end().Value() == Destination.Relative_end().Value()) &&
      (Source.Start().Value() != Destination.Start().Value());
  if (Result) {
    if (Source.Start().Value() < Destination.Start().Value()) {
      _MemoryShiftUpRaw(Source.Start(), Source.End(), Destination.Start());
    } else {
      // Convert shift down to shift up
      _MemoryShiftUpRaw(Destination.Start(), Source.Start() - 1,
                        Destination.End() + 1);
    }
  }
  return Result;
}

#endif
