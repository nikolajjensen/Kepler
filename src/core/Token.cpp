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

#include "Token.h"
#include <utility>
#include <uni_algo/conv.h>

Token::Token(TokenType _type, CharList _content) : type(_type), content(std::move(_content)) {}

Token::Token(TokenType _type, Char _char) : type(_type), content(CharList(1, _char)) {}

std::ostream& operator<<(std::ostream &os, const Token &t) {
    os << "Token(" << t.type << ", '" << uni::utf32to8(t.content) << "')";
    return os;
}