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

#include "Lexer.h"
#include "TokenType.h"
#include "CharacterSet.h"
#include <uni_algo/conv.h>
#include <iostream>
#include <utility>
#include <algorithm>
#include "Thread.h"

Lexer::Lexer(CharList _input, bool _debugOn) : input(std::move(_input)), debugOn(_debugOn), it(input.begin()), tokens(), thread(this) {}

void Lexer::log_thread_attempt(std::string &&type) {
    if (debugOn) {
        std::cout << "Threading " << type << " using substring: '" << uni::utf32to8(CharList(it, input.end())) << "'" << std::endl;
    }
}

void Lexer::log_thread_success(std::string &&type) {
    if (debugOn) {
        std::cout << "Threading " << type << " successful with token: '" << tokens.back() << "'" << std::endl;
    }
}

std::vector<Token> Lexer::run() {
    tokens.clear();
    it = input.begin();
    thread_line();
    std::cout << "Full input lexed? " << (it == input.end() ? "Yes" : "No") << "\n";
    return tokens;
}

unsigned int Lexer::thread_line() {
    log_thread_attempt("line");

    unsigned int threaded = 0;

    unsigned int lastone;

    do {
        lastone = thread.one(&Lexer::thread_identifier, true).one(&Lexer::thread_numeric_literal, true).thread();
        lastone += thread.one(&Lexer::thread_primitive, true).one(&Lexer::thread_character_literal, true).one(&Lexer::thread_space, true).one(&Lexer::statement_separator, true).thread();
        threaded += lastone;
    } while(lastone != 0);

    threaded += thread.one(&Lexer::thread_comment).thread();

    return threaded;
}

unsigned int Lexer::thread_identifier() {
    log_thread_attempt("identifier");

    return thread.any({&Lexer::thread_simple_identifier, &Lexer::thread_distinguished_identifier}).thread();
}

unsigned int Lexer::thread_simple_identifier() {
    log_thread_attempt("simple-identifier");

    return thread.any({&Lexer::thread_literal_identifier, &Lexer::thread_direct_identifier}).thread();
/*
    unsigned int threaded = thread.one(&Lexer::thread_literal_identifier)->thread();

    if(!threaded) {
        threaded += thread.one(&Lexer::thread_direct_identifier)->thread();
    }

    return threaded;*/
}

unsigned int Lexer::thread_literal_identifier() {
    log_thread_attempt("literal-identifier");

    unsigned int threaded = thread.many(Character::letter, 1).thread();

    if(threaded) {
        unsigned int last;
        do {
            last = 0;
            last += thread.many(Character::digit, 0).many(Character::underbar, 0).many(Character::overbar, 0).many(Character::letter, 0).thread();
            threaded += last;
        } while(last != 0);

        tokenize(TokenType::SimpleIdentifier);
        log_thread_success("literal-identifier");
    }

    return threaded;
}

unsigned int Lexer::thread_direct_identifier() {
    log_thread_attempt("direct-identifier");

    return Thread(this, false).any({Character::alpha, Character::omega}).thread();
}

unsigned int Lexer::thread_distinguished_identifier() {
    log_thread_attempt("distinguished-identifier");

    unsigned int threaded = thread.one(Character::quoteQuad).thread();

    if(!threaded) {
        threaded += thread.one(Character::quad).thread();

        if(threaded) {
            unsigned int last;
            do {
                last = thread.many(Character::letter).thread();
                last += thread.many(Character::digit).thread();
                threaded += last;
            } while(last != 0);
        }
    }

    if(threaded) {
        tokenize(TokenType::DistinguishedIdentifier);
        log_thread_success("distinguished-identifier");
    }

    return threaded;
}

unsigned int Lexer::thread_numeric_literal() {
    log_thread_attempt("numeric-literal");

    unsigned int threaded = thread.one(&Lexer::thread_numeric_scalar_literal).thread();

    if(threaded) {
        unsigned int last;
        do {
            last = thread.many(Character::blank, 1).one(&Lexer::thread_numeric_scalar_literal).thread();
            threaded += last;
        } while(last != 0);
    }

    if(threaded) {
        tokenize(TokenType::NumericLiteral);
        log_thread_success("numeric-literal");
    }

    return threaded;
}

unsigned int Lexer::thread_real_scalar_literal() {
    log_thread_attempt("real-scalar-literal");

    unsigned int threaded = thread.one(Character::overbar, true).thread();

    unsigned int threaded_number = thread.many(Character::digit, 1).one(Character::dot, true).many(Character::digit, 0).thread();
    if(!threaded_number) {
        threaded_number = thread.one(Character::dot).many(Character::digit, 1).thread();
    }
    threaded += threaded_number;

    if(threaded) {
        threaded += thread.one(&Lexer::thread_exponent, true).thread();
    }

    return threaded;
}

unsigned int Lexer::thread_exponent() {
    log_thread_attempt("exponent");

    return thread.one(Character::upperE).one(Character::overbar, true).many(Character::digit, 1).thread();
}

unsigned int Lexer::thread_numeric_scalar_literal() {
    log_thread_attempt("numeric-scalar-literal");

    return thread.one(&Lexer::thread_real_scalar_literal).one(&Lexer::thread_imaginary_part, true).thread();
}

unsigned int Lexer::thread_imaginary_part() {
    log_thread_attempt("imaginary-part");

    return thread.one(Character::upperJ).one(&Lexer::thread_real_scalar_literal).thread();
}

unsigned int Lexer::thread_character_literal() {
    log_thread_attempt("character-literal");

    unsigned int result = thread.one(Character::quote).many(Character::nonquote).one(Character::quote).thread();

    if(result) {
        tokenize(TokenType::CharacterLiteral);
        log_thread_success("character-literal");
    }

    return result;
}

unsigned int Lexer::thread_comment() {
    log_thread_attempt("comment");

    unsigned int result = thread.one(Character::upShoeJot).many(Character::any).thread();

    if(result) {
        clear_content();
    }

    return result;
}

unsigned int Lexer::thread_any() {
    log_thread_attempt("any");

    return thread.any(Character::any).thread();
}

unsigned int Lexer::thread_primitive() {
    log_thread_attempt("primitive");

    unsigned int threaded = thread.any(Character::ideogram).thread();
    if(threaded) {
        tokenize(TokenType::Primitive);
        log_thread_success("primitive");
    }

    return threaded;
}

unsigned int Lexer::thread_space() {
    log_thread_attempt("space");

    unsigned int result = thread.one(Character::blank).thread();

    if(result) {
        clear_content();
    }

    return result;
}

unsigned int Lexer::nonquote() {
    log_thread_attempt("nonquote");

    return thread.any(Character::nonquote).thread();
}

unsigned int Lexer::statement_separator() {
    log_thread_attempt("statement-separator");

    return thread.one(Character::diamond).thread();
}
/*
unsigned int Lexer::letter() {
    log_thread_attempt("letter");

    switch (*it) {
        case Character::lowerA: case Character::lowerB: case Character::lowerC:
        case Character::lowerD: case Character::lowerE: case Character::lowerF:
        case Character::lowerG: case Character::lowerH: case Character::lowerI:
        case Character::lowerJ: case Character::lowerK: case Character::lowerL:
        case Character::lowerM: case Character::lowerN: case Character::lowerO:
        case Character::lowerP: case Character::lowerQ: case Character::lowerR:
        case Character::lowerS: case Character::lowerT: case Character::lowerU:
        case Character::lowerV: case Character::lowerW: case Character::lowerX:
        case Character::lowerY: case Character::lowerZ:
        case Character::upperA: case Character::upperB: case Character::upperC:
        case Character::upperD: case Character::upperE: case Character::upperF:
        case Character::upperG: case Character::upperH: case Character::upperI:
        case Character::upperJ: case Character::upperK: case Character::upperL:
        case Character::upperM: case Character::upperN: case Character::upperO:
        case Character::upperP: case Character::upperQ: case Character::upperR:
        case Character::upperS: case Character::upperT: case Character::upperU:
        case Character::upperV: case Character::upperW: case Character::upperX:
        case Character::upperY: case Character::upperZ:
        case Character::delta:
        case Character::deltaUnderbar:
            append_to_content(*it);
            it++;
            return 1;
        default:
            return 0;
    }
}

unsigned int Lexer::digit() {
    log_thread_attempt("digit");

    switch (*it) {
        case Character::zero: case Character::one: case Character::two:
        case Character::three: case Character::four: case Character::five:
        case Character::six: case Character::seven: case Character::eight:
        case Character::nine:
            append_to_content(*it);
            it++;
            return 1;
        default:
            return 0;
    }
}

unsigned int Lexer::ideogram() {
    log_thread_attempt("ideogram");

    switch (*it) {
        case Character::diaeresis: case Character::overbar: case Character::leftCaret:
        case Character::lessThanOrEqual: case Character::equal: case Character::greaterThanOrEqual:
        case Character::rightCaret: case Character::notEqual: case Character::downCaret:
        case Character::upCaret: case Character::bar: case Character::divide:
        case Character::plus: case Character::multiply: case Character::query:
        case Character::omega: case Character::epsilon: case Character::rho:
        case Character::tilde: case Character::upArrow: case Character::downArrow:
        case Character::iota: case Character::circle: case Character::star:
        case Character::rightArrow: case Character::leftArrow: case Character::alpha:
        case Character::upStile: case Character::downStile: case Character::underbar:
        case Character::jot: case Character::leftParenthesis: case Character::rightParenthesis:
        case Character::leftBracket: case Character::rightBracket: case Character::leftShoe:
        case Character::rightShoe: case Character::upShoe: case Character::downShoe:
        case Character::upTack: case Character::downTack: case Character::stile:
        case Character::semicolon: case Character::colon: case Character::backSlash:
        case Character::comma: case Character::dot: case Character::slash:
        case Character::delStile: case Character::deltaStile: case Character::circleStile:
        case Character::circleBackslash: case Character::circleBar: case Character::circleStar:
        case Character::downCaretTilde: case Character::upCaretTilde: case Character::quoteDot:
        case Character::quadDivide: case Character::upTackJot: case Character::downTackJot:
        case Character::backSlashBar: case Character::slashBar: case Character::diaeresisJot:
        case Character::commaBar: case Character::diaeresisTilde: case Character::leftBrace:
        case Character::rightBrace: case Character::rightTack: case Character::leftTack:
        case Character::dollarSign:
            append_to_content(*it);
            it++;
            return 1;
        default:
            return 0;
    }
}

unsigned int Lexer::marker(Char marker) {
    log_thread_attempt("marker");
    if (*it == marker) {
        append_to_content(marker);
        it++;
        return 1;
    }
    return 0;
}
*/
void Lexer::clear_content() {
    content.clear();
}

void Lexer::append_to_content(Char c) {
    content.push_back(c);
}

void Lexer::tokenize(TokenType type) {
    tokens.emplace_back(type, content);
    content.clear();
}

void Lexer::unthread(unsigned int n) {
    unsigned int guarded_amount = std::min(n, (unsigned int)content.length());
    content.erase(content.end() - guarded_amount);
    it -= guarded_amount;
}
