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
        NUMBER,
        STRING,
        ID,

        // Arguments
        ALPHA,
        OMEGA,

        // Functions
        PLUS,
        MINUS,
        TIMES,
        DIVIDE,
        CEILING,
        FLOOR,
        RIGHT_TACK,
        LEFT_TACK,
        IOTA,
        CIRCLE_BAR,
        CIRCLE_STILE,
        LESS,
        LESSEQ,
        EQ,
        GREATEREQ,
        GREATER,
        NEQ,
        WITHOUT,
        LSHOE,
        RHO,
        AND,
        OR,
        NAND,
        NOR,
        ROLL,
        CIRCLE,
        STAR,
        LOG,
        BAR,
        EXCLAMATION_MARK,
        COMMA,
        ARROW_UP,

        // Operators
        COMMUTE,
        SLASH,
        DIAERESIS,
        JOT,
        ATOP,
        OVER,

        // Misc
        COLON,
        DIAMOND,
        NEGATE,
        ASSIGNMENT,
        LPARENS,
        RPARENS,
        LBRACE,
        RBRACE,
        END,
    };
};