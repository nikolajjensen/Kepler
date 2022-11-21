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

#include "Thread.h"

Lexer::Thread::Thread(Lexer *_lexer, bool _append) : should_continue(true), failed(false), threaded(0), lexer(_lexer), append(_append) {}

bool Lexer::Thread::match(std::vector<Char> &chars) {
    //log_thread_attempt("marker");
    bool matched = false;
    size_t index = 0;
    while(!matched && index < chars.size()) {
        if(*(lexer->it) == chars[index]) {
            if(append) {lexer->append_to_content(chars[index]);}
            matched = true;
            lexer->it++;
        }
        index++;
    }

    return matched;
}

bool Lexer::Thread::match(Char c) {
    //log_thread_attempt("marker");
    if(*(lexer->it) == c) {
        if(append) {lexer->append_to_content(c);}
        lexer->it++;
        return true;
    }
    return false;
}

Lexer::Thread& Lexer::Thread::one(Char c, bool optional) {
    if(should_continue && !failed) {
        unsigned int result = match(c);
        threaded+= result;
        failed = result == 0 && !optional;
    }

    return *this;
}

Lexer::Thread& Lexer::Thread::one(Lexer::func func, bool optional) {
    if(should_continue && !failed) {
        unsigned int result = (lexer->*func)();
        threaded+= result;
        failed = result == 0 && !optional;
    }

    return *this;
}

Lexer::Thread& Lexer::Thread::many(Char c, unsigned int at_least) {
    if(should_continue && !failed) {
        unsigned count = 0;
        unsigned int last;
        do {
            last = match(c);
            count += last;
        } while(last != 0);
        threaded += count;

        if(count < at_least) { failed = true; }
    }

    return *this;
}

Lexer::Thread& Lexer::Thread::many(std::vector<Char> chars, unsigned int at_least) {
    if(should_continue && !failed) {
        unsigned count = 0;
        unsigned int last;
        do {
            last = match(chars);
            count += last;
        } while(last != 0);
        threaded += count;

        if(count < at_least) { failed = true; }
    }

    return *this;
}

Lexer::Thread& Lexer::Thread::any(std::vector<Char> chars) {
    if(should_continue && !failed) {
        unsigned int result = match(chars);
        threaded+= result;
        failed = result == 0;
    }

    return *this;
}

Lexer::Thread& Lexer::Thread::any(std::vector<func> funcs) {
    if(should_continue && !failed) {
        unsigned int result = 0;
        size_t index = 0;
        while(result == 0 && index < funcs.size()) {
            result = (lexer->*(funcs[index]))();
            index++;
        }
        threaded+= result;
        failed = result == 0;
    }

    return *this;
}

Lexer::Thread& Lexer::Thread::one(Lexer::Thread &, bool optional) {

}

unsigned int Lexer::Thread::thread() {
    if(failed) {
        unthread();
        return 0;
    }

    return threaded;
}

void Lexer::Thread::unthread() {
    lexer->unthread(threaded);
    threaded = 0;
}