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
#include <vector>

/*
struct Character {
    std::vector<std::u32string> representations;

    Character(std::vector<std::u32string> &&);

    friend std::ostream& operator<<(std::ostream &, const Character &);
};

struct CharacterGroup {
    std::vector<Character> members;

    CharacterGroup(std::vector<Character> && members);
};


namespace CharacterSet {
    const Character lowerA({U"a"});
    const Character lowerB({U"b"});
    const Character lowerC({U"c"});
    const Character lowerD({U"d"});
    const Character lowerE({U"e"});
    const Character lowerF({U"f"});
    const Character lowerG({U"g"});
    const Character lowerH({U"h"});
    const Character lowerI({U"i"});
    const Character lowerJ({U"j"});
    const Character lowerK({U"k"});
    const Character lowerL({U"l"});
    const Character lowerM({U"m"});
    const Character lowerN({U"n"});
    const Character lowerO({U"o"});
    const Character lowerP({U"p"});
    const Character lowerQ({U"q"});
    const Character lowerR({U"r"});
    const Character lowerS({U"s"});
    const Character lowerT({U"t"});
    const Character lowerU({U"u"});
    const Character lowerV({U"v"});
    const Character lowerW({U"w"});
    const Character lowerX({U"x"});
    const Character lowerY({U"y"});
    const Character lowerZ({U"z"});

    const Character upperA({U"A"});
    const Character upperB({U"B"});
    const Character upperC({U"C"});
    const Character upperD({U"D"});
    const Character upperE({U"E"});
    const Character upperF({U"F"});
    const Character upperG({U"G"});
    const Character upperH({U"H"});
    const Character upperI({U"I"});
    const Character upperJ({U"J"});
    const Character upperK({U"K"});
    const Character upperL({U"L"});
    const Character upperM({U"M"});
    const Character upperN({U"N"});
    const Character upperO({U"O"});
    const Character upperP({U"P"});
    const Character upperQ({U"Q"});
    const Character upperR({U"R"});
    const Character upperS({U"S"});
    const Character upperT({U"T"});
    const Character upperU({U"U"});
    const Character upperV({U"V"});
    const Character upperW({U"W"});
    const Character upperX({U"X"});
    const Character upperY({U"Y"});
    const Character upperZ({U"Z"});

    const Character zero({U"0"});
    const Character one({U"1"});
    const Character two({U"2"});
    const Character three({U"3"});
    const Character four({U"4"});
    const Character five({U"5"});
    const Character six({U"6"});
    const Character seven({U"7"});
    const Character eight({U"8"});
    const Character nine({U"9"});

    // Special characters.
    const Character alpha({U"⍺"});
    const Character downArrow({U"↓"});
    const Character leftArrow({U"←"});
    const Character rightArrow({U"→"});
    const Character upArrow({U"↑"});
    const Character bar({U"-"});
    const Character blank({U" "});
    const Character leftBrace({U"{"});
    const Character rightBrace({U"}"});
    const Character leftBracket({U"["});
    const Character rightBracket({U"]"});
    const Character downCaret({U"∨"});
    const Character downCaretTilde({U"⍱"});
    const Character leftCaret({U"<"});
    const Character rightCaret({U">"});
    const Character upCaret({U"∧"});
    const Character upCaretTilde({U"⍲"});
    const Character circle({U"○"});
    const Character circleBackslash({U"⍉"});
    const Character circleBar({U"⊖"});
    const Character circleStar({U"⍟"});
    const Character circleStile({U"⌽"});
    const Character colon({U":"});
    const Character comma({U","});
    const Character commaBar({U"⍪"});
    const Character del({U"∇"});
    const Character delStile({U"⍒"});

    const Character delTilde({U"⍫"});
    const Character delta({U"∆"});
    const Character deltaStile({U"⍋"});
    const Character deltaUnderbar({U"⍙"});
    const Character diaeresis({U"¨"});
    const Character diamond({U"⋄"});
    const Character divide({U"÷"});
    const Character dollarSign({U"$"});
    const Character dot({U"."});
    const Character epsilon({U"∊"});
    const Character equal({U"="});
    const Character greaterThanOrEqual({U"≥"});
    const Character iota({U"⍳"});
    const Character jot({U"∘"});
    const Character lessThanOrEqual({U"≤"});
    const Character multiply({U"×"});
    const Character notEqual({U"≠"});
    const Character overbar({U"‾"});
    const Character leftParenthesis({U"("});
    const Character rightParenthesis({U")"});
    const Character plus({U"+"});
    const Character quad({U"⎕"});
    const Character quadDivide({U"⌹"});
    const Character query({U"?"});
    const Character diaeresisJot({U"⍤"});
    const Character quote({U"\'"});
    const Character quoteDot({U"!"});

    const Character quoteQuad({U"⍞"});
    const Character rho({U"⍴"});
    const Character semicolon({U";"});
    const Character downShoe({U"∪"});
    const Character leftShoe({U"⊂"});
    const Character rightShoe({U"⊃"});
    const Character upShoe({U"∩"});
    const Character upShoeJot({U"⍝"});
    const Character slash({U"/"});
    const Character backSlash({U"\\"});
    const Character slashBar({U"⌿"});
    const Character backSlashBar({U"⍀"});
    const Character star({U"*"});
    const Character stile({U"|"});
    const Character downStile({U"⌊"});
    const Character upStile({U"⌈"});
    const Character upTack({U"⊥"});
    const Character upTackJot({U"⍎"});
    const Character rightTack({U"⊢"});
    const Character leftTack({U"⊣"});
    const Character downTack({U"⊤"});
    const Character downTackJot({U"⍕"});
    const Character tilde({U"~"});
    const Character underbar({U"_"});
    const Character diaeresisTilde({U"⍨"});
    const Character omega({U"⍵"});
    const Character equalUnderbar({U"≡"});
};

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