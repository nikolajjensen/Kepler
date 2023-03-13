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

#include "defined_function.h"
#include "core/constants/literals.h"
#include "core/evaluation/interpreter.h"
#include "core/constants/config.h"
#include "core/symbol_table.h"

namespace kepler {
    DefinedFunction::DefinedFunction(AnonymousFunction* function_, std::ostream& output_stream_)
            : function(function_), Operation(nullptr), output_stream(output_stream_) {}

    DefinedFunction::~DefinedFunction() {
        //delete function;
    }

    Array DefinedFunction::operator()(const Array& omega) {
        auto symbol_table = function->body->symbol_table;
        symbol_table->set(constants::omega_id, omega);
        //symbol_table->set(constants::recursive_call_id, function);

        Interpreter interpreter(*function->body, *symbol_table, output_stream);
        auto result = interpreter.interpret();
        symbol_table->strip_values();
        return result;
    }

    Array DefinedFunction::operator()(const Array& alpha, const Array& omega) {
        auto symbol_table = function->body->symbol_table;
        symbol_table->set(constants::alpha_id, alpha);
        symbol_table->set(constants::omega_id, omega);

        Interpreter interpreter(*function->body, *symbol_table, output_stream);
        auto result = interpreter.interpret();
        symbol_table->strip_values();
        return result;
    }
};