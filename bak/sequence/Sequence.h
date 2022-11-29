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
#include <string>

#include "Step.h"
#include "../UnicodeCharacter.h"

template <typename T>
class Sequence {
private:
    std::vector<Step<T> *> steps;
    std::function<void(UnicodeCharacter&)> on_match;

public:
    explicit Sequence(std::vector<Step<T> *> & _steps, std::function<void(UnicodeCharacter&)> on_match_);
    ~Sequence();

    unsigned int match(typename std::vector<T>::iterator& input_cursor, typename std::vector<T>::iterator& input_end);
    //bool match(typename std::vector<T> &input);
};