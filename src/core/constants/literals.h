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

#pragma once
#include "core/datatypes.h"
#include "core/token_type.h"
#include <map>

namespace kepler::constants {
    const std::map<Char, TokenType> wysiwyg_mapping = {
            {U'⍺',  ALPHA},
            {U'⍵',  OMEGA},
            {U'+',  PLUS},
            {U'-',  MINUS},
            {U'×',  TIMES},
            {U'÷',  DIVIDE},
            {U'⌈',  CEILING},
            {U'⌊',  FLOOR},
            {U'⊢',  RIGHT_TACK},
            {U'⊣',  LEFT_TACK},
            {U'⍳',  IOTA},
            {U'⊖',  CIRCLE_BAR},
            {U'⌽',  CIRCLE_STILE},
            {U',',  COMMA},
            {U'<',  LESS},
            {U'≤',  LESSEQ},
            {U'=',  EQ},
            {U'≥',  GREATEREQ},
            {U'>',  GREATER},
            {U'≠',  NEQ},
            {U'~',  WITHOUT},
            {U'?',  ROLL},
            {U'!',  EXCLAMATION_MARK},
            {U'○',  CIRCLE},
            {U'*',  STAR},
            {U'⍟',  LOG},
            {U'|',  BAR},
            {U'⊂',  LSHOE},
            {U'↑',  ARROW_UP},
            {U'.',  PRODUCT},
            {U'⍴',  RHO},
            {U'∧',  AND},
            {U'∨',  OR},
            {U'⍲',  NAND},
            {U'⍱',  NOR},
            {U'⍨',  COMMUTE},
            {U'⍣',  POWER},
            {U'/',  SLASH},
            {U'¨',  DIAERESIS},
            {U'∘',  JOT},
            {U'⍤',  ATOP},
            {U'⍥',  OVER},
            {U'←',  ASSIGNMENT},
            {U'(',  LPARENS},
            {U')',  RPARENS},
            {U'{',  LBRACE},
            {U'}',  RBRACE},
            {U'◊',  DIAMOND},
            {U'⋄',  DIAMOND},
            {U'\n', DIAMOND},
            {U':',  COLON},
    };

    const Char exponent_marker = U'E';
    const Char complex_marker = U'J';
    const Char overbar = U'¯';

    const std::u32string alpha_id = U"⍺";
    const std::u32string omega_id = U"⍵";

    const std::u32string primitives = U"⍺⍵+-+-×÷⌈⌊⊢⊣⍳<≤=≥>≠~?!○*⍟|⊂↑.⍴∧∨⍲⍱⊖⌽,⍨⍣/¨∘⍤⍥←(){}◊⋄\n:";
    const std::u32string identifier_chars = U"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789⎕∇";
    const std::u32string digit = U"0123456789";
};