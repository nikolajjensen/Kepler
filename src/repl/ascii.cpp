//
// Copyright 2023 Nikolaj Banke Jensen.
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

#include "ascii.h"

std::string kepler::tui::reset_modifier() {
    return _esc + "[" + std::to_string(reset) + "m";
}

std::string kepler::tui::modifier(std::initializer_list<int> effects) {
    std::string result = _esc + "[";
    for(const auto& effect : effects) {
        result += std::to_string(effect);
        result += ";";
    }
    if(result.back() == ';') {
        result.pop_back();
    }
    result += "m";
    return result;
}

std::string kepler::tui::apply(std::string input, std::initializer_list<int> effects) {
    std::string result = modifier(effects);
    result += input;
    result += reset_modifier();
    return result;
}