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
#include "core/constants/literals.h"
#include "error.h"

#include <limits>
#include <cmath>
#include <iomanip>
#include "uni_algo/conv.h"

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
    auto real_exponent_begin_it = std::find(list.begin(), list.end(), kepler::constants::exponent_marker);
    auto imaginary_scalar_begin_it = std::find(list.begin(), list.end(), kepler::constants::complex_marker);
    auto imaginary_exponent_begin_it = std::find(imaginary_scalar_begin_it, list.end(), kepler::constants::exponent_marker);

    auto real = kepler::StringUTF32(list.begin(), real_exponent_begin_it);
    if (real.front() == kepler::constants::overbar) {
        real.front() = U'-';
    }
    double real_scalar = std::stod(uni::utf32to8(real));
    double imaginary_scalar = 0;

    if(real_exponent_begin_it != list.end()) {
        auto exponent = kepler::StringUTF32(real_exponent_begin_it + 1, imaginary_scalar_begin_it);
        if (exponent.front() == kepler::constants::overbar) {
            exponent.front() = U'-';
        }
        double real_exponent_scalar = std::stod(uni::utf32to8(kepler::StringUTF32(exponent)));
        kepler::apply_scientific_notation(real_scalar, real_exponent_scalar);
    }

    if(imaginary_scalar_begin_it != list.end()) {
        auto imaginary = kepler::StringUTF32(imaginary_scalar_begin_it + 1, imaginary_exponent_begin_it);
        if (imaginary.front() == kepler::constants::overbar) {
            imaginary.front() = U'-';
        }
        imaginary_scalar = std::stod(uni::utf32to8(imaginary));

        if(imaginary_exponent_begin_it != list.end()) {
            auto imag_str = kepler::StringUTF32(imaginary_exponent_begin_it + 1, list.end());
            if (imag_str.front() == kepler::constants::overbar) {
                imag_str.front() = U'-';
            }
            double imaginary_exponent_scalar = std::stod(uni::utf32to8(kepler::StringUTF32(imag_str)));
            kepler::apply_scientific_notation(imaginary_scalar, imaginary_exponent_scalar);
        }
    }

    return {real_scalar, imaginary_scalar};
}

kepler::StringUTF8 kepler::double_to_string(const double& num, int precision) {
    std::stringstream ss;
    if(precision != -1) {
        ss << std::setprecision(precision);
    }
    ss << num;
    std::string raw = ss.str();

    auto dot_index = raw.find_first_of('.');
    auto trail_index = raw.find_last_not_of('0');
    if(dot_index != std::string::npos && trail_index != std::string::npos && dot_index != trail_index) {
        trail_index++;
        raw = raw.erase(std::min(trail_index, raw.size()));
    }
    return raw;
}

kepler::StringUTF8 kepler::number_to_string(const kepler::Number& num, int precision) {
    StringUTF32 result = uni::utf8to32u(kepler::double_to_string(num.real(), precision));
    if(result.front() == U'-') {
        result.front() = constants::overbar;
    }


    if(num.imag() != 0) {
        StringUTF32 str = uni::utf8to32u(kepler::double_to_string(num.imag(), precision));
        if(str.front() == U'-') {
            str.front() = constants::overbar;
        }
        result = result + StringUTF32(1, constants::complex_marker) + str;
    }

    return uni::utf32to8(result);
}

kepler::Number kepler::integer_nearest_to(const Number &num) {
    if(num.imag() != 0) throw kepler::error(DomainError, "Integer closest to complex number is undefined.");
    return round(num.real());
}