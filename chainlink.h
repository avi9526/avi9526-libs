
//    Copyright (C) 2025
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

#ifndef Chainlink_H
#define Chainlink_H

#include "common.h"
#include "validbase.h"
#include "weighted.h"

class Chain_link : public Valid_base
{
public:
  using Link_pointer = Weighted_type<Chain_link*, bool>;
  using Parent_type = Valid_base;

  static void Create(Chain_link& Connect_to);
  static void CreateLast(Chain_link& Connect_to);

  Chain_link();
  virtual ~Chain_link() override;

  // Templates defined in chainlink.tpp
  template<class Functor>
  void For_each(Functor F);

  template<class Functor>
  void For_each_down(Functor F);

  template<class Child_class>
  static Weighted_type<Child_class*, bool> As_child_of_class(
    const Link_pointer& Link);

  template<class Child_class>
  Weighted_type<Child_class*, bool> As_child_of_class();

  virtual bool Valid() const override;
  virtual void Reset() override;

  void Connect(Chain_link& L);
  void Connect_last(Chain_link& L);
  void Disconnect();
  void Disconnect_eject();
  void Disconnect_uplink();
  void Disconnect_downlink();

  const Link_pointer& Uplink() const;
  const Link_pointer& Downlink() const;

  Link_pointer Get_first();
  Link_pointer Get_last();

protected:
  void Uplink(const Link_pointer& New_uplink);
  void Downlink(const Link_pointer& New_downlink);

  void Forget_uplink();
  void Forget_downlink();

  void Suicidal(const bool& New_suicidal = true);
  void Suicide_if_abandoned();

private:
  Link_pointer _Up;
  Link_pointer _Down;
  bool _Suicidal;
};

#include "chainlink.tpp"

#endif
