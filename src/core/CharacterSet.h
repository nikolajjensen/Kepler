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

#include <vector>
#include "Types.h"

namespace Character {
    // Lower English alphabet characters.
    const Char lowerA = U'a';
    const Char lowerB = U'b';
    const Char lowerC = U'c';
    const Char lowerD = U'd';
    const Char lowerE = U'e';
    const Char lowerF = U'f';
    const Char lowerG = U'g';
    const Char lowerH = U'h';
    const Char lowerI = U'i';
    const Char lowerJ = U'j';
    const Char lowerK = U'k';
    const Char lowerL = U'l';
    const Char lowerM = U'm';
    const Char lowerN = U'n';
    const Char lowerO = U'o';
    const Char lowerP = U'p';
    const Char lowerQ = U'q';
    const Char lowerR = U'r';
    const Char lowerS = U's';
    const Char lowerT = U't';
    const Char lowerU = U'u';
    const Char lowerV = U'v';
    const Char lowerW = U'w';
    const Char lowerX = U'x';
    const Char lowerY = U'y';
    const Char lowerZ = U'z';

    // Upper English alphabet characters.
    const Char upperA = U'A';
    const Char upperB = U'B';
    const Char upperC = U'C';
    const Char upperD = U'D';
    const Char upperE = U'E';
    const Char upperF = U'F';
    const Char upperG = U'G';
    const Char upperH = U'H';
    const Char upperI = U'I';
    const Char upperJ = U'J';
    const Char upperK = U'K';
    const Char upperL = U'L';
    const Char upperM = U'M';
    const Char upperN = U'N';
    const Char upperO = U'O';
    const Char upperP = U'P';
    const Char upperQ = U'Q';
    const Char upperR = U'R';
    const Char upperS = U'S';
    const Char upperT = U'T';
    const Char upperU = U'U';
    const Char upperV = U'V';
    const Char upperW = U'W';
    const Char upperX = U'X';
    const Char upperY = U'Y';
    const Char upperZ = U'Z';

    // Numeric characters.
    const Char zero = U'0';
    const Char one = U'1';
    const Char two = U'2';
    const Char three = U'3';
    const Char four = U'4';
    const Char five = U'5';
    const Char six = U'6';
    const Char seven = U'7';
    const Char eight = U'8';
    const Char nine = U'9';

    // Special characters.
    const Char alpha = U'⍺';
    const Char downArrow = U'↓';
    const Char leftArrow = U'←';
    const Char rightArrow = U'→';
    const Char upArrow = U'↑';
    const Char bar = U'-';
    const Char blank = U' ';
    const Char leftBrace = U'{';
    const Char rightBrace = U'}';
    const Char leftBracket = U'[';
    const Char rightBracket = U']';
    const Char downCaret = U'∨';
    const Char downCaretTilde = U'⍱';
    const Char leftCaret = U'<';
    const Char rightCaret = U'>';
    const Char upCaret = U'∧';
    const Char upCaretTilde = U'⍲';
    const Char circle = U'○';
    const Char circleBackslash = U'⍉';
    const Char circleBar = U'⊖';
    const Char circleStar = U'⍟';
    const Char circleStile = U'⌽';
    const Char colon = U':';
    const Char comma = U',';
    const Char commaBar = U'⍪';
    const Char del = U'∇';
    const Char delStile = U'⍒';

    // -2.5E

    const Char delTilde = U'⍫';
    const Char delta = U'∆';
    const Char deltaStile = U'⍋';
    const Char deltaUnderbar = U'⍙';
    const Char diaeresis = U'¨';
    const Char diamond = U'⋄';
    const Char divide = U'÷';
    const Char dollarSign = U'$';
    const Char dot = U'.';
    const Char epsilon = U'∊';
    const Char equal = U'=';
    const Char greaterThanOrEqual = U'≥';
    const Char iota = U'⍳';
    const Char jot = U'∘';
    const Char lessThanOrEqual = U'≤';
    const Char multiply = U'×';
    const Char notEqual = U'≠';
    const Char overbar = U'‾';
    const Char leftParenthesis = U'(';
    const Char rightParenthesis = U')';
    const Char plus = U'+';
    const Char quad = U'⎕';
    const Char quadDivide = U'⌹';
    const Char query = U'?';
    const Char diaeresisJot = U'⍤';
    const Char quote = U'\'';
    const Char quoteDot = U'!';

    const Char quoteQuad = U'⍞';
    const Char rho = U'⍴';
    const Char semicolon = U';';
    const Char downShoe = U'∪';
    const Char leftShoe = U'⊂';
    const Char rightShoe = U'⊃';
    const Char upShoe = U'∩';
    const Char upShoeJot = U'⍝';
    const Char slash = U'/';
    const Char backSlash = U'\\';
    const Char slashBar = U'⌿';
    const Char backSlashBar = U'⍀';
    const Char star = U'*';
    const Char stile = U'|';
    const Char downStile = U'⌊';
    const Char upStile = U'⌈';
    const Char upTack = U'⊥';
    const Char upTackJot = U'⍎';
    const Char rightTack = U'⊢';
    const Char leftTack = U'⊣';
    const Char downTack = U'⊤';
    const Char downTackJot = U'⍕';
    const Char tilde = U'~';
    const Char underbar = U'_';
    const Char diaeresisTilde = U'⍨';
    const Char omega = U'⍵';
    const Char equalUnderbar = U'≡';

    const std::vector<Char> letter({
        Character::lowerA, Character::lowerB, Character::lowerC,
        Character::lowerD, Character::lowerE, Character::lowerF,
        Character::lowerG, Character::lowerH, Character::lowerI,
        Character::lowerJ, Character::lowerK, Character::lowerL,
        Character::lowerM, Character::lowerN, Character::lowerO,
        Character::lowerP, Character::lowerQ, Character::lowerR,
        Character::lowerS, Character::lowerT, Character::lowerU,
        Character::lowerV, Character::lowerW, Character::lowerX,
        Character::lowerY, Character::lowerZ,
        Character::upperA, Character::upperB, Character::upperC,
        Character::upperD, Character::upperE, Character::upperF,
        Character::upperG, Character::upperH, Character::upperI,
        Character::upperJ, Character::upperK, Character::upperL,
        Character::upperM, Character::upperN, Character::upperO,
        Character::upperP, Character::upperQ, Character::upperR,
        Character::upperS, Character::upperT, Character::upperU,
        Character::upperV, Character::upperW, Character::upperX,
        Character::upperY, Character::upperZ,
    });

    const std::vector<Char> digit({
       Character::zero, Character::one, Character::two,
       Character::three, Character::four, Character::five,
       Character::six, Character::seven, Character::eight,
       Character::nine,
    });

    const std::vector<Char> ideogram({
        Character::diaeresis, Character::overbar, Character::leftCaret,
        Character::lessThanOrEqual, Character::equal, Character::greaterThanOrEqual,
        Character::rightCaret, Character::notEqual, Character::downCaret,
        Character::upCaret, Character::bar, Character::divide,
        Character::plus, Character::multiply, Character::query,
        Character::omega, Character::epsilon, Character::rho,
        Character::tilde, Character::upArrow, Character::downArrow,
        Character::iota, Character::circle, Character::star,
        Character::rightArrow, Character::leftArrow, Character::alpha,
        Character::upStile, Character::downStile, Character::underbar,
        Character::jot, Character::leftParenthesis, Character::rightParenthesis,
        Character::leftBracket, Character::rightBracket, Character::leftShoe,
        Character::rightShoe, Character::upShoe, Character::downShoe,
        Character::upTack, Character::downTack, Character::stile,
        Character::semicolon, Character::colon, Character::backSlash,
        Character::comma, Character::dot, Character::slash,
        Character::delStile, Character::deltaStile, Character::circleStile,
        Character::circleBackslash, Character::circleBar, Character::circleStar,
        Character::downCaretTilde, Character::upCaretTilde, Character::quoteDot,
        Character::quadDivide, Character::upTackJot, Character::downTackJot,
        Character::backSlashBar, Character::slashBar, Character::diaeresisJot,
        Character::commaBar, Character::diaeresisTilde, Character::leftBrace,
        Character::rightBrace, Character::rightTack, Character::leftTack,
        Character::dollarSign,
    });

    const std::vector<Char> nonquote({
        Character::lowerA, Character::lowerB, Character::lowerC,
        Character::lowerD, Character::lowerE, Character::lowerF,
        Character::lowerG, Character::lowerH, Character::lowerI,
        Character::lowerJ, Character::lowerK, Character::lowerL,
        Character::lowerM, Character::lowerN, Character::lowerO,
        Character::lowerP, Character::lowerQ, Character::lowerR,
        Character::lowerS, Character::lowerT, Character::lowerU,
        Character::lowerV, Character::lowerW, Character::lowerX,
        Character::lowerY, Character::lowerZ,
        Character::upperA, Character::upperB, Character::upperC,
        Character::upperD, Character::upperE, Character::upperF,
        Character::upperG, Character::upperH, Character::upperI,
        Character::upperJ, Character::upperK, Character::upperL,
        Character::upperM, Character::upperN, Character::upperO,
        Character::upperP, Character::upperQ, Character::upperR,
        Character::upperS, Character::upperT, Character::upperU,
        Character::upperV, Character::upperW, Character::upperX,
        Character::upperY, Character::upperZ,
        Character::diaeresis, Character::overbar, Character::leftCaret,
        Character::lessThanOrEqual, Character::equal,
        Character::greaterThanOrEqual,
        Character::rightCaret, Character::notEqual, Character::downCaret,
        Character::upCaret, Character::bar, Character::divide,
        Character::plus, Character::multiply, Character::query,
        Character::omega, Character::epsilon, Character::rho,
        Character::tilde, Character::upArrow, Character::downArrow,
        Character::iota, Character::circle, Character::star,
        Character::rightArrow, Character::leftArrow, Character::alpha,
        Character::upStile, Character::downStile, Character::underbar,
        Character::jot, Character::leftParenthesis, Character::rightParenthesis,
        Character::leftBracket, Character::rightBracket, Character::leftShoe,
        Character::rightShoe, Character::upShoe, Character::downShoe,
        Character::upTack, Character::downTack, Character::stile,
        Character::semicolon, Character::colon, Character::backSlash,
        Character::comma, Character::dot, Character::slash,
        Character::delStile, Character::deltaStile, Character::circleStile,
        Character::circleBackslash, Character::circleBar, Character::circleStar,
        Character::downCaretTilde, Character::upCaretTilde, Character::quoteDot,
        Character::quadDivide, Character::upTackJot, Character::downTackJot,
        Character::backSlashBar, Character::slashBar, Character::diaeresisJot,
        Character::commaBar, Character::diaeresisTilde, Character::leftBrace,
        Character::rightBrace, Character::rightTack, Character::leftTack,
        Character::dollarSign,
        Character::zero, Character::one, Character::two,
        Character::three, Character::four, Character::five,
        Character::six, Character::seven, Character::eight,
        Character::nine,
        Character::blank, Character::upShoeJot, Character::del,
        Character::delTilde, Character::quad, Character::quoteQuad,
        Character::diamond,
    });

    const std::vector<Char> any({
        Character::lowerA, Character::lowerB, Character::lowerC,
        Character::lowerD, Character::lowerE, Character::lowerF,
        Character::lowerG, Character::lowerH, Character::lowerI,
        Character::lowerJ, Character::lowerK, Character::lowerL,
        Character::lowerM, Character::lowerN, Character::lowerO,
        Character::lowerP, Character::lowerQ, Character::lowerR,
        Character::lowerS, Character::lowerT, Character::lowerU,
        Character::lowerV, Character::lowerW, Character::lowerX,
        Character::lowerY, Character::lowerZ,
        Character::upperA, Character::upperB, Character::upperC,
        Character::upperD, Character::upperE, Character::upperF,
        Character::upperG, Character::upperH, Character::upperI,
        Character::upperJ, Character::upperK, Character::upperL,
        Character::upperM, Character::upperN, Character::upperO,
        Character::upperP, Character::upperQ, Character::upperR,
        Character::upperS, Character::upperT, Character::upperU,
        Character::upperV, Character::upperW, Character::upperX,
        Character::upperY, Character::upperZ,
        Character::diaeresis, Character::overbar, Character::leftCaret,
        Character::lessThanOrEqual, Character::equal,
        Character::greaterThanOrEqual,
        Character::rightCaret, Character::notEqual, Character::downCaret,
        Character::upCaret, Character::bar, Character::divide,
        Character::plus, Character::multiply, Character::query,
        Character::omega, Character::epsilon, Character::rho,
        Character::tilde, Character::upArrow, Character::downArrow,
        Character::iota, Character::circle, Character::star,
        Character::rightArrow, Character::leftArrow, Character::alpha,
        Character::upStile, Character::downStile, Character::underbar,
        Character::jot, Character::leftParenthesis, Character::rightParenthesis,
        Character::leftBracket, Character::rightBracket, Character::leftShoe,
        Character::rightShoe, Character::upShoe, Character::downShoe,
        Character::upTack, Character::downTack, Character::stile,
        Character::semicolon, Character::colon, Character::backSlash,
        Character::comma, Character::dot, Character::slash,
        Character::delStile, Character::deltaStile, Character::circleStile,
        Character::circleBackslash, Character::circleBar, Character::circleStar,
        Character::downCaretTilde, Character::upCaretTilde, Character::quoteDot,
        Character::quadDivide, Character::upTackJot, Character::downTackJot,
        Character::backSlashBar, Character::slashBar, Character::diaeresisJot,
        Character::commaBar, Character::diaeresisTilde, Character::leftBrace,
        Character::rightBrace, Character::rightTack, Character::leftTack,
        Character::dollarSign,
        Character::zero, Character::one, Character::two,
        Character::three, Character::four, Character::five,
        Character::six, Character::seven, Character::eight,
        Character::nine,
        Character::blank, Character::upShoeJot, Character::del,
        Character::delTilde, Character::quad, Character::quoteQuad,
        Character::diamond,
        Character::quote,
    });
};



