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
#include <cmath>

kepler::Number::Number(const List<Char>& list) {
    // std::find returns the first instance.
    auto real_exponent_begin_it = std::find(list.begin(), list.end(), characters::exponent_marker);
    auto imaginary_scalar_begin_it = std::find(list.begin(), list.end(), characters::complex_marker);
    auto imaginary_exponent_begin_it = std::find(imaginary_scalar_begin_it, list.end(), characters::exponent_marker);

    real_scalar = std::stod(uni::utf32to8(StringUTF32(list.begin(), real_exponent_begin_it)));

    if(real_exponent_begin_it != list.end()) {
        auto str = StringUTF32(real_exponent_begin_it + 1, imaginary_scalar_begin_it);
        if (str.front() == characters::overbar) {
            str.front() = U'-';
        }
        double exponent = std::stod(uni::utf32to8(StringUTF32(str)));
        apply_scientific_notation(real_scalar, exponent);
    }

    if(imaginary_scalar_begin_it != list.end()) {
        auto str = StringUTF32(imaginary_scalar_begin_it + 1, imaginary_exponent_begin_it);
        if (str.front() == characters::overbar) {
            str.front() = U'-';
        }
        imaginary_scalar = std::stod(uni::utf32to8(str));

        if(imaginary_exponent_begin_it != list.end()) {
            auto str = StringUTF32(imaginary_exponent_begin_it + 1, list.end());
            if (str.front() == characters::overbar) {
                str.front() = U'-';
            }
            double exponent = std::stod(uni::utf32to8(StringUTF32(str)));
            apply_scientific_notation((*imaginary_scalar), exponent);
        }
    }
}

kepler::Number::Number(double real_scalar_,
                       boost::optional<double> real_exponent_,
                       boost::optional<double> imaginary_scalar_,
                       boost::optional<double> imaginary_exponent_)
        : real_scalar(real_scalar_),
          imaginary_scalar(imaginary_scalar_) {

    if(real_exponent_) {
        apply_scientific_notation(real_scalar, real_exponent_.get());
    }

    if(imaginary_exponent_ && imaginary_scalar) {
        apply_scientific_notation((*imaginary_scalar), imaginary_exponent_.get());
    }
}

kepler::Number& kepler::Number::operator=(const double& num) {
    real_scalar = num;
    return *this;
}

kepler::StringUTF8 kepler::Number::double_to_string(const double& num) {
    std::string raw = std::to_string(num);
    auto index = raw.find_last_not_of('0');
    if(raw[index] != '.') {
        index++;
    }
    raw = raw.erase(std::min(index, raw.size() - 1));
    return raw;
}

kepler::StringUTF8 kepler::Number::to_string() const {
    StringUTF32 result = uni::utf8to32u(double_to_string(real_scalar));
    if(result.front() == U'-') {
        result.front() = characters::overbar;
    }


    if(imaginary_scalar) {
        StringUTF32 str = uni::utf8to32u(double_to_string(imaginary_scalar.get()));
        if(str.front() == U'-') {
            str.front() = characters::overbar;
        }
        result = result + StringUTF32(1, characters::complex_marker) + str;
    }

    return uni::utf32to8(result);
}