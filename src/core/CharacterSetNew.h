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
#include "uni_algo/conv.h"
#include "Types.h"
/*
namespace Characters {
    // Lower English alphabet characters.
    const std::u32string lowerA = U"a";
    const std::u32string lowerA = U"a";
    const std::u32string lowerB = U"b";
    const std::u32string lowerC = U"c";
    const std::u32string lowerD = U"d";
    const std::u32string lowerE = U"e";
    const std::u32string lowerF = U"f";
    const std::u32string lowerG = U"g";
    const std::u32string lowerH = U"h";
    const std::u32string lowerI = U"i";
    const std::u32string lowerJ = U"j";
    const std::u32string lowerK = U"k";
    const std::u32string lowerL = U"l";
    const std::u32string lowerM = U"m";
    const std::u32string lowerN = U"n";
    const std::u32string lowerO = U"o";
    const std::u32string lowerP = U"p";
    const std::u32string lowerQ = U"q";
    const std::u32string lowerR = U"r";
    const std::u32string lowerS = U"s";
    const std::u32string lowerT = U"t";
    const std::u32string lowerU = U"u";
    const std::u32string lowerV = U"v";
    const std::u32string lowerW = U"w";
    const std::u32string lowerX = U"x";
    const std::u32string lowerY = U"y";
    const std::u32string lowerZ = U"z";

    // Upper English alphabet characters.
    const std::u32string upperA = U"A";
    const std::u32string upperB = U"B";
    const std::u32string upperC = U"C";
    const std::u32string upperD = U"D";
    const std::u32string upperE = U"E";
    const std::u32string upperF = U"F";
    const std::u32string upperG = U"G";
    const std::u32string upperH = U"H";
    const std::u32string upperI = U"I";
    const std::u32string upperJ = U"J";
    const std::u32string upperK = U"K";
    const std::u32string upperL = U"L";
    const std::u32string upperM = U"M";
    const std::u32string upperN = U"N";
    const std::u32string upperO = U"O";
    const std::u32string upperP = U"P";
    const std::u32string upperQ = U"Q";
    const std::u32string upperR = U"R";
    const std::u32string upperS = U"S";
    const std::u32string upperT = U"T";
    const std::u32string upperU = U"U";
    const std::u32string upperV = U"V";
    const std::u32string upperW = U"W";
    const std::u32string upperX = U"X";
    const std::u32string upperY = U"Y";
    const std::u32string upperZ = U"Z";

    // Numeric characters.
    const std::u32string zero = U"0";
    const std::u32string one = U"1";
    const std::u32string two = U"2";
    const std::u32string three = U"3";
    const std::u32string four = U"4";
    const std::u32string five = U"5";
    const std::u32string six = U"6";
    const std::u32string seven = U"7";
    const std::u32string eight = U"8";
    const std::u32string nine = U"9";

    // Special characters.
    const std::u32string alpha = U"⍺";
    const std::u32string downArrow = U"↓";
    const std::u32string leftArrow = U"←";
    const std::u32string rightArrow = U"→";
    const std::u32string upArrow = U"↑";
    const std::u32string bar = U"-";
    const std::u32string blank = U" ";
    const std::u32string leftBrace = U"{";
    const std::u32string rightBrace = U"}";
    const std::u32string leftBracket = U"[";
    const std::u32string rightBracket = U"]";
    const std::u32string downCaret = U"∨";
    const std::u32string downCaretTilde = U"⍱";
    const std::u32string leftCaret = U"<";
    const std::u32string rightCaret = U">";
    const std::u32string upCaret = U"∧";
    const std::u32string upCaretTilde = U"⍲";
    const std::u32string circle = U"○";
    const std::u32string circleBackslash = U"⍉";
    const std::u32string circleBar = U"⊖";
    const std::u32string circleStar = U"⍟";
    const std::u32string circleStile = U"⌽";
    const std::u32string colon = U":";
    const std::u32string comma = U",";
    const std::u32string commaBar = U"⍪";
    const std::u32string del = U"∇";
    const std::u32string delStile = U"⍒";

    const std::u32string delTilde = U"⍫";
    const std::u32string delta = U"∆";
    const std::u32string deltaStile = U"⍋";
    const std::u32string deltaUnderbar = U"⍙";
    const std::u32string diaeresis = U"¨";
    const std::u32string diamond = U"⋄";
    const std::u32string divide = U"÷";
    const std::u32string dollarSign = U"$";
    const std::u32string dot = U".";
    const std::u32string epsilon = U"∊";
    const std::u32string equal = U"=";
    const std::u32string greaterThanOrEqual = U"≥";
    const std::u32string iota = U"⍳";
    const std::u32string jot = U"∘";
    const std::u32string lessThanOrEqual = U"≤";
    const std::u32string multiply = U"×";
    const std::u32string notEqual = U"≠";
    const std::u32string overbar = U"‾";
    const std::u32string leftParenthesis = U"(";
    const std::u32string rightParenthesis = U")";
    const std::u32string plus = U"+";
    const std::u32string quad = U"⎕";
    const std::u32string quadDivide = U"⌹";
    const std::u32string query = U"?";
    const std::u32string diaeresisJot = U"⍤";
    const std::u32string quote = U"\'";
    const std::u32string quoteDot = U"!";

    const std::u32string quoteQuad = U"⍞";
    const std::u32string rho = U"⍴";
    const std::u32string semicolon = U";";
    const std::u32string downShoe = U"∪";
    const std::u32string leftShoe = U"⊂";
    const std::u32string rightShoe = U"⊃";
    const std::u32string upShoe = U"∩";
    const std::u32string upShoeJot = U"⍝";
    const std::u32string slash = U"/";
    const std::u32string backSlash = U"\\";
    const std::u32string slashBar = U"⌿";
    const std::u32string backSlashBar = U"⍀";
    const std::u32string star = U"*";
    const std::u32string stile = U"|";
    const std::u32string downStile = U"⌊";
    const std::u32string upStile = U"⌈";
    const std::u32string upTack = U"⊥";
    const std::u32string upTackJot = U"⍎";
    const std::u32string rightTack = U"⊢";
    const std::u32string leftTack = U"⊣";
    const std::u32string downTack = U"⊤";
    const std::u32string downTackJot = U"⍕";
    const std::u32string tilde = U"~";
    const std::u32string underbar = U"_";
    const std::u32string diaeresisTilde = U"⍨";
    const std::u32string omega = U"⍵";
    const std::u32string equalUnderbar = U"≡";


    const std::string regex_nonquote = uni::utf32to8(
            U"["
            );

    const std::string regex_statement_separator = uni::utf32to8(diamond);

    const std::string regex_letter = uni::utf32to8(
            U"[" + lowerA + lowerB + lowerC + lowerD + lowerE + lowerF
            + lowerG + lowerH + lowerI + lowerJ + lowerK + lowerL
            + lowerM + lowerN + lowerO + lowerP + lowerQ + lowerR
            + lowerS + lowerT + lowerU + lowerV + lowerW + lowerY
            + lowerZ + delta
            + upperA + upperB + upperC + upperD + upperE + upperF
            + upperG + upperH + upperI + upperJ + upperK + upperL
            + upperM + upperN + upperO + upperP + upperQ + upperR
            + upperS + upperT + upperU + upperV + upperW + upperY
            + upperZ + deltaUnderbar + U"]");

    const std::string regex_digit = uni::utf32to8(
            U"[" + one + two + three + four + five + six + seven + U"]"
            );

    const std::string regex_ideogram = uni::utf32to8(
            U"[" + diaeresis + overbar + leftCaret
            + lessThanOrEqual + equal + greaterThanOrEqual
            + rightCaret + notEqual + downCaret
            + upCaret + bar + divide
            + plus + multiply + query
            + omega + epsilon + rho
            + tilde + upArrow + downArrow
            + iota + circle + star
            + rightArrow + leftArrow + alpha
            + upStile + downStile + underbar
            + jot + leftParenthesis + rightParenthesis
            + leftBracket + rightBracket + leftShoe
            + rightShoe + upShoe + downShoe
            + upTack + downTack + stile
            + semicolon + colon + backSlash
            + comma + dot + slash
            + delStile + deltaStile + circleStile
            + circleBackslash + circleBar + circleStar
            + downCaretTilde + upCaretTilde + quoteDot
            + quadDivide + upTackJot + downTackJot
            + backSlashBar + slashBar + diaeresisJot
            + commaBar + diaeresisTilde + leftBrace
            + rightBrace + rightTack + leftTack
            + dollarSign + U"]"
            );
};



*/