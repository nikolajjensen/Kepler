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

#include "datatypes.h"
#include "characters.h"

#include <format>
#include <limits>
#include <cmath>

kepler::Number kepler::numeric_limit_max() {
    return std::numeric_limits<double>::max();
}

kepler::Number kepler::numeric_limit_min() {
    return std::numeric_limits<double>::min();
}

double& kepler::apply_scientific_notation(double& input, double& exponent) {
    return input *= pow(10.0, exponent);
}

kepler::Number kepler::number_from_characters(const kepler::List<kepler::Char>& list) {
    // std::find returns the first instance.
    auto real_exponent_begin_it = std::find(list.begin(), list.end(), kepler::characters::exponent_marker);
    auto imaginary_scalar_begin_it = std::find(list.begin(), list.end(), kepler::characters::complex_marker);
    auto imaginary_exponent_begin_it = std::find(imaginary_scalar_begin_it, list.end(), kepler::characters::exponent_marker);

    double real_scalar = std::stod(uni::utf32to8(kepler::StringUTF32(list.begin(), real_exponent_begin_it)));
    double imaginary_scalar = 0;

    if(real_exponent_begin_it != list.end()) {
        auto str = kepler::StringUTF32(real_exponent_begin_it + 1, imaginary_scalar_begin_it);
        if (str.front() == kepler::characters::overbar) {
            str.front() = U'-';
        }
        double exponent = std::stod(uni::utf32to8(kepler::StringUTF32(str)));
        kepler::apply_scientific_notation(real_scalar, exponent);
    }

    if(imaginary_scalar_begin_it != list.end()) {
        auto str = kepler::StringUTF32(imaginary_scalar_begin_it + 1, imaginary_exponent_begin_it);
        if (str.front() == kepler::characters::overbar) {
            str.front() = U'-';
        }
        imaginary_scalar = std::stod(uni::utf32to8(str));

        if(imaginary_exponent_begin_it != list.end()) {
            auto imag_str = kepler::StringUTF32(imaginary_exponent_begin_it + 1, list.end());
            if (imag_str.front() == kepler::characters::overbar) {
                imag_str.front() = U'-';
            }
            double exponent = std::stod(uni::utf32to8(kepler::StringUTF32(imag_str)));
            kepler::apply_scientific_notation(imaginary_scalar, exponent);
        }
    }

    return {real_scalar, imaginary_scalar};
}

kepler::StringUTF8 kepler::double_to_string(const double& num) {
    std::string raw = std::to_string(num);
    auto index = raw.find_last_not_of('0');
    if(raw[index] != '.') {
        index++;
    }
    raw = raw.erase(std::min(index, raw.size() - 1));
    return raw;
}

kepler::StringUTF8 kepler::number_to_string(const kepler::Number& num) {
    StringUTF32 result = uni::utf8to32u(kepler::double_to_string(num.real()));
    if(result.front() == U'-') {
        result.front() = characters::overbar;
    }


    if(num.imag() != 0) {
        StringUTF32 str = uni::utf8to32u(kepler::double_to_string(num.imag()));
        if(str.front() == U'-') {
            str.front() = characters::overbar;
        }
        result = result + StringUTF32(1, characters::complex_marker) + str;
    }

    return uni::utf32to8(result);
}