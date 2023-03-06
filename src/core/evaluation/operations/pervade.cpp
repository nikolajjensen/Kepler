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

#include "pervade.h"
#include "core/error.h"

namespace kepler {
    Array Pervade::operator()(Array omega) {
        if (!is_configured()) throw kepler::error(InternalError, "Not configured.");

        if (!omega.is_simple_scalar()) {
            for (auto &element: omega.data) {
                element = apply(element);
            }
        } else if (omega.is_simple_scalar()) {
            omega = Array{{}, {apply(omega.data[0])}};
        }
        return omega;
    }

    Array Pervade::operator()(Array alpha, Array omega) {
        if (!is_configured()) throw kepler::error(InternalError, "Not configured.");

        Array tmp = alpha;

        if (!alpha.is_simple_scalar() && !omega.is_simple_scalar()) {

            if (alpha.shape != omega.shape) {
                throw kepler::error(SyntaxError, "Mismatched left and right shapes.");
            }

            tmp.data.resize(alpha.data.size());
            tmp.shape = alpha.shape;
            for (int i = 0; i < alpha.data.size(); ++i) {
                tmp.data[i] = apply(alpha.data[i], omega.data[i]);
            }

        } else if (alpha.is_simple_scalar() && omega.is_simple_scalar()) {
            tmp.shape = alpha.shape;
            tmp.data = {apply(alpha.data[0], omega.data[0])};

        } else if (!alpha.is_simple_scalar() && omega.is_simple_scalar()) {
            tmp.shape = alpha.shape;
            tmp.data.resize(alpha.data.size());

            for (int i = 0; i < alpha.data.size(); ++i) {
                tmp.data[i] = (*this)(get<Array>(alpha.data[i]), omega);
            }

        } else if (alpha.is_simple_scalar() && !omega.is_simple_scalar()) {
            tmp.shape = omega.shape;
            tmp.data.resize(omega.data.size());

            for (int i = 0; i < omega.data.size(); ++i) {
                tmp.data[i] = (*this)(alpha, get<Array>(omega.data[i]));
            }
        }

        return tmp;
    }

    Array::element_type Pervade::apply(Array::element_type& omega) {
        if(holds_alternative<Number>(omega)) {
            return (*op)(get<Number>(omega));
        } else if(holds_alternative<std::u32string>(omega)) {
            return (*op)(get<std::u32string>(omega));
        } else if(holds_alternative<Array>(omega)) {
            return (*this)(get<Array>(omega));
        }

        throw kepler::error(DomainError, "Unsupported operand types.");
    }

    // Ugly, but needs to be compile-time deducible.
    Array::element_type Pervade::apply(Array::element_type& alpha, Array::element_type& omega) {
        if(std::holds_alternative<Number>(alpha)) {
            if(holds_alternative<Number>(omega)) {
                return (*op)(get<Number>(alpha), get<Number>(omega));
            } else if(holds_alternative<std::u32string>(omega)) {
                //return (*op)(get<Number>(alpha), get<Char>(omega));
            } else if(std::holds_alternative<Array>(omega)) {

            }
        } else if(holds_alternative<std::u32string>(alpha)) {
            if(holds_alternative<Number>(omega)) {
                //return (*op)(get<Char>(alpha), get<Number>(omega));
            } else if(holds_alternative<std::u32string>(omega)) {
                return (*op)(get<std::u32string>(alpha), get<std::u32string>(omega));
            }
        }

        if(std::holds_alternative<Array>(alpha) && std::holds_alternative<Array>(omega)) {
            return (*this)(get<Array>(alpha), get<Array>(omega));
        }

        throw kepler::error(DomainError, "Unsupported operand types.");
    }
};