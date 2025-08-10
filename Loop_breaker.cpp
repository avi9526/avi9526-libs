
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


#include "Loop_breaker.hpp"

// Constructor
Loop_breaker::Loop_breaker() : _Type_name("Loop_breaker") {
    std::cout << "Loop_breaker constructed" << std::endl;
}

// Destructor
Loop_breaker::~Loop_breaker() {
    std::cout << "Loop_breaker destroyed" << std::endl;
}

// Copy Constructor
Loop_breaker::Loop_breaker(const Loop_breaker& Other)
    : _Type_name(Other._Type_name) {
    std::cout << "Loop_breaker copied" << std::endl;
}

// Move Constructor
Loop_breaker::Loop_breaker(Loop_breaker&& Other) noexcept
    : _Type_name(std::move(Other._Type_name)) {
    std::cout << "Loop_breaker moved" << std::endl;
}

// Copy Assignment Operator
Loop_breaker& Loop_breaker::operator=(Loop_breaker const& Other) {
    if (this != &Other) {
        _Type_name = Other._Type_name;
    }
    std::cout << "Loop_breaker copy assigned" << std::endl;
    return *this;
}

// Move Assignment Operator
Loop_breaker& Loop_breaker::operator=(Loop_breaker&& Other) noexcept {
    if (this != &Other) {
        _Type_name = std::move(Other._Type_name);
    }
    std::cout << "Loop_breaker move assigned" << std::endl;
    return *this;
}
