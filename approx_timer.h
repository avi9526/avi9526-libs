
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

#ifndef APPROXTIMER_H
#define APPROXTIMER_H

#include "common.h"
#include "weighted.h"

#ifdef ARDUINO
# include <Arduino.h>
#else
# include <chrono>

unsigned long millis();

#endif

typedef Weighted_type<unsigned long, bool> Weighted_time;

// Non-precise timer
class Approximate_timer
{
public:
  Approximate_timer();
  Approximate_timer(const unsigned long& New_delay);
  virtual ~Approximate_timer();

  virtual bool Start();
  virtual bool Finish();
  virtual void Reset();
  virtual bool Running() const;
  virtual void Restart(const bool& If_running = false);

  virtual bool operator()();

  virtual unsigned long Delay() const;
  virtual void Delay(const unsigned long& New_delay);

  virtual operator Weighted_float() const;

  virtual Weighted_time Passed();

  virtual Weighted_float Seconds_passed() const;

private:
  bool _Running;
  Weighted_time _Passed;
  unsigned long _Start_time;
  unsigned long _Delay;
};

// #include "approxtimer.cpp"

#endif
