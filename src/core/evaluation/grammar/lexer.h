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
#include "core/datatypes.h"
#include "rules.h"

namespace kepler {
    class Lexer : public grammar::Matcher<Char, grammar::lexer_context> {
    public:
        using grammar::Matcher<Char, grammar::lexer_context>::Matcher;

        bool lex() {
            return grammar::Matcher<Char, grammar::lexer_context>::match(grammar::rules::line);
        }
    };
};