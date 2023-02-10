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

#pragma once
#include <string>

namespace kepler::tui {
    const int black = 30;
    const int red = 31;
    const int green = 32;
    const int yellow = 33;
    const int blue = 34;
    const int magenta = 35;
    const int cyan = 36;
    const int white = 37;

    const int black_bg = 40;
    const int red_bg = 41;
    const int green_bg = 42;
    const int yellow_bg = 43;
    const int blue_bg = 44;
    const int magenta_bg = 45;
    const int cyan_bg = 46;
    const int white_bg = 47;

    const int bold = 1;
    const int underline = 4;
    const int inverse = 7;

    const int reset = 0;

    const std::string _esc = "\033";

    std::string modifier(std::initializer_list<int> effects);
    std::string reset_modifier();
    std::string apply(std::string input, std::initializer_list<int> effects);
};