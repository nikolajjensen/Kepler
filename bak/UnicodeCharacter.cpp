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

#include "UnicodeCharacter.h"
#include <ostream>
#include "uni_algo/conv.h"

UnicodeCharacter::UnicodeCharacter(std::vector<Char> && _representations) : representations(_representations) {}
UnicodeCharacter::UnicodeCharacter(const Char & representation_) : representations({representation_}) {}

std::ostream& operator<<(std::ostream &os, const UnicodeCharacter &c) {
    os << "Character(";
    for(size_t i = 0; i < c.representations.size(); ++i) {
        os << uni::utf32to8(std::u32string(1, c.representations[i]));
        if(i < c.representations.size() - 1) {
            os << ", ";
        }
    }
    os << ")";
    return os;
}

bool operator==(const Char& first, const UnicodeCharacter& second) {
    return std::find(second.representations.begin(), second.representations.end(), first) != second.representations.end();
}

bool operator==(const UnicodeCharacter& first, const Char& second) {
    return std::find(first.representations.begin(), first.representations.end(), second) != first.representations.end();
}

bool operator==(const UnicodeCharacter& first, const UnicodeCharacter& second) {
    auto it = first.representations.begin();
    bool match = false;

    while(!match && it != first.representations.end()) {
        match = std::find(second.representations.begin(), second.representations.end(), *it) != second.representations.end();
        it++;
    }

    return match;
}