
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


#ifndef LOOP_BREAKER_HPP
#define LOOP_BREAKER_HPP

#include <iostream>
#include <string>

class Loop_breaker {
private:
    std::string _Type_name = "Loop_breaker";

public:
    // Constructor
    Loop_breaker();

    // Virtual Destructor
    virtual ~Loop_breaker();

    // Copy Constructor
    Loop_breaker(const Loop_breaker& Other);

    // Move Constructor
    Loop_breaker(Loop_breaker&& Other) noexcept;

    // Copy Assignment Operator
    Loop_breaker& operator=(Loop_breaker const& Other);

    // Move Assignment Operator
    Loop_breaker& operator=(Loop_breaker&& Other) noexcept;

    // Get Type Name
    std::string Type_name() const {
        return _Type_name;
    }
};

#endif // LOOP_BREAKER_HPP
