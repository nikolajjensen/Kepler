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

#include "conversion.h"
#include <algorithm>
#include <uni_algo/conv.h>

kepler::Number kepler::from_string(std::string num_str) {
    String str = uni::utf8to32u(num_str);
    std::replace(str.begin(), str.end(), U'¯', U'-');

    size_t complex_index = str.find(U'J');
    if(complex_index != String::npos) {
        return {
                std::stod(uni::utf32to8(str.substr(0, complex_index))), std::stod(uni::utf32to8(str.substr(complex_index + 1)))
        };
    }

    return {std::stod(uni::utf32to8(str))};
}

std::string kepler::to_string(TokenType type) {
    switch (type) {
        case NUMBER:
            return "NUMBER";
        case STRING:
            return "STRING";
        case ID:
            return "ID";
        case ALPHA:
            return "ALPHA";
        case OMEGA:
            return "OMEGA";
        case PLUS:
            return "PLUS";
        case MINUS:
            return "MINUS";
        case TIMES:
            return "TIMES";
        case DIVIDE:
            return "DIVIDE";
        case CEILING:
            return "CEILING";
        case FLOOR:
            return "FLOOR";
        case RIGHT_TACK:
            return "RIGHT_TACK";
        case LEFT_TACK:
            return "LEFT_TACK";
        case IOTA:
            return "IOTA";
        case LESS:
            return "LESS";
        case LESS_EQUAL:
            return "LESSEQ";
        case EQUAL:
            return "EQ";
        case GREATER_EQUAL:
            return "GREATEREQ";
        case GREATER:
            return "GREATER";
        case NOT_EQUAL:
            return "NEQ";
        case WITHOUT:
            return "WITHOUT";
        case LEFT_SHOE:
            return "LSHOE";
        case RHO:
            return "RHO";
        case AND:
            return "AND";
        case OR:
            return "OR";
        case NAND:
            return "NAND";
        case NOR:
            return "NOR";
        case QUESTION_MARK:
            return "ROLL";
        case COMMUTE:
            return "COMMUTE";
        case SLASH:
            return "SLASH";
        case DIAERESIS:
            return "DIAERESIS";
        case JOT:
            return "JOT";
        case ATOP:
            return "ATOP";
        case OVER:
            return "OVER";
        case DIAMOND:
            return "DIAMOND";
        case NEGATE:
            return "NEGATE";
        case ASSIGNMENT:
            return "ASSIGNMENT";
        case LEFT_PARENS:
            return "LPARENS";
        case RIGHT_PARENS:
            return "RPARENS";
        case LEFT_BRACE:
            return "LBRACE";
        case RIGHT_BRACE:
            return "RBRACE";
        case END:
            return "END";
        default:
            return "UNRECOGNIZED";
    }
}