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

#pragma once
#include "Types.h"
#include "Token.h"
#include <vector>
#include <re2/re2.h>


class Lex {
    bool debugOn;

    const std::string input;
    std::string::const_iterator cursor;
    std::vector<Token> tokens;

    bool match_line();

    bool match_identifier();
    bool match_simple_identifier();
    bool match_literal_identifier();
    bool match_direct_identifier();
    bool match_distinguished_identifier();
    bool match_numeric_literal();
    bool match_character_literal();
    bool match_comment();
    bool match_primitive();
    bool match_space();
    bool match_statement_separator();

    bool match(const std::string &regex);

public:
    Lex(std::string, bool debugOn = false);
};
