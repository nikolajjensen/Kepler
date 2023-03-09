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

#include "algorithms.h"
#include "core/error.h"
#include <cmath>
#include <numeric>

//https://www.jsoftware.com/papers/eem/complexfloor1.htm#0
kepler::Number kepler::floor(const Number &number) {
    Number raw = {std::floor(number.real()), std::floor(number.imag())};

    double integral;
    double fractional_real = std::modf(number.real(), &integral);
    double fractional_imag = std::modf(number.imag(), &integral);

    if (1.0 > (fractional_imag + fractional_real)) {
        return raw;
    } else if ((1.0 <= (fractional_imag + fractional_real)) && fractional_real >= fractional_imag) {
        return raw + 1.0;
    } else if ((1.0 <= (fractional_imag + fractional_real)) && fractional_real < fractional_imag) {
        return raw + Number(0, 1);
    } else {
        throw kepler::error(InternalError, "Unexpected case reached in floor of number.");
    }
}