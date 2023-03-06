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
#include <uni_algo/conv.h>

std::string kepler::to_string(const Number& num) {
    std::string result;

    if(num.real() < 0.0) {
        result += "¯";
    }
    result += std::to_string(abs(num.real()));

    if(num.imag() != 0) {
        result += "J";

        if(num.imag() < 0.0) {
            result += "¯";
        }
        result += std::to_string(abs(num.imag()));
    }

    return result;
}

kepler::Number kepler::from_string(std::string num_str) {
    std::u32string str = uni::utf8to32u(num_str);
    std::replace(str.begin(), str.end(), U'¯', U'-');

    size_t complex_index = str.find(U'J');
    if(complex_index != std::u32string::npos) {
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
        case LESSEQ:
            return "LESSEQ";
        case EQ:
            return "EQ";
        case GREATEREQ:
            return "GREATEREQ";
        case GREATER:
            return "GREATER";
        case NEQ:
            return "NEQ";
        case WITHOUT:
            return "WITHOUT";
        case LSHOE:
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
        case DECODE:
            return "DECODE";
        case ENCODE:
            return "ENCODE";
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
        case LPARENS:
            return "LPARENS";
        case RPARENS:
            return "RPARENS";
        case END:
            return "END";
        default:
            return "UNRECOGNIZED";
    }
}