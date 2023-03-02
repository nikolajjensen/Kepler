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
#include "matcher.h"
#include "context.h"
#include "core/error.h"
#include "core/datatypes.h"
#include "rules.h"

namespace kepler {
    class FunctionEditingParser : public grammar::Matcher<Char, grammar::function_editing_context> {
    private:
        Token& identifier;
        Context& context;

    public:
        explicit FunctionEditingParser(Token& identifier_, Context& context_)
                              : grammar::Matcher<Char, grammar::function_editing_context>(context_.current_line, identifier_, context_),
                                identifier(identifier_), context(context_) {}

        void parse() {
            if(!grammar::Matcher<Char, grammar::function_editing_context>::match(grammar::rules::general_request)) {
                throw kepler::error(DefinitionError, "Could not parse input.");
            }
        }
    };
};