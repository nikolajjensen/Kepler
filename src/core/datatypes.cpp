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

kepler::Number::Number(const List<Char>& list) {
    auto exponent_it = std::find(list.begin(), list.end(), characters::exponent_marker);
    auto complex_it = std::find(list.begin(), list.end(), characters::complex_marker);

    auto real_scalar_end_it = (exponent_it != list.end()) ? exponent_it : (complex_it != list.end()) ? complex_it : list.end();
    auto exponent_end_it = (complex_it != list.end()) ? complex_it : list.end();
    auto complex_end_it = list.end();

    realScalar = std::stod(uni::utf32to8(StringUTF32(list.begin(), real_scalar_end_it)));

    if(exponent_it != list.end()) {
        auto str = StringUTF32(exponent_it + 1, exponent_end_it);
        if (str.front() == characters::overbar) {
            str.front() = U'-';
        }
        exponent = std::stod(uni::utf32to8(StringUTF32(exponent_it + 1, exponent_end_it)));
    }

    if(complex_it != list.end()) {
        auto str = StringUTF32(complex_it + 1, complex_end_it);
        if (str.front() == characters::overbar) {
            str.front() = U'-';
        }
        imaginaryScalar = std::stod(uni::utf32to8(str));
    }
}

kepler::Number::Number(const double realScalar_,
                       const boost::optional<double> exponent_,
                       const boost::optional<double> imaginaryScalar_)
        : realScalar(realScalar_),
          exponent(exponent_),
          imaginaryScalar(imaginaryScalar_) {}

kepler::Number& kepler::Number::operator=(const double& num) {
    realScalar = num;
    return *this;
}

kepler::StringUTF8 kepler::Number::to_string() const {
    std::stringstream ss;

    ss << std::to_string(realScalar);

    if(exponent) {
        StringUTF32 str = uni::utf8to32u(std::to_string(exponent.get()));
        if(str.front() == U'-') {
            str.front() = characters::overbar;
        }
        ss << uni::utf32to8(StringUTF32(1, characters::exponent_marker)) << uni::utf32to8(str);
    }
    if(imaginaryScalar) {
        StringUTF32 str = uni::utf8to32u(std::to_string(imaginaryScalar.get()));
        if(str.front() == U'-') {
            str.front() = characters::overbar;
        }
        ss << uni::utf32to8(StringUTF32(1, characters::complex_marker)) << uni::utf32to8(str);
    }

    return ss.str();
}