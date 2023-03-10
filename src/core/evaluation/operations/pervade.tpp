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

#include "core/error.h"

namespace kepler {

    template <typename BASE>
    Array PervadeMixin<BASE>::operator()(const Array& omega) {
        if (!omega.is_simple_scalar()) {
            Array tmp = omega;
            for (auto &element: tmp.data) {
                element = apply(element);
            }
            return tmp;
        } else if (omega.is_simple_scalar()) {
            return apply(omega.data[0]);
        }
        return omega;
    }

    template <typename BASE>
    Array PervadeMixin<BASE>::operator()(const Array& alpha, const Array& omega) {
        Array tmp = alpha;

        if (!alpha.is_simple_scalar() && !omega.is_simple_scalar()) {

            if (alpha.shape != omega.shape) {
                throw kepler::error(LengthError, "Mismatched left and right shapes.");
            }

            tmp.data.resize(alpha.data.size());
            tmp.shape = alpha.shape;
            for (int i = 0; i < alpha.data.size(); ++i) {
                tmp.data[i] = apply(alpha.data[i], omega.data[i]);
            }

        } else if (alpha.is_simple_scalar() && omega.is_simple_scalar()) {
            tmp = apply(alpha.data[0], omega.data[0]);

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

    template <typename BASE>
    Array PervadeMixin<BASE>::operator()(const std::u32string &alpha, const std::u32string &omega) {
        Array tmp{{}, {}};

        if (alpha.length() != 1 && omega.length() != 1) {

            if (alpha.length() != omega.length()) {
                throw kepler::error(LengthError, "Mismatched left and right shapes.");
            }

            tmp.data.resize(alpha.length());
            tmp.shape.emplace_back(alpha.length());
            for (int i = 0; i < alpha.length(); ++i) {
                tmp.data[i] = (*this)(alpha[i], omega[i]);
            }

        } else if (alpha.length() == 1 && omega.length() == 1) {
            tmp = apply(alpha[0], omega[0]);

        } else if (alpha.length() != 1 && omega.length() == 1) {
            tmp.shape.emplace_back(alpha.length());
            tmp.data.resize(alpha.length());

            for (int i = 0; i < alpha.length(); ++i) {
                tmp.data[i] = (*this)(alpha[i], omega[0]);
            }

        } else if (alpha.length() == 1 && omega.length() != 1) {
            tmp.shape.emplace_back(omega.length());
            tmp.data.resize(omega.length());

            for (int i = 0; i < omega.length(); ++i) {
                tmp.data[i] = (*this)(alpha[0], omega[i]);
            }

        }

        return tmp;
    }

    template <typename BASE>
    Array PervadeMixin<BASE>::apply(const Array::element_type& omega) {
        return std::visit(*this, omega);
    }

    template <typename BASE>
    Array PervadeMixin<BASE>::apply(const Array::element_type& alpha, const Array::element_type& omega) {
        /*
        if(holds_alternative<Array>(alpha) && holds_alternative<Array>(omega)) {
            return (*this)(get<Array>(alpha), get<Array>(omega));
        }
        */
        return std::visit(*this, alpha, omega);
    }
};