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

#include "classifiers.h"

bool kepler::helpers::is_function(TokenType type) {
    return type == PLUS || type == MINUS || type == TIMES || type == DIVIDE || type == FLOOR
           || type == CEILING || type == RIGHT_TACK || type == LEFT_TACK || type == IOTA || type == LESS
           || type == LESS_EQUAL || type == EQUAL || type == GREATER_EQUAL || type == GREATER || type == NOT_EQUAL
           || type == WITHOUT || type == LEFT_SHOE || type == RHO || type == AND || type == OR
           || type == NAND || type == NOR || type == CIRCLE_BAR || type == CIRCLE_STILE || type == QUESTION_MARK
           || type == CIRCLE || type == STAR || type == LOG || type == BAR || type == EXCLAMATION_MARK
           || type == COMMA || type == ARROW_UP;
}

bool kepler::helpers::is_monadic_function(TokenType type) {
    return type == QUESTION_MARK;
}

bool kepler::helpers::is_monadic_operator(TokenType type) {
    return type == COMMUTE || type == DIAERESIS || type == SLASH || type == PRODUCT;
}

bool kepler::helpers::is_dyadic_operator(TokenType type) {
    return type == JOT || type == ATOP || type == OVER || type == PRODUCT || type == POWER;
}

bool kepler::helpers::is_array_token(TokenType type) {
    return type == NUMBER || type == STRING || type == ID || type == ALPHA || type == OMEGA;
}