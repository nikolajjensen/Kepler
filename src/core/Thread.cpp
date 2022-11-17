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

Thread::Thread(Lexer *_lexer, CharList::iterator &_it, CharList &_content) : success(true), threaded(0), it(_it), content(_content), lexer(_lexer) {}

Thread* Thread::one(Thread::func f) {
    if(success) {
        unsigned int result = (lexer->*f)();
        threaded+= result;
        success = result != 0;
    }

    return this;
}

Thread* Thread::many(Thread::func f) {
    if(success) {
        unsigned int last;
        do {
            last = (lexer->*f)();
            threaded += last;
        } while(last != 0);
    }

    // Not changing success, as this semantically we could run f no times. '' is a valid character-literal, for example.
    return this;
}

unsigned int Thread::thread() {
    if(success) {
        return threaded;
    } else {
        unthread();
        return 0;
    }
}

void Thread::unthread() {
    content.erase(content.end() - threaded);
    it -= threaded;
    threaded = 0;
}