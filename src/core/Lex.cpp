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

#include "Lex.h"
#include <re2/re2.h>

#include <utility>
#include "uni_algo/conv.h"
#include "CharacterSetNew.h"

/*
Lex::Lex(std::string _input, bool _debugOn) : input(std::move(_input)), cursor(input.begin()), debugOn(_debugOn) {}

bool Lex::match_line() {

}

bool Lex::match_literal_identifier() {

    return match(r);
}

bool Lex::match_direct_identifier() {
    std::regex r(uni::utf32to8(U"^" + Character::alpha + U"|" + Character::omega));
    return match(r);
}

bool Lex::match(const std::string &regex) {

    re2::StringPiece s(input.substr())
    if(re2::RE2::FullMatch())

    std::smatch match;
    if(std::regex_search(cursor, input.end(), match, regex)) {
        //cursor += match.length();
        return true;
    }

    return false;
}
 */