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

#include "form_table_evaluators.h"
#include "form_table.h"

namespace kepler::form_table::evaluators {
    Array reduction::operator()(const Token &func, const Array &operand) {
        auto applicator = form_table::lookup({form_table::Constant, &func, form_table::Constant}, this->session);
        if(applicator == nullptr) {
            throw kepler::error(SyntaxError, "No evaluation sequence.");
        }
        auto& evaluator = applicator->ar->ex->ev;

        Array result = Array::vectorOf(List<Number>{0});
        auto& accumulator = result.ravel_list[0];
        accumulator = operand.ravel_list.back();

        for(auto i = operand.ravel_list.rbegin() + 1; i != operand.ravel_list.rend(); ++i) {
            accumulator = boost::apply_visitor(*evaluator, *i, accumulator);
        }

        return result;
    }
};