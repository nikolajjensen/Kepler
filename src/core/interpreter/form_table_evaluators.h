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
#include "form_table.h"
#include "../error/error.h"

namespace kepler::form_table::evaluators {
    struct evaluator : boost::static_visitor<boost::variant<Number, Char, Array>> {
        template <typename T>
        T operator()(T& arg) const {
            throw kepler::error(InternalError, "Evaluator called with unsupported argument.");
        }

        template <typename T, typename U>
        T operator()(T& lhs, U&rhs) const {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments.");
        }
    };


    struct conjugate : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return conj(num);
        }

        Char operator()(Char& ch) const {
            return ch;
        }
    };

    struct negative : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return Number(0) - num;
        }

        Char operator()(Char& ch) const {
            return ch;
        }
    };

    struct direction : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return (num == 0.0) ? num : num / abs(num);
        }

        Char operator()(Char& ch) const {
            return ch;
        }
    };

    struct plus : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs + rhs;
        }
    };

    struct divide : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            if(rhs == 0.0) {
                throw kepler::error(DomainError, "Dividing by 0.");
            }
            return lhs / rhs;
        }
    };

    struct shape : evaluator {
        using evaluator::operator();

        Array operator()(Array& arr) const {
            List<Number> ravel;
            ravel.reserve(arr.ravelList.size());
            for(auto& dim : arr.shapeList) {
                ravel.emplace_back(dim);
            }
            return Array::vectorOf(std::move(ravel));
        }
    };
};