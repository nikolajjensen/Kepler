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

#include <iostream>

namespace kepler {
    enum TokenType {
        // Data types
        ID,
        NUMBER,
        STRING,

        // Arguments
        ALPHA,
        OMEGA,

        // Functions
        AND,
        ARROW_UP,
        BAR,
        CEILING,
        CIRCLE,
        CIRCLE_BAR,
        CIRCLE_STILE,
        COMMA,
        DIVIDE,
        EQUAL,
        EXCLAMATION_MARK,
        FLOOR,
        GREATER,
        GREATER_EQUAL,
        IOTA,
        LEFT_SHOE,
        LEFT_TACK,
        LESS,
        LESS_EQUAL,
        LOG,
        MINUS,
        NAND,
        NOR,
        NOT_EQUAL,
        OR,
        PLUS,
        POWER,
        PRODUCT,
        QUESTION_MARK,
        RHO,
        RIGHT_TACK,
        STAR,
        TIMES,
        WITHOUT,

        // Operators
        ATOP,
        COMMUTE,
        DIAERESIS,
        JOT,
        OVER,
        SLASH,

        // Misc
        ASSIGNMENT,
        COLON,
        DIAMOND,
        END,
        LEFT_BRACE,
        LEFT_PARENS,
        NEGATE,
        RIGHT_BRACE,
        RIGHT_PARENS,
    };
};