//
// Copyright 2022 Nikolaj Banke Jensen.
//
// This file is part of Kepler.
// 
// Kepler is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Kepler is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with Kepler. If not, see <https://www.gnu.org/licenses/>.
//

#include "Character.h"
#include <ostream>
#include <uni_algo/conv.h>
/*
Character::Character(std::vector<std::u32string> && _representations) : representations(_representations) {}

std::ostream& operator<<(std::ostream &os, const Character &c) {
    os << "Character(";
    for(size_t i = 0; i < c.representations.size(); ++i) {
        os << uni::utf32to8(c.representations[i]);
        if(i < c.representations.size() - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}*/