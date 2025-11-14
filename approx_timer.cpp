
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

#ifndef APPROXTIMER_CPP
#define APPROXTIMER_CPP

#include "approx_timer.h"

#ifndef ARDUINO
unsigned long
millis()
{
  static const auto Start_time = std::chrono::steady_clock::now();
  auto Current_time = std::chrono::steady_clock::now();
  return std::chrono::duration_cast<std::chrono::milliseconds>(Current_time -
                                                               Start_time)
    .count();
}
#endif

Approximate_timer::Approximate_timer()
  : _Running(false)
  , _Passed()
  , _Start_time(0)
  , _Delay(1)
{
}

Approximate_timer::Approximate_timer(const unsigned long& New_delay)
  : _Running(false)
  , _Passed()
  , _Start_time(0)
  , _Delay(New_delay)
{
}

Approximate_timer::~Approximate_timer() {}

bool
Approximate_timer::Start()
{
  auto Result = false;
  if (!_Running) {
    _Start_time = millis();
    _Running = true;
    _Passed(false, 0);
    Result = true;
  }
  return Result;
}

bool
Approximate_timer::Finish()
{
  Passed();
  if (_Running) {
    if (_Passed.Valid()) {
      _Running = false;
    }
    return _Passed.Valid();
  } else {
    //_Passed(false, 0);
    return false;
  }
}

void
Approximate_timer::Reset()
{
  _Running = false;
  _Passed(false, 0);
}

bool
Approximate_timer::Running() const
{
  return _Running;
}

bool
Approximate_timer::operator()()
{
  Start();
  return Finish();
}

void
Approximate_timer::Restart(const bool& If_running)
{
  if (_Running || (!If_running)) {
    Reset();
    Start();
  }
}

unsigned long
Approximate_timer::Delay() const
{
  return _Delay;
}

void
Approximate_timer::Delay(const unsigned long& New_delay)
{
  _Delay = New_delay;
}

Approximate_timer::
operator Weighted_float() const
{
  return Seconds_passed();
}

Weighted_time
Approximate_timer::Passed()
{
  unsigned long Time = millis();
  if (Time >= _Start_time) {
      _Passed.Value() = Time - _Start_time;
    } else {
      _Passed.Value() =
          (std::numeric_limits<unsigned long>::max() - _Start_time) + Time;
    }
  _Passed.Weight() = _Passed.Value() >= _Delay;
  return _Passed;
}

Weighted_float
Approximate_timer::Seconds_passed() const
{
  return static_cast<Weighted_float>(_Passed.Value() / 1000.f);
}

#endif
