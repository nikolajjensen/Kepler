//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include "interpreter.h"
#include "form_table.h"
#include "phrase_table.h"

using namespace kepler::interpreter;
using namespace kepler::phrase_table;

kepler::Token kepler::interpreter::interpret(kepler::Context *context, kepler::Session *session) {
    context->stack = {};

    auto it = context->currentStatement.rbegin();
    auto end_it = context->currentStatement.rend();
    bool done = false;

    while(!done) {
        lookup_result result = kepler::phrase_table::lookup(context->stack);

        if(result.evaluator == nullptr) {
            // No evaluator was found with lookup, so we push to stack.
            if(context->currentStatement.empty()) {
                throw kepler::error(SyntaxError, "Ran out of tokens to evaluate, but is still not done...");
            } else {
                context->stack.insert(context->stack.begin(),
                                      std::make_move_iterator(context->currentStatement.end() - 1),
                                      std::make_move_iterator(context->currentStatement.end()));
                context->currentStatement.erase(context->currentStatement.end() - 1);
            }
        } else {
            result.evaluator(context->stack, *session);

            if(result.end_of_statement) {
                done = true;
            }
        }
    }

    return context->stack[0];
}
