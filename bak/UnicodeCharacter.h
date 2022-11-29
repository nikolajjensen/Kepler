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
#include <string>
#include <span>
#include "Types.h"
#include <vector>


struct UnicodeCharacter {
    typename std::vector<Char> representations;

    UnicodeCharacter(std::vector<Char> &&);
    UnicodeCharacter(const Char &);

    friend std::ostream& operator<<(std::ostream &, const UnicodeCharacter &);

    friend bool operator==(const UnicodeCharacter&, const UnicodeCharacter&);
    friend bool operator==(const Char&, const UnicodeCharacter&);
    friend bool operator==(const UnicodeCharacter&, const Char&);
};

/*

namespace CharacterGroups {
    const CharacterGroup letters({
        CharacterSet::lowerA, CharacterSet::lowerB, CharacterSet::lowerC,
        CharacterSet::lowerD, CharacterSet::lowerE, CharacterSet::lowerF,
        CharacterSet::lowerG, CharacterSet::lowerH, CharacterSet::lowerI,
        CharacterSet::lowerJ, CharacterSet::lowerK, CharacterSet::lowerL,
        CharacterSet::lowerM, CharacterSet::lowerN, CharacterSet::lowerO,
        CharacterSet::lowerP, CharacterSet::lowerQ, CharacterSet::lowerR,
        CharacterSet::lowerS, CharacterSet::lowerT, CharacterSet::lowerU,
        CharacterSet::lowerV, CharacterSet::lowerW, CharacterSet::lowerX,
        CharacterSet::lowerY, CharacterSet::lowerZ,
        CharacterSet::upperA, CharacterSet::upperB, CharacterSet::upperC,
        CharacterSet::upperD, CharacterSet::upperE, CharacterSet::upperF,
        CharacterSet::upperG, CharacterSet::upperH, CharacterSet::upperI,
        CharacterSet::upperJ, CharacterSet::upperK, CharacterSet::upperL,
        CharacterSet::upperM, CharacterSet::upperN, CharacterSet::upperO,
        CharacterSet::upperP, CharacterSet::upperQ, CharacterSet::upperR,
        CharacterSet::upperS, CharacterSet::upperT, CharacterSet::upperU,
        CharacterSet::upperV, CharacterSet::upperW, CharacterSet::upperX,
        CharacterSet::upperY, CharacterSet::upperZ,
    });

    const CharacterGroup digits({
        CharacterSet::zero, CharacterSet::one, CharacterSet::two,
        CharacterSet::three, CharacterSet::four, CharacterSet::five,
        CharacterSet::six, CharacterSet::seven, CharacterSet::eight,
        CharacterSet::nine,
    });

    const CharacterGroup ideograms({
       CharacterSet::diaeresis, CharacterSet::overbar, CharacterSet::leftCaret,
       CharacterSet::lessThanOrEqual, CharacterSet::equal, CharacterSet::greaterThanOrEqual,
       CharacterSet::rightCaret, CharacterSet::notEqual, CharacterSet::downCaret,
       CharacterSet::upCaret, CharacterSet::bar, CharacterSet::divide,
       CharacterSet::plus, CharacterSet::multiply, CharacterSet::query,
       CharacterSet::omega, CharacterSet::epsilon, CharacterSet::rho,
       CharacterSet::tilde, CharacterSet::upArrow, CharacterSet::downArrow,
       CharacterSet::iota, CharacterSet::circle, CharacterSet::star,
       CharacterSet::rightArrow, CharacterSet::leftArrow, CharacterSet::alpha,
       CharacterSet::upStile, CharacterSet::downStile, CharacterSet::underbar,
       CharacterSet::jot, CharacterSet::leftParenthesis, CharacterSet::rightParenthesis,
       CharacterSet::leftBracket, CharacterSet::rightBracket, CharacterSet::leftShoe,
       CharacterSet::rightShoe, CharacterSet::upShoe, CharacterSet::downShoe,
       CharacterSet::upTack, CharacterSet::downTack, CharacterSet::stile,
       CharacterSet::semicolon, CharacterSet::colon, CharacterSet::backSlash,
       CharacterSet::comma, CharacterSet::dot, CharacterSet::slash,
       CharacterSet::delStile, CharacterSet::deltaStile, CharacterSet::circleStile,
       CharacterSet::circleBackslash, CharacterSet::circleBar, CharacterSet::circleStar,
       CharacterSet::downCaretTilde, CharacterSet::upCaretTilde, CharacterSet::quoteDot,
       CharacterSet::quadDivide, CharacterSet::upTackJot, CharacterSet::downTackJot,
       CharacterSet::backSlashBar, CharacterSet::slashBar, CharacterSet::diaeresisJot,
       CharacterSet::commaBar, CharacterSet::diaeresisTilde, CharacterSet::leftBrace,
       CharacterSet::rightBrace, CharacterSet::rightTack, CharacterSet::leftTack,
       CharacterSet::dollarSign,
    });
};
*/