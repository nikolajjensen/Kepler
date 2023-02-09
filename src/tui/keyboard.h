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
#include "core/characters.h"
#include <string>

namespace kepler::tui {
    namespace keyboard {
        const Char lock_char = characters::dollar_sign;

        bool should_lock(const StringUTF8& input) {
            return uni::utf32to8(StringUTF32(1, lock_char)) == input;
        }

        Char alternative_char(Char input) {
            switch (input) {
                case U'å':
                    return characters::left_arrow;
                case U'+':
                    return characters::multiply;
                case U'´':
                    return characters::divide;
                case U'(':
                    return characters::circle_star;
                case U'`':
                    return characters::quad_divide;
                case U'o':
                    return characters::circle;
                case U's':
                    return characters::up_stile;
                case U'd':
                    return characters::down_stile;
                case U'b':
                    return characters::up_tack;
                case U'n':
                    return characters::down_tack;
                case U'>':
                    return characters::left_tack;
                case U'<':
                    return characters::right_tack;
                case U'8':
                    return characters::not_equal;
                case U'4':
                    return characters::less_than_or_equal;
                case U'6':
                    return characters::greater_than_or_equal;
                case U'9':
                    return characters::down_caret;
                case U'0':
                    return characters::up_caret;
                case U'=':
                    return characters::up_caret_tilde;
                case U')':
                    return characters::down_caret_tilde;
                case U'y':
                    return characters::up_arrow;
                case U'u':
                    return characters::down_arrow;
                case U'z':
                    return characters::left_shoe;
                case U'x':
                    return characters::right_shoe;
                case U'€':
                    return characters::delta_stile;
                case U'#':
                    return characters::del_stile;
                case U'i':
                    return characters::iota;
                case U'e':
                    return characters::epsilon;
                case U'v':
                    return characters::down_shoe;
                case U'c':
                    return characters::up_shoe;
                case U'-':
                    return characters::slash_bar;
                case U'.':
                    return characters::back_slash_bar;
                case U';':
                    return characters::comma_bar;
                case U'r':
                    return characters::rho;
                case U'%':
                    return characters::circle_stile;
                case U'/':
                    return characters::circle_bar;
                case U'&':
                    return characters::circle_back_slash;
                case U'1':
                    return characters::diaeresis;
                case U'T':
                    return characters::diaeresis_tilde;
                case U'j':
                    return characters::jot;
                case U'J':
                    return characters::diaeresis_jot;
                case U'Å':
                    return characters::quote_quad;
                case U'l':
                    return characters::quote;
                case U'æ':
                    return characters::up_tack_jot;
                case U'ø':
                    return characters::down_tack_jot;
                case U'$':
                    return characters::diamond;
                case U',':
                    return characters::up_shoe_jot;
                case U'¨':
                    return characters::right_arrow;
                case U'w':
                    return characters::omega;
                case U'a':
                    return characters::alpha;
                case U'g':
                    return characters::del;
                case U'2':
                    return characters::overbar;
                default:
                    return characters::underbar;
            }
        }

        StringUTF8 alternative(StringUTF8 input) {
            Char ch = alternative_char(uni::utf8to32(input)[0]);
            return uni::utf32to8(StringUTF32(1, ch));
        }
    }
}