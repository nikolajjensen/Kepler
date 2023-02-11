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

    ///////////////////////////////////////////////////////
    /// Monadic functions
    ///////////////////////////////////////////////////////

    struct conjugate : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return conj(num);
        }
    };

    struct negative : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return Number(0) - num;
        }
    };

    struct direction : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return (num == 0.0) ? num : num / abs(num);
        }
    };

    struct reciprocal : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            if(num == 0.0) {
                throw kepler::error(DomainError, "Reciprocal of 0.");
            }
            return Number(1) / num;
        }
    };

    struct floor : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct ceiling : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct exponential : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return exp(num);
        }
    };

    struct natural_log : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            if(num == 0.0) {
                throw kepler::error(DomainError, "Natural logarithm of 0.");
            }
            return log(num);
        }
    };

    struct magnitude : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return abs(num);
        }
    };

    struct factorial : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct pi_times : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            return num * M_PI;
        }
    };

    struct negation : evaluator {
        using evaluator::operator();

        Number operator()(Number& num) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };


    ///////////////////////////////////////////////////////
    /// Dyadic functions
    ///////////////////////////////////////////////////////

    struct plus : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs + rhs;
        }
    };

    struct minus : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs - rhs;
        }
    };

    struct times : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
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

    struct maximum : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct minimum : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct power : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            if(lhs == 0.0 && rhs == 0.0) return {1};
            if(lhs == 0.0) {
                if(rhs.real() > 0) {
                    return {0};
                } else {
                    throw kepler::error(DomainError, "Cannot take power.");
                }
            }
            return pow(lhs, rhs);
        }
    };

    struct logarithm : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            if(lhs == rhs) return {1};
            if(rhs == 1.0) throw kepler::error(DomainError, "Log of base 1 undefined.");
            lhs = natural_log()(lhs);
            rhs = natural_log()(rhs);
            return rhs / lhs;
        }
    };

    struct residue : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct binomial : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct circular_functions : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct and_lcm : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct or_gcd : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct nand : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct nor : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct equal : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct less_than : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct less_than_or_equal_to : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct not_equal : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct greater_than_or_equal_to : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
        }
    };

    struct greater_than : evaluator {
        using evaluator::operator();

        Number operator()(Number& lhs, Number& rhs) const {
            return lhs * rhs;
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