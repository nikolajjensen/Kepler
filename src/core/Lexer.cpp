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
#include "Thread.h"

Lexer::Lexer(CharList _input, bool _debugOn) : input(std::move(_input)), debugOn(_debugOn), it(input.begin()), tokens() {}

void Lexer::log_thread_attempt(std::string &&type) {
    if (debugOn) {
        std::cout << "Threading " << type << " using substring: " << uni::utf32to8(CharList(it, input.end())) << std::endl;
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
    // Should throw syntax-error if 'pos' is not at end of 'input'.
    return tokens;
}

unsigned int Lexer::thread_line() {
    log_thread_attempt("line");

    thread_identifier() || thread_numeric_literal();

    while(thread_primitive() || thread_character_literal() || thread_space() || thread_statement_separator()) {
        thread_identifier();
        thread_numeric_literal();
    }

    thread_comment();

    return true;
}

unsigned int Lexer::thread_identifier() {
    log_thread_attempt("identifier");

    unsigned int threaded = thread_simple_identifier();

    if (threaded) {
        return threaded;
    } else {
        threaded = thread_distinguished_identifier();
    }

    return threaded;
}

unsigned int Lexer::thread_simple_identifier() {
    log_thread_attempt("simple-identifier");

    unsigned int threaded = thread_literal_identifier();

    if (threaded) {
        return threaded;
    } else {
        threaded = thread_direct_identifier();
    }

    return threaded;
}

unsigned int Lexer::thread_literal_identifier() {
    log_thread_attempt("literal-identifier");

    unsigned int threaded = 0;

    if(thread_letter()) {
        threaded++;
        while(thread_letter() || thread_digit() || thread_marker(Character::underbar) || thread_marker(Character::overbar)) {
            threaded++;
        }
        tokenize(TokenType::SimpleIdentifier);
        log_thread_success("literal-identifier");
        return threaded;
    }

    return 0;
}

unsigned int Lexer::thread_direct_identifier() {
    log_thread_attempt("direct-identifier");

    if (*it == Character::alpha || *it == Character::omega) {
        it++;
        return 1;
    }

    return 0;
}

unsigned int Lexer::thread_distinguished_identifier() {
    log_thread_attempt("distinguished-identifier");

    unsigned int threaded = 0;

    if(thread_marker(Character::quoteQuad)) {
        threaded++;
    }
    else if (thread_marker(Character::quad)) {
        threaded++;
        while(thread_letter() || thread_digit()) {
            threaded++;
        }
    } else {
        unthread(threaded);
        return 0;
    }

    tokenize(TokenType::DistinguishedIdentifier);

    log_thread_success("distinguished-identifier");
    return threaded;
}

unsigned int Lexer::thread_numeric_literal() {
    log_thread_attempt("numeric-literal");

    unsigned int threaded = thread_numeric_scalar_literal();

    if(threaded) {
        if(thread_marker(Character::blank)) {
            threaded++;
            threaded += repeatedly(&Lexer::thread_marker, Character::blank);

            if(!thread_numeric_scalar_literal()) {
                // Note '!'; cannot thread-numeric-scalar, so un-thread.
                unthread(threaded);
                return 0;
            }
        }

        tokenize(TokenType::NumericLiteral);

        log_thread_success("numeric-literal");
        return threaded;
    }

    return threaded;
}

unsigned int Lexer::thread_real_scalar_literal() {
    log_thread_attempt("real-scalar-literal");

    unsigned int threaded = thread_marker(Character::overbar);

    if(thread_digit()) {
        threaded++;
        threaded += repeatedly(&Lexer::thread_digit);

        if (thread_marker(Character::dot)) {
            threaded++;
            threaded += repeatedly(&Lexer::thread_digit);
        }
    } else if (thread_marker(Character::dot)) {
        threaded++;
        threaded += thread_digit();
    } else {
        unthread(threaded);
        return 0;
    }

    threaded += thread_exponent();
    return threaded;
}

unsigned int Lexer::thread_exponent() {
    log_thread_attempt("exponent");

    unsigned int threaded_sign = thread_marker(Character::upperE);
    if(threaded_sign) {
        unsigned int threaded_overbar = thread_marker(Character::overbar);
        unsigned int threaded_digits = repeatedly(&Lexer::thread_digit);

        if(threaded_digits >= 1) {
            return threaded_sign + threaded_overbar + threaded_digits;
        } else {
            unthread(threaded_sign + threaded_overbar);
            return 0;
        }
    }

    return 0;
}

unsigned int Lexer::thread_numeric_scalar_literal() {
    log_thread_attempt("numeric-scalar-literal");

    if(thread_real_scalar_literal()) {
        return 1 + thread_imaginary_part();
    }

    return 0;
}

unsigned int Lexer::thread_imaginary_part() {
    log_thread_attempt("imaginary-part");

    // Dangerous, as we may not have real-scalar-literal, but still eat in thread_marker.
    unsigned int threaded_sign = thread_marker(Character::upperJ);
    if(threaded_sign) {
        unsigned int threaded_real_scalar = thread_real_scalar_literal();
        if(threaded_real_scalar) {
            return threaded_sign + threaded_real_scalar;
        } else {
            unthread(threaded_sign);
            return 0;
        }
    }

    return 0;
}

unsigned int Lexer::thread_character_literal() {
    log_thread_attempt("character-literal");

    unsigned int threaded_start_quote = thread_marker(Character::quote);
    if(threaded_start_quote) {
        unsigned int threaded_nonquotes = repeatedly(&Lexer::thread_nonquote);
        unsigned int threaded_end_quote = thread_marker(Character::quote);

        if(threaded_end_quote) {
            tokenize(TokenType::CharacterLiteral);
            log_thread_success("character-literal");
            return threaded_start_quote + threaded_nonquotes + threaded_end_quote;
        } else {
            unthread(threaded_start_quote + threaded_nonquotes);
            return 0;
        }
    }

    return 0;
}

unsigned int Lexer::thread_comment() {
    log_thread_attempt("comment");

    if(thread_marker(Character::upShoeJot)) {
        unsigned int threaded = repeatedly(&Lexer::thread_any);
        clear_content();
        return 1 + threaded;
    }

    return 0;
}

unsigned int Lexer::thread_any() {
    log_thread_attempt("any");

    return thread_marker(Character::quote) || thread_nonquote();
}

unsigned int Lexer::thread_primitive() {
    log_thread_attempt("primitive");

    unsigned int i = 0;
    if(i += thread_ideogram()) {
        tokenize(TokenType::Primitive);
        log_thread_success("primitive");
        return 1;
    }

    return 0;
}

unsigned int Lexer::thread_space() {
    log_thread_attempt("space");

    if(thread_marker(Character::blank)) {
        clear_content();
        return 1;
    }

    return 0;
}

unsigned int Lexer::thread_nonquote() {
    log_thread_attempt("nonquote");

    return (thread_ideogram() || thread_digit()
            || thread_marker(Character::blank) || thread_letter()
            || thread_marker(Character::upShoeJot) || thread_marker(Character::del)
            || thread_marker(Character::delTilde) || thread_marker(Character::quad)
            || thread_marker(Character::quoteQuad) || thread_marker(Character::diamond));
}

unsigned int Lexer::thread_statement_separator() {
    log_thread_attempt("statement-separator");

    return thread_marker(Character::diamond);
}

unsigned int Lexer::thread_letter() {
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

unsigned int Lexer::thread_digit() {
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

unsigned int Lexer::thread_ideogram() {
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

unsigned int Lexer::thread_marker(Char marker) {
    log_thread_attempt("marker");
    if (*it == marker) {
        append_to_content(marker);
        it++;
        return 1;
    }
    return 0;
}

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
    content.erase(content.end() - n);
    it -= n;
}

unsigned int Lexer::repeatedly(unsigned int (Lexer::*f)()) {
    unsigned int count = 0;
    unsigned int last = 0;
    do {
        last = (this->*f)();
        count += last;
    } while(last != 0);
    return count;
}

unsigned int Lexer::repeatedly(unsigned int (Lexer::*f)(Char), Char c) {
    unsigned int count = 0;
    unsigned int last = 0;
    do {
        last = (this->*f)(c);
        count += last;
    } while(last != 0);
    return count;
}

unsigned int Lexer::one(Lexer::func f) {
    return (this->*f)();
}

unsigned int Lexer::many(Lexer::func f) {
    unsigned int count = 0;
    unsigned int last;
    do {
        last = (this->*f)();
        count += last;
    } while(last != 0);
    return count;
}

unsigned int Lexer::any(std::initializer_list<func> && funcs) {
    unsigned int count = 0;
    auto func_it = funcs.begin();
    while(count == 0 && func_it != funcs.end()) {
        count += (this->*(*func_it))();
        func_it++;
    }
    return count;
}

unsigned int Lexer::all(std::initializer_list<func> && funcs) {
    unsigned int count = 0;
    bool failed = false;
    auto func_it = funcs.begin();
    while(!failed &&func_it != funcs.end()) {
        unsigned int result = (this->*(*func_it))();

        if(result == 0) {
            failed = true;
        } else {
            count += result;
            func_it++;
        }
    }

    if(!failed) {
        return count;
    } else {
        unthread(count);
        return 0;
    }
}