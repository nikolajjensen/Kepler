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
#include "UnicodeCharacter.h"

namespace CharacterSet {
    const UnicodeCharacter lowerA(U'a');
    const UnicodeCharacter lowerB(U'b');
    const UnicodeCharacter lowerC(U'c');
    const UnicodeCharacter lowerD(U'd');
    const UnicodeCharacter lowerE(U'e');
    const UnicodeCharacter lowerF(U'f');
    const UnicodeCharacter lowerG(U'g');
    const UnicodeCharacter lowerH(U'h');
    const UnicodeCharacter lowerI(U'i');
    const UnicodeCharacter lowerJ(U'j');
    const UnicodeCharacter lowerK(U'k');
    const UnicodeCharacter lowerL(U'l');
    const UnicodeCharacter lowerM(U'm');
    const UnicodeCharacter lowerN(U'n');
    const UnicodeCharacter lowerO(U'o');
    const UnicodeCharacter lowerP(U'p');
    const UnicodeCharacter lowerQ(U'q');
    const UnicodeCharacter lowerR(U'r');
    const UnicodeCharacter lowerS(U's');
    const UnicodeCharacter lowerT(U't');
    const UnicodeCharacter lowerU(U'u');
    const UnicodeCharacter lowerV(U'v');
    const UnicodeCharacter lowerW(U'w');
    const UnicodeCharacter lowerX(U'x');
    const UnicodeCharacter lowerY(U'y');
    const UnicodeCharacter lowerZ(U'z');

    const UnicodeCharacter upperA(U'A');
    const UnicodeCharacter upperB(U'B');
    const UnicodeCharacter upperC(U'C');
    const UnicodeCharacter upperD(U'D');
    const UnicodeCharacter upperE(U'E');
    const UnicodeCharacter upperF(U'F');
    const UnicodeCharacter upperG(U'G');
    const UnicodeCharacter upperH(U'H');
    const UnicodeCharacter upperI(U'I');
    const UnicodeCharacter upperJ(U'J');
    const UnicodeCharacter upperK(U'K');
    const UnicodeCharacter upperL(U'L');
    const UnicodeCharacter upperM(U'M');
    const UnicodeCharacter upperN(U'N');
    const UnicodeCharacter upperO(U'O');
    const UnicodeCharacter upperP(U'P');
    const UnicodeCharacter upperQ(U'Q');
    const UnicodeCharacter upperR(U'R');
    const UnicodeCharacter upperS(U'S');
    const UnicodeCharacter upperT(U'T');
    const UnicodeCharacter upperU(U'U');
    const UnicodeCharacter upperV(U'V');
    const UnicodeCharacter upperW(U'W');
    const UnicodeCharacter upperX(U'X');
    const UnicodeCharacter upperY(U'Y');
    const UnicodeCharacter upperZ(U'Z');

    const UnicodeCharacter zero(U'0');
    const UnicodeCharacter one(U'1');
    const UnicodeCharacter two(U'2');
    const UnicodeCharacter three(U'3');
    const UnicodeCharacter four(U'4');
    const UnicodeCharacter five(U'5');
    const UnicodeCharacter six(U'6');
    const UnicodeCharacter seven(U'7');
    const UnicodeCharacter eight(U'8');
    const UnicodeCharacter nine(U'9');

    // Special characters.
    const UnicodeCharacter alpha(U'⍺');
    const UnicodeCharacter downArrow(U'↓');
    const UnicodeCharacter leftArrow(U'←');
    const UnicodeCharacter rightArrow(U'→');
    const UnicodeCharacter upArrow(U'↑');
    const UnicodeCharacter bar(U'-');
    const UnicodeCharacter blank(U' ');
    const UnicodeCharacter leftBrace(U'{');
    const UnicodeCharacter rightBrace(U'}');
    const UnicodeCharacter leftBracket(U'[');
    const UnicodeCharacter rightBracket(U']');
    const UnicodeCharacter downCaret(U'∨');
    const UnicodeCharacter downCaretTilde(U'⍱');
    const UnicodeCharacter leftCaret(U'<');
    const UnicodeCharacter rightCaret(U'>');
    const UnicodeCharacter upCaret(U'∧');
    const UnicodeCharacter upCaretTilde(U'⍲');
    const UnicodeCharacter circle(U'○');
    const UnicodeCharacter circleBackslash(U'⍉');
    const UnicodeCharacter circleBar(U'⊖');
    const UnicodeCharacter circleStar(U'⍟');
    const UnicodeCharacter circleStile(U'⌽');
    const UnicodeCharacter colon(U':');
    const UnicodeCharacter comma(U',');
    const UnicodeCharacter commaBar(U'⍪');
    const UnicodeCharacter del(U'∇');
    const UnicodeCharacter delStile(U'⍒');

    const UnicodeCharacter delTilde(U'⍫');
    const UnicodeCharacter delta(U'∆');
    const UnicodeCharacter deltaStile(U'⍋');
    const UnicodeCharacter deltaUnderbar(U'⍙');
    const UnicodeCharacter diaeresis(U'¨');
    const UnicodeCharacter diamond(U'⋄');
    const UnicodeCharacter divide(U'÷');
    const UnicodeCharacter dollarSign(U'$');
    const UnicodeCharacter dot(U'.');
    const UnicodeCharacter epsilon(U'∊');
    const UnicodeCharacter equal(U'=');
    const UnicodeCharacter greaterThanOrEqual(U'≥');
    const UnicodeCharacter iota(U'⍳');
    const UnicodeCharacter jot(U'∘');
    const UnicodeCharacter lessThanOrEqual(U'≤');
    const UnicodeCharacter multiply(U'×');
    const UnicodeCharacter notEqual(U'≠');
    const UnicodeCharacter overbar(U'‾');
    const UnicodeCharacter leftParenthesis(U'(');
    const UnicodeCharacter rightParenthesis(U')');
    const UnicodeCharacter plus(U'+');
    const UnicodeCharacter quad(U'⎕');
    const UnicodeCharacter quadDivide(U'⌹');
    const UnicodeCharacter query(U'?');
    const UnicodeCharacter diaeresisJot(U'⍤');
    const UnicodeCharacter quote(U'\'');
    const UnicodeCharacter quoteDot(U'!');

    const UnicodeCharacter quoteQuad(U'⍞');
    const UnicodeCharacter rho(U'⍴');
    const UnicodeCharacter semicolon(U';');
    const UnicodeCharacter downShoe(U'∪');
    const UnicodeCharacter leftShoe(U'⊂');
    const UnicodeCharacter rightShoe(U'⊃');
    const UnicodeCharacter upShoe(U'∩');
    const UnicodeCharacter upShoeJot(U'⍝');
    const UnicodeCharacter slash(U'/');
    const UnicodeCharacter backSlash(U'\\');
    const UnicodeCharacter slashBar(U'⌿');
    const UnicodeCharacter backSlashBar(U'⍀');
    const UnicodeCharacter star(U'*');
    const UnicodeCharacter stile(U'|');
    const UnicodeCharacter downStile(U'⌊');
    const UnicodeCharacter upStile(U'⌈');
    const UnicodeCharacter upTack(U'⊥');
    const UnicodeCharacter upTackJot(U'⍎');
    const UnicodeCharacter rightTack(U'⊢');
    const UnicodeCharacter leftTack(U'⊣');
    const UnicodeCharacter downTack(U'⊤');
    const UnicodeCharacter downTackJot(U'⍕');
    const UnicodeCharacter tilde(U'~');
    const UnicodeCharacter underbar(U'_');
    const UnicodeCharacter diaeresisTilde(U'⍨');
    const UnicodeCharacter omega(U'⍵');
    const UnicodeCharacter equalUnderbar(U'≡');
};

/*
namespace CharacterSet {
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

    const std::vector<Char> digit({
       CharacterSet::zero, CharacterSet::one, CharacterSet::two,
       CharacterSet::three, CharacterSet::four, CharacterSet::five,
       CharacterSet::six, CharacterSet::seven, CharacterSet::eight,
       CharacterSet::nine,
    });

    const std::vector<Char> ideogram({
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

    const std::vector<Char> nonquote({
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
        CharacterSet::diaeresis, CharacterSet::overbar, CharacterSet::leftCaret,
        CharacterSet::lessThanOrEqual, CharacterSet::equal,
        CharacterSet::greaterThanOrEqual,
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
        CharacterSet::zero, CharacterSet::one, CharacterSet::two,
        CharacterSet::three, CharacterSet::four, CharacterSet::five,
        CharacterSet::six, CharacterSet::seven, CharacterSet::eight,
        CharacterSet::nine,
        CharacterSet::blank, CharacterSet::upShoeJot, CharacterSet::del,
        CharacterSet::delTilde, CharacterSet::quad, CharacterSet::quoteQuad,
        CharacterSet::diamond,
    });

    const std::vector<Char> any({
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
        CharacterSet::diaeresis, CharacterSet::overbar, CharacterSet::leftCaret,
        CharacterSet::lessThanOrEqual, CharacterSet::equal,
        CharacterSet::greaterThanOrEqual,
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
        CharacterSet::zero, CharacterSet::one, CharacterSet::two,
        CharacterSet::three, CharacterSet::four, CharacterSet::five,
        CharacterSet::six, CharacterSet::seven, CharacterSet::eight,
        CharacterSet::nine,
        CharacterSet::blank, CharacterSet::upShoeJot, CharacterSet::del,
        CharacterSet::delTilde, CharacterSet::quad, CharacterSet::quoteQuad,
        CharacterSet::diamond,
        CharacterSet::quote,
    });
};
*/