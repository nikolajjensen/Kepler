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

namespace kepler {
    DefinedFunction::DefinedFunction(AnonymousFunction* function_)
            : function(function_) {}

    DefinedFunction::~DefinedFunction() {
        //delete function;
    }

    bool DefinedFunction::is_configured() const {
        // Defined functions are always entirely configured,
        // as they do not rely on any sub-operations.
        return true;
    }

    Array DefinedFunction::operator()(Array omega) {
        auto symbol_table = function->body->symbol_table;
        symbol_table->set(constants::omega_id, omega);

        Interpreter interpreter(*function->body, *symbol_table);
        auto result = interpreter.interpret();
        symbol_table->strip_values();
        return result;
    }

    Array DefinedFunction::operator()(Array alpha, Array omega) {
        auto symbol_table = function->body->symbol_table;
        symbol_table->set(constants::alpha_id, alpha);
        symbol_table->set(constants::omega_id, omega);

        Interpreter interpreter(*function->body, *symbol_table);
        auto result = interpreter.interpret();
        symbol_table->strip_values();
        return result;
    }
};