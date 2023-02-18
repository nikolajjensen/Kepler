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
        kepler::Session* session;

        explicit evaluator(kepler::Session* session_) : session(session_) {}

        template <typename T>
        T operator()(const T& arg) {
            throw kepler::error(InternalError, "Evaluator called with unsupported argument.");
        }

        template <typename T, typename U>
        T operator()(const T& lhs, const U&rhs) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments.");
        }
    };

    ///////////////////////////////////////////////////////
    /// Monadic scalar functions
    ///////////////////////////////////////////////////////

    struct conjugate : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            return conj(num);
        }
    };

    struct negative : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            return Number(0) - num;
        }
    };

    struct direction : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            return (num == 0.0) ? num : num / abs(num);
        }
    };

    struct reciprocal : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            if(num == 0.0) {
                throw kepler::error(DomainError, "Reciprocal of 0.");
            }
            return Number(1) / num;
        }
    };

    struct floor : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct ceiling : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct exponential : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            return exp(num);
        }
    };

    struct natural_log : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            if(num == 0.0) {
                throw kepler::error(DomainError, "Natural logarithm of 0.");
            }
            return log(num);
        }
    };

    struct magnitude : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            return abs(num);
        }
    };

    struct factorial : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct pi_times : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            return num * M_PI;
        }
    };

    struct negation : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };


    ///////////////////////////////////////////////////////
    /// Dyadic scalar functions
    ///////////////////////////////////////////////////////

    struct plus : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs + rhs;
        }
    };

    struct minus : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs - rhs;
        }
    };

    struct times : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct divide : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            if(rhs == 0.0) {
                throw kepler::error(DomainError, "Dividing by 0.");
            }
            return lhs / rhs;
        }
    };

    struct maximum : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct minimum : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct power : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
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
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            if(lhs == rhs) return {1};
            if(rhs == 1.0) throw kepler::error(DomainError, "Log of base 1 undefined.");
            auto log_eval = natural_log(session);
            return log_eval(rhs) / log_eval(lhs);
        }
    };

    struct residue : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct binomial : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct circular_functions : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct and_lcm : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct or_gcd : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct nand : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct nor : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct equal : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct less_than : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct less_than_or_equal_to : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct not_equal : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct greater_than_or_equal_to : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    struct greater_than : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            return lhs * rhs;
        }
    };

    ///////////////////////////////////////////////////////
    /// Monadic array functions
    ///////////////////////////////////////////////////////

    struct ravel : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Array operator()(const Array& arr) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct shape : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Array operator()(const Array& arr) {
            List<Number> ravel;
            ravel.reserve(arr.ravelList.size());
            for(auto& dim : arr.shapeList) {
                ravel.emplace_back(dim);
            }
            return Array::vectorOf(std::move(ravel));
        }
    };

    struct index_generator : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Array operator()(const Array& arr) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct table : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Array operator()(Array& arr) const {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    ///////////////////////////////////////////////////////
    /// Dyadic array functions
    ///////////////////////////////////////////////////////

    struct reshape : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct join_1 : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct join_2 : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };
    ///////////////////////////////////////////////////////
    /// System variables.
    ///////////////////////////////////////////////////////

    struct index_origin : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Token operator()() {
            auto& symbol = session->active_workspace.symbol_table.lookup(distinguished_identifiers::IO);
            return {ConstantToken, symbol.referentList[0].get_content<Array>()};
        }

        Token operator()(const Token& assignment) {
            auto guarded_assignment = assignment;
            auto arr = guarded_assignment.get_content<Array>();

            if(arr.rank() > 1) throw kepler::error(RankError, "Rank higher than 1.");
            if(arr.count() != 1) throw kepler::error(LengthError, "Only accepts one number.");

            auto& num = arr.get_content<Number>(0);
            if(!classifiers::is_near_integer(num, *session)) throw kepler::error(DomainError, "Only accepts integers.");

            num = integer_nearest_to(num);
            if(num != 0.0 && num != 1.0) throw kepler::error(LimitError, "IO must be either 0 or 1.");

            session->active_workspace.symbol_table.set(distinguished_identifiers::IO, {guarded_assignment});
            return {CommittedValueToken, assignment.content.get()};
        }
    };

    struct print_precision : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Token operator()() {
            auto& symbol = session->active_workspace.symbol_table.lookup(distinguished_identifiers::PP);
            return {ConstantToken, symbol.referentList[0].get_content<Array>()};
        }

        Token operator()(const Token& assignment) {
            auto guarded_assignment = assignment;
            auto arr = guarded_assignment.get_content<Array>();

            if(arr.rank() > 1) throw kepler::error(RankError, "Rank higher than 1.");
            if(arr.count() != 1) throw kepler::error(LengthError, "Only accepts one number.");

            auto& num = arr.get_content<Number>(0);
            if(!classifiers::is_near_integer(num, *session)) throw kepler::error(DomainError, "Only accepts integers.");

            num = integer_nearest_to(num);
            if(num.real() < 1.0 || num.real() > numeric_limit_max().real()) throw kepler::error(LimitError, "IO must be either 0 or 1.");

            session->active_workspace.symbol_table.set(distinguished_identifiers::PP, {guarded_assignment});
            return {CommittedValueToken, assignment.content.get()};
        }
    };
};