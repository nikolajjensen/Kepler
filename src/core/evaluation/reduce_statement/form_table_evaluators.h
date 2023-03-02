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
#include "core/error.h"
#include "core/constants/literals.h"
#include "core/evaluation/numeric.h"
#include <numeric>

namespace kepler::form_table::evaluators {
    using return_type = boost::variant<Number, Char, Array>;

    struct evaluator : boost::static_visitor<return_type> {
        kepler::Session* session;

        explicit evaluator(kepler::Session* session_) : session(session_) {}

        virtual return_type operator()() {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments (no argument).");
        }

        virtual Number operator()(const Number& arg) {
            throw kepler::error(InternalError, "Evaluator called with unsupported argument: Number.");
        }

        virtual Char operator()(const Char& arg) {
            throw kepler::error(InternalError, "Evaluator called with unsupported argument: Char.");
        }

        virtual Array operator()(const Array& arg) {
            throw kepler::error(InternalError, "Evaluator called with unsupported argument: Array.");
        }

        virtual Number operator()(const Number&, const Number&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Number and Number.");
        }

        virtual Number operator()(const Number&, const Char&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Number and Char.");
        }

        virtual Number operator()(const Number&, const Array&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Number and Array.");
        }

        virtual Char operator()(const Char&, const Number&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Char and Number.");
        }

        virtual Char operator()(const Char&, const Char&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Char and Char.");
        }

        virtual Char operator()(const Char&, const Array&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Char and Array.");
        }

        virtual Array operator()(const Array&, const Number&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Char and Number.");
        }

        virtual Array operator()(const Array&, const Char&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Char and Char.");
        }

        virtual Array operator()(const Array&, const Array&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Char and Array.");
        }

        virtual Array operator()(const Token&, const Array&) {
            throw kepler::error(InternalError, "Evaluator called with unsupported arguments: Char and Array.");
        }
    };

    ///////////////////////////////////////////////////////
    /// Monadic scalar functions
    ///////////////////////////////////////////////////////

    struct conjugate : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            return conj(num);
        }
    };

    struct negative : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            return Number(0) - num;
        }
    };

    struct direction : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            return (num == 0.0) ? num : num / abs(num);
        }
    };

    struct reciprocal : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            if(num == 0.0) {
                throw kepler::error(DomainError, "Reciprocal of 0.");
            }
            return Number(1) / num;
        }
    };

    struct floor : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            Array& ct = session->get_system_parameter(constants::CT);
            auto& comp_tol = ct.get_content<Number>();

            if(algorithms::integral_within(num, comp_tol)) {
                return {std::round(num.real()), std::round(num.imag())};
            }

            return {std::floor(num.real()), std::floor(num.imag())};
        }
    };

    struct ceiling : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            return {std::ceil(num.real()), std::ceil(num.imag())};
        }
    };

    struct exponential : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            return exp(num);
        }
    };

    struct natural_log : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            if(num == 0.0) {
                throw kepler::error(DomainError, "Natural logarithm of 0.");
            }
            return log(num);
        }
    };

    struct magnitude : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            return abs(num);
        }
    };

    struct factorial : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            if(num.imag() != 0.0) throw kepler::error(DomainError, "Cannot take factorial of complex number.");
            if(num.real() < 0.0 && round(num.real()) == num.real()) throw kepler::error(DomainError, "Cannot take factorial of negative integer.");
            return lgamma(num.real());
        }
    };

    struct pi_times : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            return num * M_PI;
        }
    };

    struct negation : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& num) override {
            auto rounded = round(num.real());
            if(rounded != 0.0 && rounded != 1.0) throw kepler::error(DomainError, "Not near boolean");
            return rounded == 1.0 ? 0.0 : 1.0;
        }
    };


    ///////////////////////////////////////////////////////
    /// Dyadic scalar functions
    ///////////////////////////////////////////////////////

    struct plus : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs + rhs;
        }
    };

    struct minus : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs - rhs;
        }
    };

    struct times : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct divide : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            if(rhs == 0.0) {
                throw kepler::error(DomainError, "Dividing by 0.");
            }
            return lhs / rhs;
        }
    };

    struct maximum : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return std::max(lhs.real(), rhs.real());
        }
    };

    struct minimum : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return std::min(lhs.real(), rhs.real());
        }
    };

    struct power : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
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
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            if(lhs == rhs) return {1};
            if(rhs == 1.0) throw kepler::error(DomainError, "Log of base 1 undefined.");
            auto log_eval = natural_log(session);
            return log_eval(rhs) / log_eval(lhs);
        }
    };

    struct residue : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct binomial : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct circular_functions : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct and_lcm : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct or_gcd : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct nand : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct nor : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct equal : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct less_than : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct less_than_or_equal_to : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct not_equal : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct greater_than_or_equal_to : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    struct greater_than : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            return lhs * rhs;
        }
    };

    ///////////////////////////////////////////////////////
    /// Monadic array functions
    ///////////////////////////////////////////////////////

    struct ravel : evaluator {
        using evaluator::evaluator;

        Array operator()(const Array& arr) override {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct shape : evaluator {
        using evaluator::evaluator;

        Array operator()(const Array& arr) override {
            List<Number> ravel;
            ravel.reserve(arr.ravel_list.size());
            for(auto& dim : arr.shape_list) {
                ravel.emplace_back(dim);
            }
            return Array::vectorOf(std::move(ravel));
        }
    };

    struct index_generator : evaluator {
        using evaluator::evaluator;

        Array operator()(const Array& arr) override {
            Array index_origin = session->get_system_parameter(constants::IO);
            Number io_number = index_origin.get_content<Number>(0);

            if(arr.rank() > 1) throw kepler::error(RankError, "Invalid argument.");
            if(arr.count() != 1) throw kepler::error(LengthError, "Invalid argument.");

            const auto& operand = arr.get_content<Number>(0);
            if(!algorithms::near_integer(operand)) throw kepler::error(DomainError, "Accepts only integer operands.");

            Number nearest_int = algorithms::integer_nearest_to(operand);
            if(nearest_int.real() < 0.0) throw kepler::error(DomainError, "Argument must be positive.");
            if(nearest_int == 0.0) {
                return {};
            }

            List<Number> list(nearest_int.real());
            std::iota(list.begin(), list.end(), io_number.real());
            return Array::vectorOf(std::move(list));
        }
    };

    struct table : evaluator {
        using evaluator::evaluator;

        Array operator()(const Array& arr) override {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    ///////////////////////////////////////////////////////
    /// Dyadic array functions
    ///////////////////////////////////////////////////////

    struct reshape : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct join_1 : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    struct join_2 : evaluator {
        using evaluator::evaluator;

        Number operator()(const Number& lhs, const Number& rhs) override {
            throw kepler::error(InternalError, "Not yet implemented.");
        }
    };

    ///////////////////////////////////////////////////////
    /// Operators.
    ///////////////////////////////////////////////////////

    struct reduction : evaluator {
        using evaluator::evaluator;

        Array operator()(const Token& func, const Array& operand) override;
    };

    ///////////////////////////////////////////////////////
    /// System variables.
    ///////////////////////////////////////////////////////

    struct index_origin : evaluator {
        using evaluator::evaluator;
        using evaluator::operator();

        return_type operator()() override {
            auto& symbol = session->active_workspace.symbol_table.lookup(constants::IO);
            return symbol.referentList[0].get_content<Array>();
        }

        Array operator()(const Array& assignment) override {
            if(assignment.rank() > 1) throw kepler::error(RankError, "Rank higher than 1.");
            if(assignment.count() != 1) throw kepler::error(LengthError, "Only accepts one number.");

            Number num = assignment.get_content<Number>(0);
            if(!algorithms::near_integer(num)) throw kepler::error(DomainError, "Only accepts integers.");

            num = integer_nearest_to(num);
            if(num != 0.0 && num != 1.0) throw kepler::error(LimitError, "IO must be either 0 or 1.");

            session->active_workspace.symbol_table.set(constants::IO, {Token{VariableToken, assignment}});

            return assignment;
        }
    };

    struct print_precision : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        return_type operator()() override {
            auto& symbol = session->active_workspace.symbol_table.lookup(constants::PP);
            return symbol.referentList[0].get_content<Array>();
        }

        Array operator()(const Array& assignment) override {
            if(assignment.rank() > 1) throw kepler::error(RankError, "Rank higher than 1.");
            if(assignment.count() != 1) throw kepler::error(LengthError, "Only accepts one number.");

            Number num = assignment.get_content<Number>(0);
            if(!algorithms::near_integer(num)) throw kepler::error(DomainError, "Only accepts integers.");

            num = integer_nearest_to(num);
            if(num.real() < 1.0 || num.real() > numeric_limit_max().real()) throw kepler::error(LimitError, "IO must be either 0 or 1.");

            session->active_workspace.symbol_table.set(constants::PP, {Token{VariableToken, assignment}});
            return assignment;
        }
    };

    struct comparison_tolerance : evaluator {
        using evaluator::operator();
        using evaluator::evaluator;

        return_type operator()() override {
            auto& symbol = session->active_workspace.symbol_table.lookup(constants::CT);
            return symbol.referentList[0].get_content<Array>();
        }

        Array operator()(const Array& assignment) override {
            if(assignment.rank() > 1) throw kepler::error(RankError, "Rank higher than 1.");
            if(assignment.count() != 1) throw kepler::error(LengthError, "Only accepts one number.");

            Number num = assignment.get_content<Number>(0);
            if(num.real() < 0.0) throw kepler::error(DomainError, "CT must be non-negative.");

            session->active_workspace.symbol_table.set(constants::CT, {Token{VariableToken, assignment}});
            return assignment;
        }
    };
};