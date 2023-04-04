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
#include "core/datatypes.h"
#include "core/array.h"

namespace kepler {
    Number floor(const Number& number);
    Number binomial(const Number& alpha, const Number& omega);

    Array partitioned_enclose(const Array& partitioning, const Array& subject);
    Array partitioned_enclose(const Array& partitioning, const std::u32string& subject);

    Array without(const Array& alpha, const Array& omega);
    Array without(const std::u32string& alpha, const std::u32string& omega);

    Array rho(const Array& alpha, const Array& omega);
};