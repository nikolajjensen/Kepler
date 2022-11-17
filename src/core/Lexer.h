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
#include "CharacterSet.h"

class Lexer {
private:
    bool debugOn;

    CharList input;
    CharList::iterator it;
    CharList content;
    std::vector<Token> tokens;

    unsigned int thread_line();
    unsigned int thread_identifier();
    unsigned int thread_simple_identifier();
    unsigned int thread_literal_identifier();
    unsigned int thread_direct_identifier();
    unsigned int thread_distinguished_identifier();
    unsigned int thread_numeric_literal();
    unsigned int thread_real_scalar_literal();
    unsigned int thread_exponent();
    unsigned int thread_numeric_scalar_literal();
    unsigned int thread_imaginary_part();
    unsigned int thread_character_literal();
    unsigned int thread_comment();
    unsigned int thread_any();
    unsigned int thread_primitive();
    unsigned int thread_space();
    unsigned int thread_nonquote();

    unsigned int thread_statement_separator();
    unsigned int thread_letter();
    unsigned int thread_digit();
    unsigned int thread_ideogram();

    unsigned int thread_marker(Char marker);
    unsigned int repeatedly(unsigned int (Lexer::*f)());
    unsigned int repeatedly(unsigned int (Lexer::*f)(Char), Char);

    void log_thread_attempt(std::string &&type);
    void log_thread_success(std::string &&type);

    void clear_content();
    void append_to_content(Char c);
    void tokenize(TokenType type);

    void unthread(unsigned int);

public:
    explicit Lexer(CharList input, bool debugOn = false);


    std::vector<Token> run();
};
