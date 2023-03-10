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

#include "monadic_operators.h"

#include <utility>
#include "core/error.h"
#include <memory>

namespace kepler {
    MonadicOp::MonadicOp(Operation_ptr op_) : op(std::move(op_)), Operation(nullptr) {}
    MonadicOp::MonadicOp(Operation* op_) : op(op_), Operation(nullptr) {}

    Array Commute::operator()(const Array& alpha, const Array& omega) {
        return (*op)(omega, alpha);
    }

    Array Commute::operator()(const Array& omega) {
        return (*op)(omega, omega);
    }

    Array Slash::operator()(const Array& alpha, const Array& omega) {
        throw kepler::error(InternalError, "Dyadic SLASH is not implemented.");
    }

    Array Slash::operator()(const Array& omega) {
        if(omega.size() < 2) {
            return omega;
        }

        Array acc = get<Array>(omega.data.back());
        for(int i = omega.size() - 2; i >= 0; --i) {
            acc = (*op)(get<Array>(omega.data[i]), acc);
        }
        return acc;
    }
};