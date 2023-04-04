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
#include "core/literals.h"
#include <cmath>
#include <iomanip>
#include "uni_algo/conv.h"

kepler::StringUTF8 kepler::double_to_string(const double& num, int precision) {
    std::stringstream ss;
    ss << std::setprecision(precision);
    ss << num;

    std::string raw = ss.str();

    if(!raw.empty() && raw.front() == '-') {
        raw.erase(0, 1);
        if(raw != "0") {
            raw.insert(0, "¯");
        }
    }

    auto e_index = raw.find_first_of('e');
    if(e_index != std::string::npos) {
        auto mantissa_string = raw.substr(e_index + 1);
        raw.erase(e_index);

        int mantissa = std::stoi(mantissa_string);

        if(mantissa > 0 && mantissa < precision) {
            raw += std::string(mantissa, '0');
        } else if(mantissa < 0 && -mantissa < precision - 3) {
            raw = "0." + std::string(abs(mantissa) - 1, '0') + raw;
        } else {
            bool negative_mantissa = mantissa_string.front() == '-';
            mantissa_string.erase(0, 1);

            mantissa_string.erase(0, std::min(mantissa_string.find_first_not_of('0'), mantissa_string.size()-1));

            if(negative_mantissa && mantissa_string != "0") {
                mantissa_string.insert(0, "¯");
            }

            raw += "E" + mantissa_string;
        }
    }

    return raw;
}

kepler::StringUTF8 kepler::number_to_string(const kepler::Number& num, int precision) {
    String result = uni::utf8to32u(kepler::double_to_string(num.real(), precision));

    if(num.imag() != 0) {
        result = result + String(1, constants::complex_marker) + uni::utf8to32u(kepler::double_to_string(num.imag(), precision));
    }

    return uni::utf32to8(result);
}