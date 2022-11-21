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
public:
    typedef unsigned int (Lexer::*func)();

    class Thread {
    private:
        bool match(std::vector<Char> &);
        bool match(Char);

    public:

        bool failed;
        bool should_continue;
        bool append;
        unsigned int threaded;
        Lexer *lexer;

        Thread(Lexer *, bool append = true);

        Thread& one(Char, bool optional = false);
        Thread& one(func, bool optional = false);
        Thread& many(Char, unsigned int at_least = 0);
        Thread& many(std::vector<Char>, unsigned int at_least = 0);
        Thread& many(std::vector<func>, unsigned int at_least = 0);
        Thread& any(std::vector<Char>);
        Thread& any(std::vector<func>);

        Thread& one(Thread &, bool optional = false);
        Thread& many(Thread &, bool optional = false);
        Thread& many(std::vector<Thread &>, bool at_least = 0);
        Thread& any(std::vector<Thread &>, bool at_least = 0);


        unsigned int thread();

        void unthread();
    };

    explicit Lexer(CharList input, bool debugOn = false);


    std::vector<Token> run();

protected:
    bool debugOn;

    CharList input;
    CharList::iterator it;
    CharList content;
    std::vector<Token> tokens;
    Thread thread;

    //unsigned int statement_separator();
    //unsigned int letter();
    //unsigned int digit();
    //unsigned int ideogram();

    //typedef unsigned int (Lexer::*func)();

    //unsigned int one(func);
    //unsigned int many(func);
    //unsigned int any(std::initializer_list<func> && funcs);
    //unsigned int all(std::initializer_list<func> && funcs);
    //unsigned int repeatedly(unsigned int (Lexer::*f)());
    //unsigned int repeatedly(unsigned int (Lexer::*f)(Char), Char);

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
    unsigned int nonquote();

    unsigned int statement_separator();
    //unsigned int letter();
    //unsigned int digit();
    //unsigned int ideogram();

    //unsigned int marker(Char marker);

    void log_thread_attempt(std::string &&type);
    void log_thread_success(std::string &&type);

    void clear_content();
    void append_to_content(Char c);
    void tokenize(TokenType type);
    void unthread(unsigned int);
};
