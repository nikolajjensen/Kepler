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

#include "dyadic_operators.h"
#include "monadic_operators.h"

namespace kepler {
    DyadicOp::DyadicOp(Operation_ptr aalpha_, Operation_ptr oomega_) : aalpha(std::move(aalpha_)), oomega(std::move(oomega_)), Operation(
            nullptr) {}

    Array Jot::operator()(const Array &alpha, const Array &omega) {
        return (*aalpha)(alpha, (*oomega)(omega));
    }

    Array Jot::operator()(const Array &omega) {
        return (*aalpha)((*oomega)(omega));
    }

    Array Atop::operator()(const Array &alpha, const Array &omega) {
        return (*aalpha)((*oomega)(alpha, omega));
    }

    Array Atop::operator()(const Array &omega) {
        return (*aalpha)((*oomega)(omega));
    }

    Array Over::operator()(const Array &alpha, const Array &omega) {
        return (*aalpha)((*oomega)(alpha), (*oomega)(omega));
    }

    Array Over::operator()(const Array &omega) {
        return (*aalpha)((*oomega)(omega));
    }

    Array InnerProduct::operator()(const Array &alpha, const Array &omega) {
        Diaeresis diaeresis(oomega);
        Slash slash(aalpha);

        return slash(diaeresis(alpha, omega));
    }
};
