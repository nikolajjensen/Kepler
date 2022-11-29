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
#include <iostream>
#include "Token.h"
#include "CharacterSet.h"
#include "../src/core/sequence/Sequence.h"
#include "../src/core/sequence/SequenceBuilder.h"
#include "UnicodeCharacter.h"
#include "UnicodeString.h"
#include <functional>

class Lexer {
public:
    explicit Lexer(CharList input, bool debugOn = false);

    std::vector<Token> run();

protected:
    bool debugOn;

    UnicodeString input;
    UnicodeString content;
    std::vector<Token> tokens;

    std::function<void(UnicodeCharacter&)> idle = [](UnicodeCharacter &){
        //std::cout << "Idle! " << std::endl;
    };

    std::function<void(UnicodeCharacter&)> clear = [&](UnicodeCharacter &){
        std::cout << "Clearing content! " << std::endl;
        content.clear();
    };

    std::function<void(UnicodeCharacter&)> append = [&](UnicodeCharacter & c){
        std::cout << "Appending content! " << std::endl;
        content.push_back(c);
    };

    std::function<void(TokenType, UnicodeCharacter&)> tokenize = [&](TokenType token_type, UnicodeCharacter &_){
        std::cout << "Tokenizing into: " << token_type << std::endl;
        tokens.emplace_back(token_type, content);
        content.clear();
    };


    Sequence<UnicodeCharacter> diamond = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::diamond)
                                            .build(append);

    Sequence<UnicodeCharacter> quote_quad = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::quoteQuad)
                                            .build(append);

    Sequence<UnicodeCharacter> quad = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::quad)
                                            .build(append);

    Sequence<UnicodeCharacter> lamp = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::upShoeJot)
                                            .build(append);

    Sequence<UnicodeCharacter> del_tilde = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::delTilde)
                                            .build(append);

    Sequence<UnicodeCharacter> del = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::del)
                                            .build(append);

    Sequence<UnicodeCharacter> blank = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::blank)
                                            .build(append);

    Sequence<UnicodeCharacter> overbar = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::overbar)
                                            .build(append);

    Sequence<UnicodeCharacter> underbar = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::underbar)
                                            .build(append);

    Sequence<UnicodeCharacter> dot = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::dot)
                                            .build(append);

    Sequence<UnicodeCharacter> complex_marker = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::upperJ)
                                            .build(append);

    Sequence<UnicodeCharacter> exponent_marker = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::upperE)
                                            .build(append);

    Sequence<UnicodeCharacter> quote = SequenceBuilder<UnicodeCharacter>()
                                            .one(CharacterSet::quote)
                                            .build(append);

    Sequence<UnicodeCharacter> ideogram = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({
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
                                             })
                                            .build(append);

    Sequence<UnicodeCharacter> digit = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({
                                                 CharacterSet::zero, CharacterSet::one, CharacterSet::two,
                                                 CharacterSet::three, CharacterSet::four, CharacterSet::five,
                                                 CharacterSet::six, CharacterSet::seven, CharacterSet::eight,
                                                 CharacterSet::nine,
                                            })
                                            .build(append);

    Sequence<UnicodeCharacter> letter = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({
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
                                                 CharacterSet::deltaUnderbar, CharacterSet::delta,
                                            })
                                            .build(append);


    Sequence<UnicodeCharacter> statement_separator = SequenceBuilder<UnicodeCharacter>()
                                            .one(diamond)
                                            .build(append);

    Sequence<UnicodeCharacter> nonquote = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({
                                                &ideogram,
                                                &digit,
                                                &blank,
                                                &letter,
                                                &lamp,
                                                &del,
                                                &del_tilde,
                                                &quad,
                                                &quote_quad,
                                                &diamond,
                                            })
                                            .build(idle);

    Sequence<UnicodeCharacter> space = SequenceBuilder<UnicodeCharacter>()
                                            .one(blank)
                                            .build(clear);

    Sequence<UnicodeCharacter> primitive = SequenceBuilder<UnicodeCharacter>()
                                            .one(ideogram)
                                            .build(std::bind(tokenize, TokenType::Primitive, std::placeholders::_1));

    Sequence<UnicodeCharacter> any = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({&quote, &nonquote})
                                            .build(idle);

    Sequence<UnicodeCharacter> comment = SequenceBuilder<UnicodeCharacter>()
                                            .one(lamp)
                                            .many(any, false)
                                            .build(clear);

    Sequence<UnicodeCharacter> _single_character_literal = SequenceBuilder<UnicodeCharacter>()
                                            .one(quote)
                                            .many(nonquote, false)
                                            .one(quote)
                                            .build(append);

    Sequence<UnicodeCharacter> character_literal = SequenceBuilder<UnicodeCharacter>()
                                            .many(_single_character_literal, true)
                                            .build(clear);

    Sequence<UnicodeCharacter> exponent = SequenceBuilder<UnicodeCharacter>()
                                            .one(exponent_marker)
                                            .one(overbar, false)
                                            .many(digit, true)
                                            .build(idle);

    Sequence<UnicodeCharacter> _one_real_scalar = SequenceBuilder<UnicodeCharacter>()
                                            .many(digit)
                                            .one(dot, false)
                                            .build(idle);

    Sequence<UnicodeCharacter> _two_real_scalar = SequenceBuilder<UnicodeCharacter>()
                                            .many(digit)
                                            .one(dot)
                                            .many(digit)
                                            .build(idle);

    Sequence<UnicodeCharacter> _three_real_scalar = SequenceBuilder<UnicodeCharacter>()
                                            .one(dot)
                                            .many(digit)
                                            .build(idle);

    Sequence<UnicodeCharacter> real_scalar_literal = SequenceBuilder<UnicodeCharacter>()
                                            .one(overbar, false)
                                            .anyOfEither({&_one_real_scalar, &_two_real_scalar, &_three_real_scalar})
                                            .one(exponent, false)
                                            .build(idle);

    Sequence<UnicodeCharacter> numeric_scalar_literal = SequenceBuilder<UnicodeCharacter>()
                                            .one(real_scalar_literal)
                                            .one(imaginary_part, false)
                                            .build(idle);

    Sequence<UnicodeCharacter> imaginary_part = SequenceBuilder<UnicodeCharacter>()
                                            .one(complex_marker)
                                            .one(real_scalar_literal)
                                            .build(idle);

    Sequence<UnicodeCharacter> _numeric_literal_atom = SequenceBuilder<UnicodeCharacter>()
                                            .one(numeric_scalar_literal)
                                            .many(blank)
                                            .build(idle);

    Sequence<UnicodeCharacter> numeric_literal = SequenceBuilder<UnicodeCharacter>()
                                            .many(_numeric_literal_atom)
                                            .build(std::bind(tokenize, TokenType::NumericLiteral, std::placeholders::_1));

    Sequence<UnicodeCharacter> _distinguished_identifier_atom_atom = SequenceBuilder<UnicodeCharacter>()
                                            .manyOfEither({&letter, &digit})
                                            .build(idle);

    Sequence<UnicodeCharacter> _distinguished_identifier_atom = SequenceBuilder<UnicodeCharacter>()
                                            .one(quad)
                                            .many(_distinguished_identifier_atom_atom, false)
                                            .build(idle);

    Sequence<UnicodeCharacter> distinguished_identifier = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({&quote_quad, &_distinguished_identifier_atom})
                                            .build(std::bind(tokenize, TokenType::DistinguishedIdentifier, std::placeholders::_1));

    Sequence<UnicodeCharacter> direct_identifier = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({CharacterSet::alpha, CharacterSet::omega})
                                            .build(idle);

    Sequence<UnicodeCharacter> _literal_identifier_atom = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({&letter, &digit, &underbar, &overbar})
                                            .build(idle);

    Sequence<UnicodeCharacter> literal_identifier = SequenceBuilder<UnicodeCharacter>()
                                            .one(letter)
                                            .many(_literal_identifier_atom, false)
                                            .build(std::bind(tokenize, TokenType::SimpleIdentifier, std::placeholders::_1));

    Sequence<UnicodeCharacter> simple_identifier = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({&literal_identifier, &direct_identifier})
                                            .build(idle);

    Sequence<UnicodeCharacter> identifier = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({&simple_identifier, &distinguished_identifier})
                                            .build(idle);

    Sequence<UnicodeCharacter> _line_one_atomic = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({&identifier, &numeric_scalar_literal})
                                            .build(idle);

    Sequence<UnicodeCharacter> _line_two_atomic = SequenceBuilder<UnicodeCharacter>()
                                            .anyOfEither({&primitive, &character_literal, &space, &statement_separator})
                                            .build(idle);

    Sequence<UnicodeCharacter> _line_three_atomic = SequenceBuilder<UnicodeCharacter>()
                                            .one(_line_one_atomic, false)
                                            .one(_line_two_atomic, false)
                                            .build(idle);

    Sequence<UnicodeCharacter> line = SequenceBuilder<UnicodeCharacter>()
                                            .many(_line_three_atomic, false)
                                            .one(comment, false)
                                            .build(idle);
};
