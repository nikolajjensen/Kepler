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
#include "datatypes.h"

namespace kepler {
    namespace characters {
        const Char alpha = U'⍺';
        const Char down_arrow = U'↓';
        const Char left_arrow = U'←';
        const Char right_arrow = U'→';
        const Char up_arrow = U'↑';
        const Char bar = U'-';
        const Char blank = U' ';
        const Char left_brace = U'{';
        const Char right_brace = U'}';
        const Char left_bracket = U'[';
        const Char right_bracket = U']';
        const Char down_caret = U'∨';
        const Char down_caret_tilde = U'⍱';
        const Char left_caret = U'<';
        const Char right_caret = U'>';
        const Char up_caret = U'∧';
        const Char up_caret_tilde = U'⍱';
        const Char circle = U'○';
        const Char circle_backslash = U'⍉';
        const Char circle_bar = U'⊖';
        const Char circle_star = U'⍟';
        const Char circle_stile = U'⌽';
        const Char colon = U':';
        const Char comma = U',';
        const Char comma_bar = U'⍪';
        const Char del = U'∇';
        const Char del_stile = U'⍒';
        const Char del_tilde = U'⍫';
        const Char delta = U'∆';
        const Char delta_stile = U'⍋';
        const Char delta_underbar = U'⍙';
        const Char diaeresis = U'¨';
        const Char diamond = U'⋄';
        const Char divide = U'÷';
        const Char dollar_sign = U'$';
        const Char dot = U'.';
        const Char epsilon = U'∈';
        const Char equal = U'=';
        const Char greater_than_or_equal = U'≥';
        const Char iota = U'⍳';
        const Char jot = U'∘';
        const Char less_than_or_equal = U'≤';
        const Char multiply = U'×';
        const Char not_equal = U'≠';
        const Char overbar = U'‾';
        const Char left_parenthesis = U'(';
        const Char right_parenthesis = U')';
        const Char plus = U'+';
        const Char quad = U'⎕';
        const Char quad_divide = U'⌹';
        const Char query = U'?';
        const Char diaeresis_jot = U'⍤';
        const Char quote = U'\'';
        const Char quote_dot = U'!';
        const Char quote_quad = U'⍞';
        const Char rho = U'⍴';
        const Char semicolon = U';';
        const Char down_shoe = U'∪';
        const Char left_shoe = U'⊂';
        const Char right_shoe = U'⊃';
        const Char up_shoe = U'∩';
        const Char up_shoe_jot = U'⍝';
        const Char slash = U'/';
        const Char back_slash = U'\\';
        const Char slash_bar = U'⌿';
        const Char back_slash_bar = U'⍀';
        const Char star = U'*';
        const Char stile = U'|';
        const Char down_stile = U'⌊';
        const Char up_stile = U'⌈';
        const Char up_tack = U'⊥';
        const Char up_tack_jot = U'⍎';
        const Char right_tack = U'⊢';
        const Char left_tack = U'⊣';
        const Char down_tack = U'⊤';
        const Char down_tack_jot = U'⍕';
        const Char tilde = U'~';
        const Char underbar = U'_';
        const Char diaeresis_tilde = U'⍨';
        const Char omega = U'⍵';

        const Char complex_marker = U'J';
        const Char exponent_marker = U'E';

        const StringUTF32 ideogram_1 = U"¨‾<≤=≥>≠∨∧÷+×?⍵∊⍴~↑↓⍳○*→←⍺⌈⌊_∘()[]⊂⊃∩∪⊥⊤|;:\\,./⍒⍋⌽⍉⊖⍟⍱⍲!⌹⍎⍕⍀⌿⍤⍪⍨{}⊢⊣$";
        const StringUTF32 ideogram_2 = U"-";

        const StringUTF32 numbers = U"0123456789";
        const StringUTF32 letters = U"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    };
};