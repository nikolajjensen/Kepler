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

template <>
kepler::Token kepler::form_table::evaluators::call_defined_function<kepler::form_table::niladic_cdf_size, kepler::form_table::niladic_cdf>(token_input&& input) {
    return kepler::Token();
}

template <>
kepler::Token kepler::form_table::evaluators::conjugate<kepler::form_table::conjugate_size, kepler::form_table::conjugate>(token_input&& input) {
    kepler::Token& operand = *input[1];
    if(classifiers::is_scalar(operand)) {
        auto& arr = operand.get_content<Array>();
        if(arr.contains_at<Number>(0)) {
            auto& num = arr.get_content<Number>(0);
            num.conjugate();
        }
    } else {
        throw kepler::error(DomainError, "Expected a scalar.");
    }

    return operand;
}

template <>
kepler::Token kepler::form_table::evaluators::negation<kepler::form_table::negation_size, kepler::form_table::negation>(token_input &&input) {
    kepler::Token& operand = *input[1];
    if(classifiers::is_scalar(operand)) {
        auto& arr = operand.get_content<Array>();
        if(arr.contains_at<Number>(0)) {
            auto& num = arr.get_content<Number>(0);
            num = 0 - num;
        }
    } else {
        throw kepler::error(DomainError, "Expected a scalar.");
    }

    return operand;
}