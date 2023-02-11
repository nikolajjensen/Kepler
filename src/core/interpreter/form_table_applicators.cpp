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
#include "../token.h"
#include "../exceptions/error.h"

/*
kepler::Token kepler::form_table::applicators::monadic_scalar(List<Token*>& tokens, monadic_scalar_evaluator evaluator) {
    kepler::Token operand = *tokens[1];
    if(operand.contains<Array>()) {
        for(auto& element : operand.get_content<Array>().ravelList) {
            boost::variant<Number, Char>* num = boost::get<Number>(&element);
            num = evaluator(num);
        }
    } else {
        throw kepler::error(InternalError, "Expected an array.");
    }
    return operand;
}
kepler::Token kepler::form_table::applicators::dyadic_scalar(List<Token*>& tokens, dyadic_scalar_evaluator evaluator) {
    kepler::Token& a = *tokens[0];
    kepler::Token& b = *tokens[2];
    kepler::Token result = a;

    if(a.contains<Array>() && b.contains<Array>()) {
        auto& a_arr = a.get_content<Array>();
        auto& b_arr = b.get_content<Array>();
        auto& result_arr = result.get_content<Array>();
        if(a_arr.shapeList == b_arr.shapeList) {
            for(int i = 0; i < a_arr.ravelList.size(); ++i) {
                result_arr.ravelList[i] = evaluator(a_arr.ravelList[i], b_arr.ravelList[i]);
            }

            return result;
        }
    }

    throw kepler::error(DomainError, "Incompatible operands.");
}

kepler::Token kepler::form_table::applicators::monadic_array(List<Token *> &tokens, monadic_array_evaluator evaluator) {
    kepler::Token operand = *tokens[1];
    if(operand.contains<Array>()) {
        kepler::Array& arr = operand.get_content<Array>();
        arr = evaluator(arr);
    } else {
        throw kepler::error(InternalError, "Expected an array.");
    }
    return operand;
}
 */