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
#include <complex>

namespace kepler {
    template<typename T>
    using List = std::vector<T>;

    using Char = char32_t;
    using Double = double;
    using Integer = int;
    using UnsignedInteger = unsigned int;

    using StringUTF8 = std::string;
    using StringUTF32 = std::u32string;
    using Boolean = bool;

    using Number = std::complex<double>;

    Number numeric_limit_max();
    Number numeric_limit_min();

    Number number_from_characters(const List<Char>& list);

    double& apply_scientific_notation(double& input, double& exponent);

    StringUTF8 number_to_string(const Number& num, int precision = -1);

    StringUTF8 double_to_string(const double& num, int precision);
};