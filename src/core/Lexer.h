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

#include <string>
#include <vector>
#include "Token.h"

class Lexer {
private:
    bool debugOn;

    std::string input;
    unsigned int pos;
    std::string content;
    std::vector<Token> tokens;

    bool thread_line();
    bool thread_identifier();
    bool thread_simple_identifier();
    bool thread_literal_identifier();
    bool thread_direct_identifier();
    bool thread_distinguished_identifier();
    bool thread_numeric_literal();
    bool thread_real_scalar_literal();
    bool thread_exponent();
    bool thread_numeric_scalar_literal();
    bool thread_imaginary_part();
    bool thread_character_literal();
    bool thread_comment();
    bool thread_any();
    bool thread_primitive();
    bool thread_space();
    bool thread_nonquote();

    bool thread_statement_separator();
    bool thread_letter();
    bool thread_digit();
    bool thread_ideogram();

    bool thread_quote();
    bool thread_exponent_marker();
    bool thread_complex_marker();
    bool thread_dot();
    bool thread_underbar();
    bool thread_overbar();
    bool thread_blank();
    bool thread_del();
    bool thread_del_tilde();
    bool thread_lamp();
    bool thread_quad();
    bool thread_quote_quad();
    bool thread_diamond();

public:
    explicit Lexer(std::string input, bool debugOn = false);


    std::vector<Token> run();
};
