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
#include "Utility.h"
#include <iostream>

Lexer::Lexer(std::string _input, bool _debugOn) : input(_input), debugOn(_debugOn), pos(0) {}

std::vector<Token> Lexer::run() {
    tokens = {};
    pos = 0;
    thread_line();
    // Should throw syntax-error if 'pos' is not at end of 'input'.
    return tokens;
}

bool Lexer::thread_line() {
    if (debugOn) {
        std::cout << "Threading line: '" << input.substr(pos) << "'" << std::endl;
    }

    thread_identifier() || thread_numeric_literal();

    while(thread_primitive()/* || thread_character_literal() || thread_space() || thread_statement_separator()*/) {
        thread_identifier();
        thread_numeric_literal();
    }

    thread_comment();

    if (debugOn) {
        std::cout << "Threading line worked" << std::endl;
    }
    return true;
}

bool Lexer::thread_identifier() {
    if (debugOn) {
        auto d = input.substr(pos);
        std::cout << d << std::endl;
        std::cout << "Threading identifier: '" << input.substr(pos) << "'" << std::endl;
    }

    if (thread_simple_identifier() || thread_distinguished_identifier()) {
        if (debugOn) {
            std::cout << "Threading identifier worked" << std::endl;
        }

        return true;
    } else {
        if (debugOn) {
            std::cout << "Threading identifier failed" << std::endl;
        }
        return false;
    }
}

bool Lexer::thread_simple_identifier() {
    if (debugOn) {
        std::cout << "Threading simple-identifier: '" << input.substr(pos) << "'" << std::endl;
    }

    if (thread_literal_identifier() || thread_direct_identifier()) {
        if (debugOn) {
            std::cout << "Threading simple-identifier worked" << std::endl;
        }

        return true;
    } else {
        if (debugOn) {
            std::cout << "Threading simple-identifier failed" << std::endl;
        }
        return false;
    }
}

bool Lexer::thread_literal_identifier() {
    if (debugOn) {
        std::cout << "Threading literal-identifier: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_letter()) {
        while(thread_letter() || thread_digit() || thread_underbar() || thread_overbar()) {}

        tokens.emplace_back(TokenType::SimpleIdentifier, content);
        content.clear();

        if (debugOn) {
            std::cout << "Threading literal-identifier worked: '" << tokens.back() << "'" << std::endl;
        }
        return true;
    }

    if (debugOn) {
        std::cout << "Threading simple-identifier failed" << std::endl;
    }

    return false;
}

bool Lexer::thread_direct_identifier() {
    if (debugOn) {
        std::cout << "Threading direct-identifier: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::alpha || c == CharacterSet::omega) {
        pos++;
        //content.push_back(c);
        if (debugOn) {
            std::cout << "Threading direct-identifier worked" << std::endl;
        }
        return true;
    }

    if (debugOn) {
        std::cout << "Threading simple-identifier failed" << std::endl;
    }

    return false;
}

bool Lexer::thread_distinguished_identifier() {
    if (debugOn) {
        std::cout << "Threading distinguished-identifier: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_quote_quad()) {}
    else if (thread_quad()) {
        while(thread_letter() || thread_digit()) {}
    } else {
        if (debugOn) {
            std::cout << "Threading distinguished-identifier failed" << std::endl;
        }
        return false;
    }

    tokens.emplace_back(TokenType::DistinguishedIdentifier, content);
    content.clear();

    if (debugOn) {
        std::cout << "Threading distinguished-identifier worked: '" << tokens.back() << "'" << std::endl;
    }
    return true;
}

// 1. Thread at least one numeric-scalar-literal.
// while(thread_space())
//      while(thread_space()) {}
//      thread_numeric_scalar_literal()
bool Lexer::thread_numeric_literal() {
    if (debugOn) {
        std::cout << "Threading numeric-literal: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_numeric_scalar_literal()) {
        if(thread_blank()) {
            if(thread_numeric_scalar_literal()) {
                // '1 1' here.
            } else {
                // '1 ' here.
                std::cout << "'" << content << "'" << std::endl;
                content.pop_back();
                pos--;
            }
        }


        tokens.emplace_back(TokenType::NumericLiteral, content);
        content.clear();

        if (debugOn) {
            std::cout << "Threading numeric-literal worked: '" << tokens.back() << "'" << std::endl;
        }
        return true;
    }

    if (debugOn) {
        std::cout << "Threading numeric-literal failed" << std::endl;
    }
    return false;
}

bool Lexer::thread_real_scalar_literal() {
    if (debugOn) {
        std::cout << "Threading real-scalar-literal: '" << input.substr(pos) << "'" << std::endl;
    }

    thread_overbar();

    if(thread_digit()) {
        while(thread_digit()) {}

        if (thread_dot()) {
            if (thread_digit()) {
                while(thread_digit()) {}
            }
        }
    } else if (thread_dot() && thread_digit()) {
        while(thread_digit()) {}
    } else {

        if (debugOn) {
            std::cout << "Threading real-scalar-literal failed" << std::endl;
        }
        return false;
    }

    thread_exponent();

    if (debugOn) {
        std::cout << "Threading real-scalar-literal worked" << std::endl;
    }
    return true;
}

bool Lexer::thread_exponent() {
    if (debugOn) {
        std::cout << "Threading exponent: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_exponent_marker()) {
        thread_overbar();

        if(thread_digit()) {
            while(thread_digit()) {}

            if (debugOn) {
                std::cout << "Threading exponent worked" << std::endl;
            }
            return true;
        } else {
            if (debugOn) {
                std::cout << "Threading exponent failed" << std::endl;
            }
            return false;
        }
    }

    if (debugOn) {
        std::cout << "Threading exponent failed" << std::endl;
    }
    return false;
}

bool Lexer::thread_numeric_scalar_literal() {
    if (debugOn) {
        std::cout << "Threading numeric-scalar-literal: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_real_scalar_literal()) {
        thread_imaginary_part();

        return true;
    }

    if (debugOn) {
        std::cout << "Threading numeric-scalar-literal failed" << std::endl;
    }
    return false;
}

bool Lexer::thread_imaginary_part() {
    if (debugOn) {
        std::cout << "Threading imaginary-part: '" << input.substr(pos) << "'" << std::endl;
    }

    if (thread_complex_marker() && thread_real_scalar_literal()) {
        if (debugOn) {
            std::cout << "Threading imaginary-part worked" << std::endl;
        }
        return true;
    } else {
        if (debugOn) {
            std::cout << "Threading imaginary-part failed" << std::endl;
        }
        return false;
    }
}

bool Lexer::thread_character_literal() {
    if (debugOn) {
        std::cout << "Threading character-literal: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_quote()) {
        while(thread_nonquote()) {}
        if(thread_quote()) {
            tokens.emplace_back(TokenType::CharacterLiteral, content);
            content.clear();

            if (debugOn) {
                std::cout << "Threading character-literal worked: '" << tokens.back() << "'" << std::endl;
            }

            return true;
        } else {
            if (debugOn) {
                std::cout << "Threading character-literal failed" << std::endl;
            }

            return false;
        }
    }

    if (debugOn) {
        std::cout << "Threading character-literal failed" << std::endl;
    }
    return false;
}

bool Lexer::thread_comment() {
    if (debugOn) {
        std::cout << "Threading comment: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_lamp()) {
        while(thread_any()) {}
        content.clear();
        return true;
    }

    if (debugOn) {
        std::cout << "Threading comment failed" << std::endl;
    }
    return false;
}

bool Lexer::thread_any() {
    if (debugOn) {
        std::cout << "Threading any: '" << input.substr(pos) << "'" << std::endl;
    }

    if (thread_quote() || thread_nonquote()) {
        if (debugOn) {
            std::cout << "Threading any worked" << std::endl;
        }
        return true;
    } else {
        if (debugOn) {
            std::cout << "Threading any failed" << std::endl;
        }
        return false;
    }
}

bool Lexer::thread_primitive() {
    if (debugOn) {
        std::cout << "Threading primitive: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_ideogram()) {
        tokens.emplace_back(TokenType::Primitive, content);
        content.clear();

        if (debugOn) {
            std::cout << "Threading primitive worked: '" << tokens.back() << "'" << std::endl;
        }

        return true;
    }

    if (debugOn) {
        std::cout << "Threading primitive failed" << std::endl;
    }

    return false;
}

bool Lexer::thread_space() {
    if (debugOn) {
        std::cout << "Threading space: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_blank()) {
        content.clear();
        if (debugOn) {
            std::cout << "Threading space worked" << std::endl;
        }
        return true;
    }

    if (debugOn) {
        std::cout << "Threading space failed" << std::endl;
    }
    return false;
}

bool Lexer::thread_nonquote() {
    if (debugOn) {
        std::cout << "Threading nonquote: '" << input.substr(pos) << "'" << std::endl;
    }

    if (thread_ideogram() || thread_digit() || thread_blank() ||
        thread_letter() || thread_lamp() || thread_del() ||
        thread_del_tilde() || thread_quad() || thread_quote_quad() || thread_diamond()) {
        if (debugOn) {
            std::cout << "Threading nonquote worked" << std::endl;
        }
        return true;
    } else {
        if (debugOn) {
            std::cout << "Threading nonquote failed" << std::endl;
        }
        return false;
    }
}

bool Lexer::thread_statement_separator() {
    if (debugOn) {
        std::cout << "Threading statement-separator: '" << input.substr(pos) << "'" << std::endl;
    }

    if(thread_diamond()) {
        if (debugOn) {
            std::cout << "Threading diamond worked" << std::endl;
        }
        return false;
    } else {
        if (debugOn) {
            std::cout << "Threading diamond failed" << std::endl;
        }
        return true;
    }
}

bool Lexer::thread_letter() {
    if (debugOn) {
        std::cout << "Threading letter: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];

    switch (c) {
        case CharacterSet::lowerA: case CharacterSet::lowerB: case CharacterSet::lowerC:
        case CharacterSet::lowerD: case CharacterSet::lowerE: case CharacterSet::lowerF:
        case CharacterSet::lowerG: case CharacterSet::lowerH: case CharacterSet::lowerI:
        case CharacterSet::lowerJ: case CharacterSet::lowerK: case CharacterSet::lowerL:
        case CharacterSet::lowerM: case CharacterSet::lowerN: case CharacterSet::lowerO:
        case CharacterSet::lowerP: case CharacterSet::lowerQ: case CharacterSet::lowerR:
        case CharacterSet::lowerS: case CharacterSet::lowerT: case CharacterSet::lowerU:
        case CharacterSet::lowerV: case CharacterSet::lowerW: case CharacterSet::lowerX:
        case CharacterSet::lowerY: case CharacterSet::lowerZ:

        case CharacterSet::upperA: case CharacterSet::upperB: case CharacterSet::upperC:
        case CharacterSet::upperD: case CharacterSet::upperE: case CharacterSet::upperF:
        case CharacterSet::upperG: case CharacterSet::upperH: case CharacterSet::upperI:
        case CharacterSet::upperJ: case CharacterSet::upperK: case CharacterSet::upperL:
        case CharacterSet::upperM: case CharacterSet::upperN: case CharacterSet::upperO:
        case CharacterSet::upperP: case CharacterSet::upperQ: case CharacterSet::upperR:
        case CharacterSet::upperS: case CharacterSet::upperT: case CharacterSet::upperU:
        case CharacterSet::upperV: case CharacterSet::upperW: case CharacterSet::upperX:
        case CharacterSet::upperY: case CharacterSet::upperZ:

        case CharacterSet::delta:
        case CharacterSet::deltaUnderbar:
            pos++;
            content.push_back(c);
            if (debugOn) {
                std::cout << "Threading letter worked" << std::endl;
            }
            return true;
        default:
            if (debugOn) {
                std::cout << "Threading letter failed" << std::endl;
            }
            return false;
    }
}

bool Lexer::thread_digit() {
    if (debugOn) {
        std::cout << "Threading digit: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];

    switch (c) {
        case CharacterSet::zero: case CharacterSet::one: case CharacterSet::two:
        case CharacterSet::three: case CharacterSet::four: case CharacterSet::five:
        case CharacterSet::six: case CharacterSet::seven: case CharacterSet::eight:
        case CharacterSet::nine:
            pos++;
            content.push_back(c);
            if (debugOn) {
                std::cout << "Threading digit worked" << std::endl;
            }
            return true;
        default:
            if (debugOn) {
                std::cout << "Threading digit failed" << std::endl;
            }
            return false;
    }
}

bool Lexer::thread_ideogram() {
    if (debugOn) {
        std::cout << "Threading ideogram: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    Char l = CharacterSet::leftArrow;

    std::cout << typeid(c).name() << std::endl;
    std::cout << typeid(CharacterSet::leftArrow).name() << std::endl;

    if(c == CharacterSet::leftArrow) {
        std::cout << "GOT THE ARROW!" << std::endl;
    }

    switch (c) {
        case CharacterSet::diaeresis: case CharacterSet::overbar: case CharacterSet::leftCaret:
        case CharacterSet::lessThanOrEqual: case CharacterSet::equal: case CharacterSet::greaterThanOrEqual:
        case CharacterSet::rightCaret: case CharacterSet::notEqual: case CharacterSet::downCaret:
        case CharacterSet::upCaret: case CharacterSet::bar: case CharacterSet::divide:
        case CharacterSet::plus: case CharacterSet::multiply: case CharacterSet::query:
        case CharacterSet::omega: case CharacterSet::epsilon: case CharacterSet::rho:
        case CharacterSet::tilde: case CharacterSet::upArrow: case CharacterSet::downArrow:
        case CharacterSet::iota: case CharacterSet::circle: case CharacterSet::star:
        case CharacterSet::rightArrow: case CharacterSet::leftArrow: case CharacterSet::alpha:
        case CharacterSet::upStile: case CharacterSet::downStile: case CharacterSet::underbar:
        case CharacterSet::jot: case CharacterSet::leftParenthesis: case CharacterSet::rightParenthesis:
        case CharacterSet::leftBracket: case CharacterSet::rightBracket: case CharacterSet::leftShoe:
        case CharacterSet::rightShoe: case CharacterSet::upShoe: case CharacterSet::downShoe:
        case CharacterSet::upTack: case CharacterSet::downTack: case CharacterSet::stile:
        case CharacterSet::semicolon: case CharacterSet::colon: case CharacterSet::backSlash:
        case CharacterSet::comma: case CharacterSet::dot: case CharacterSet::slash:
        case CharacterSet::delStile: case CharacterSet::deltaStile: case CharacterSet::circleStile:
        case CharacterSet::circleBackslash: case CharacterSet::circleBar: case CharacterSet::circleStar:
        case CharacterSet::downCaretTilde: case CharacterSet::upCaretTilde: case CharacterSet::quoteDot:
        case CharacterSet::quadDivide: case CharacterSet::upTackJot: case CharacterSet::downTackJot:
        case CharacterSet::backSlashBar: case CharacterSet::slashBar: case CharacterSet::diaeresisJot:
        case CharacterSet::commaBar: case CharacterSet::diaeresisTilde: case CharacterSet::leftBrace:
        case CharacterSet::rightBrace: case CharacterSet::rightTack: case CharacterSet::leftTack:
        case CharacterSet::dollarSign:
            pos++;
            content.push_back(c);

            if(c == CharacterSet::leftArrow) {
                std::cout << "GOT THE ARROW!" << std::endl;
            }

            if (debugOn) {
                std::cout << "Threading ideogram worked" << std::endl;
            }
            return true;
        default:
            if (debugOn) {
                std::cout << "Threading ideogram failed" << std::endl;
            }
            return false;
    }
}

bool Lexer::thread_quote() {
    if (debugOn) {
        std::cout << "Threading quote: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::quote) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_exponent_marker() {
    if (debugOn) {
        std::cout << "Threading exponent-marker: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::upperE) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_complex_marker() {
    if (debugOn) {
        std::cout << "Threading complex-marker: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::upperJ) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_dot() {
    if (debugOn) {
        std::cout << "Threading dot: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::dot) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_underbar() {
    if (debugOn) {
        std::cout << "Threading underbar: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::underbar) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_overbar() {
    if (debugOn) {
        std::cout << "Threading overbar: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::overbar) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_blank() {
    if (debugOn) {
        std::cout << "Threading blank: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::blank) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_del() {
    if (debugOn) {
        std::cout << "Threading del: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::del) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_del_tilde() {
    if (debugOn) {
        std::cout << "Threading del-tilde: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::delTilde) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_lamp() {
    if (debugOn) {
        std::cout << "Threading lamp: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::upShoeJot) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_quad() {
    if (debugOn) {
        std::cout << "Threading quad: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::quad) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_quote_quad() {
    if (debugOn) {
        std::cout << "Threading quote-quad: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::quoteQuad) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}

bool Lexer::thread_diamond() {
    if (debugOn) {
        std::cout << "Threading diamond: '" << input.substr(pos) << "'" << std::endl;
    }

    Char c = input[pos];
    if (c == CharacterSet::diamond) {
        pos++;
        content.push_back(c);
        return true;
    }

    return false;
}