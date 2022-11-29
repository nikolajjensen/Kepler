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

#include "Lexer.h"
#include "TokenType.h"
#include "CharacterSet.h"
#include "UnicodeString.h"
#include "uni_algo/conv.h"
#include <iostream>
#include <utility>
#include <algorithm>

Lexer::Lexer(CharList _input, bool _debugOn) : input(std::move(_input)), debugOn(_debugOn), tokens(), content() {}

std::vector<Token> Lexer::run() {
    tokens.clear();
    // Do some magic lexing here! thread_line();

    //UnicodeString something(U"ABC←FN");
    auto begin = input.begin();
    auto end = input.end();

    primitive.match(begin, end);

    //bool success = test3.match(begin, end) && begin == end;

    //std::cout << "Works? " << success << "\n";

    //std::cout << "Full input lexed? " << (it == input.end() ? "Yes" : "No") << "\n";
    return tokens;
}