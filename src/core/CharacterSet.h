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

namespace CharacterSet {
    // Lower English alphabet characters.
    const Char lowerA = u'a';
    const Char lowerB = u'b';
    const Char lowerC = u'c';
    const Char lowerD = u'd';
    const Char lowerE = u'e';
    const Char lowerF = u'f';
    const Char lowerG = u'g';
    const Char lowerH = u'h';
    const Char lowerI = u'i';
    const Char lowerJ = u'j';
    const Char lowerK = u'k';
    const Char lowerL = u'l';
    const Char lowerM = u'm';
    const Char lowerN = u'n';
    const Char lowerO = u'o';
    const Char lowerP = u'p';
    const Char lowerQ = u'q';
    const Char lowerR = u'r';
    const Char lowerS = u's';
    const Char lowerT = u't';
    const Char lowerU = u'u';
    const Char lowerV = u'v';
    const Char lowerW = u'w';
    const Char lowerX = u'x';
    const Char lowerY = u'y';
    const Char lowerZ = u'z';

    // Upper English alphabet characters.
    const Char upperA = u'A';
    const Char upperB = u'B';
    const Char upperC = u'C';
    const Char upperD = u'D';
    const Char upperE = u'E';
    const Char upperF = u'F';
    const Char upperG = u'G';
    const Char upperH = u'H';
    const Char upperI = u'I';
    const Char upperJ = u'J';
    const Char upperK = u'K';
    const Char upperL = u'L';
    const Char upperM = u'M';
    const Char upperN = u'N';
    const Char upperO = u'O';
    const Char upperP = u'P';
    const Char upperQ = u'Q';
    const Char upperR = u'R';
    const Char upperS = u'S';
    const Char upperT = u'T';
    const Char upperU = u'U';
    const Char upperV = u'V';
    const Char upperW = u'W';
    const Char upperX = u'X';
    const Char upperY = u'Y';
    const Char upperZ = u'Z';

    // Numeric characters.
    const Char zero = u'0';
    const Char one = u'1';
    const Char two = u'2';
    const Char three = u'3';
    const Char four = u'4';
    const Char five = u'5';
    const Char six = u'6';
    const Char seven = u'7';
    const Char eight = u'8';
    const Char nine = u'9';

    // Special characters.
    const Char alpha = u'⍺';
    const Char downArrow = u'↓';
    const Char leftArrow = u'←';
    const Char rightArrow = u'→';
    const Char upArrow = u'↑';
    const Char bar = u'-';
    const Char blank = u' ';
    const Char leftBrace = u'{';
    const Char rightBrace = u'}';
    const Char leftBracket = u'[';
    const Char rightBracket = u']';
    const Char downCaret = u'∨';
    const Char downCaretTilde = u'⍱';
    const Char leftCaret = u'<';
    const Char rightCaret = u'>';
    const Char upCaret = u'∧';
    const Char upCaretTilde = u'⍲';
    const Char circle = u'○';
    const Char circleBackslash = u'⍉';
    const Char circleBar = u'⊖';
    const Char circleStar = u'⍟';
    const Char circleStile = u'⌽';
    const Char colon = u':';
    const Char comma = u',';
    const Char commaBar = u'⍪';
    const Char del = u'∇';
    const Char delStile = u'⍒';

    const Char delTilde = u'⍫';
    const Char delta = u'∆';
    const Char deltaStile = u'⍋';
    const Char deltaUnderbar = u'⍙';
    const Char diaeresis = u'¨';
    const Char diamond = u'⋄';
    const Char divide = u'÷';
    const Char dollarSign = u'$';
    const Char dot = u'.';
    const Char epsilon = u'∊';
    const Char equal = u'=';
    const Char greaterThanOrEqual = u'≥';
    const Char iota = u'⍳';
    const Char jot = u'∘';
    const Char lessThanOrEqual = u'≤';
    const Char multiply = u'×';
    const Char notEqual = u'≠';
    const Char overbar = u'‾';
    const Char leftParenthesis = u'(';
    const Char rightParenthesis = u')';
    const Char plus = u'+';
    const Char quad = u'⎕';
    const Char quadDivide = u'⌹';
    const Char query = u'?';
    const Char diaeresisJot = u'⍤';
    const Char quote = u'\'';
    const Char quoteDot = u'!';

    const Char quoteQuad = u'⍞';
    const Char rho = u'⍴';
    const Char semicolon = u';';
    const Char downShoe = u'∪';
    const Char leftShoe = u'⊂';
    const Char rightShoe = u'⊃';
    const Char upShoe = u'∩';
    const Char upShoeJot = u'⍝';
    const Char slash = u'/';
    const Char backSlash = u'\\';
    const Char slashBar = u'⌿';
    const Char backSlashBar = u'⍀';
    const Char star = u'*';
    const Char stile = u'|';
    const Char downStile = u'⌊';
    const Char upStile = u'⌈';
    const Char upTack = u'⊥';
    const Char upTackJot = u'⍎';
    const Char rightTack = u'⊢';
    const Char leftTack = u'⊣';
    const Char downTack = u'⊤';
    const Char downTackJot = u'⍕';
    const Char tilde = u'~';
    const Char underbar = u'_';
    const Char diaeresisTilde = u'⍨';
    const Char omega = u'⍵';
    const Char equalUnderbar = u'≡';
};



