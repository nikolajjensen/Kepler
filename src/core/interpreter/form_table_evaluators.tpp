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
    kepler::Token evaluators::call_defined_function<patterns::niladic, patterns::niladic_cdf>(input_t &&input) {
        return kepler::Token();
    }

    template<>
    kepler::Token evaluators::call_defined_function<patterns::monadic, patterns::monadic_cdf>(input_t &&input) {
        return kepler::Token();
    }

    template<>
    kepler::Token evaluators::conjugate<patterns::monadic, patterns::conjugate>(input_t&& input) {
        kepler::Token operand = *input[1];
        if(operand.contains<Array>()) {
            for(auto& element : operand.get_content<Array>().ravelList) {
                if(Number* number = boost::get<Number>(&element)) {
                    *number = conj(*number);
                } else {
                    throw kepler::error(DomainError, "Expected a number.");
                }
            }
        } else {
            throw kepler::error(InternalError, "Expected an array.");
        }
        return operand;
    }

    template<>
    kepler::Token evaluators::negative<patterns::monadic, patterns::negative>(input_t &&input) {
        kepler::Token operand = *input[1];
        if(operand.contains<Array>()) {
            for(auto& element : operand.get_content<Array>().ravelList) {
                if(Number* number = boost::get<Number>(&element)) {
                    *number = Number(0) - *number;
                } else {
                    throw kepler::error(DomainError, "Expected a number.");
                }
            }
        } else {
            throw kepler::error(InternalError, "Expected an array.");
        }
        return operand;
    }

    template<>
    kepler::Token evaluators::direction<patterns::monadic, patterns::direction>(input_t &&input) {
        kepler::Token operand = *input[1];
        if(operand.contains<Array>()) {
            for(auto& element : operand.get_content<Array>().ravelList) {
                if(Number* number = boost::get<Number>(&element)) {
                    if(*number != 0.0) {
                        *number = *number / abs(*number);
                    }
                } else {
                    throw kepler::error(DomainError, "Expected a number.");
                }
            }
        } else {
            throw kepler::error(InternalError, "Expected an array.");
        }
        return operand;
    }

    template<>
    kepler::Token evaluators::plus<patterns::dyadic, patterns::plus>(input_t &&input) {
        kepler::Token& a = *input[0];
        kepler::Token& b = *input[2];
        kepler::Token result = a;

        if(a.contains<Array>() && b.contains<Array>()) {
            auto& a_arr = a.get_content<Array>();
            auto& b_arr = b.get_content<Array>();
            auto& result_arr = result.get_content<Array>();
            if(a_arr.shapeList == b_arr.shapeList) {
                for(int i = 0; i < a_arr.ravelList.size(); ++i) {
                    auto& a_num = boost::get<Number>(a_arr.ravelList[i]);
                    auto& b_num = boost::get<Number>(b_arr.ravelList[i]);
                    result_arr.ravelList[i] = a_num + b_num;
                }

                return result;
            }
        }

        throw kepler::error(DomainError, "Incompatible operands.");
    }

    template<>
    kepler::Token evaluators::divide<patterns::dyadic, patterns::divide>(input_t &&input) {
        kepler::Token& a = *input[0];
        kepler::Token& b = *input[2];
        kepler::Token result = a;

        if(a.contains<Array>() && b.contains<Array>()) {
            auto& a_arr = a.get_content<Array>();
            auto& b_arr = b.get_content<Array>();
            auto& result_arr = result.get_content<Array>();
            if(a_arr.shapeList == b_arr.shapeList) {
                for(int i = 0; i < a_arr.ravelList.size(); ++i) {
                    auto& a_num = boost::get<Number>(a_arr.ravelList[i]);
                    auto& b_num = boost::get<Number>(b_arr.ravelList[i]);
                    result_arr.ravelList[i] = a_num / b_num;
                }

                return result;
            }
        }

        throw kepler::error(DomainError, "Incompatible operands.");
    }
};