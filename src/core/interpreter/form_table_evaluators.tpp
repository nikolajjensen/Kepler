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
#include "form_table.h"
#include "../classifiers.h"
#include "../exceptions/error.h"

namespace kepler::form_table {
    template<>
    kepler::Token evaluators::call_defined_function<patterns::niladic, patterns::niladic_cdf>(evaluator_input &&input) {
        return kepler::Token();
    }

    template<>
    kepler::Token evaluators::call_defined_function<patterns::monadic, patterns::monadic_cdf>(evaluator_input &&input) {
        return kepler::Token();
    }

    template<>
    kepler::Token evaluators::conjugate<patterns::monadic, patterns::conjugate>(evaluator_input &&input) {
        /*
        kepler::Token& operand = *input[1];
        if(operand.contains<Number>()) {
            auto& num = operand.get_content<Number>();
            num = conj(num);
        } else {
            throw kepler::error(DomainError, "Expected a number.");
        }
        return operand;*/
        kepler::Token::content_type& operand = *input[1];
    }
/*
    template<>
    kepler::Token evaluators::negative<patterns::monadic, patterns::negative>(evaluator_input &&input) {
        kepler::Token& operand = *input[1];
        if(operand.contains<Number>()) {
            auto& num = operand.get_content<Number>();
            num = Number(0) - num;
        } else {
            throw kepler::error(DomainError, "Expected a number.");
        }
        return operand;
    }

    template<>
    kepler::Token evaluators::direction<patterns::monadic, patterns::direction>(evaluator_input &&input) {
        kepler::Token& operand = *input[1];
        if(operand.contains<Number>()) {
            auto& num = operand.get_content<Number>();
            if(num != 0.0) {
                num = num / abs(num);
            }
        } else {
            throw kepler::error(DomainError, "Expected a number.");
        }
        return operand;
    }

    template<>
    kepler::Token evaluators::plus<patterns::dyadic, patterns::plus>(evaluator_input &&input) {
        return kepler::Token();
    }
    */
};