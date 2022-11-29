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

#pragma once
#include <vector>

#include "UnicodeCharacter.h"

class UnicodeString {
private:
    std::vector<UnicodeCharacter> content;

public:
    UnicodeString() = default;
    UnicodeString(std::vector<UnicodeCharacter> &&);
    UnicodeString(std::u32string &&) noexcept;

    std::vector<UnicodeCharacter>::const_iterator begin() const {
        return content.begin();
    }

    std::vector<UnicodeCharacter>::const_iterator end() const {
        return content.end();
    }

    std::vector<UnicodeCharacter>::iterator begin() {
        return content.begin();
    }

    std::vector<UnicodeCharacter>::iterator end() {
        return content.end();
    }

    void clear() {
        content.clear();
    }

    void push_back(UnicodeCharacter c) {
        content.push_back(c);
    }
};
