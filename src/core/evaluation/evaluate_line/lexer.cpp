//
// Copyright 2023 Nikolaj Banke Jensen.
//
// This file is part of Test.
// 
// Test is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Test is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License 
// along with Test. If not, see <https://www.gnu.org/licenses/>.
//

#include "lexer.h"
#include "core/constants/literals.h"
#include "core/token.h"
#include "core/error.h"

#include <utility>

using namespace kepler::evaluation;

Lexer::Lexer(List<Char> input_, kepler::List<kepler::Token>* output_) : input(std::move(input_)), content(), output(output_) {}

bool Lexer::lex() {
    return line() == input.size();
}

int Lexer::line() {
    int counter = 0;

    if(match(&Lexer::identifier, &counter)) {}
    else if(match(&Lexer::numeric_literal, &counter)) {}

    while(match(&Lexer::primitive, &counter)
            || match(&Lexer::character_literal, &counter)
            || match(&Lexer::space, &counter)
            || match(&Lexer::statement_separator, &counter)) {
        if(match(&Lexer::identifier, &counter)) {}
        else if(match(&Lexer::numeric_literal, &counter)) {}
    }

    match(&Lexer::comment, &counter);
    return counter;
}

int Lexer::identifier() {
    int counter = 0;

    if(match(&Lexer::simple_identifier, &counter)) {}
    else if(match(&Lexer::distinguished_identifier, &counter)) {}

    return counter;
}

int Lexer::simple_identifier() {
    int counter = 0;

    if(match(&Lexer::literal_identifier, &counter)) {}
    else if(match(&Lexer::direct_identifier, &counter)) {}

    return counter;
}

int Lexer::literal_identifier() {
    int counter = 0;

    if(match(&Lexer::letter, &counter)) {
        while(match(&Lexer::letter, &counter)
                || match(&Lexer::digit, &counter)
                || match(&Lexer::underbar, &counter)
                || match(&Lexer::overbar, &counter)) {}
        create(kepler::SimpleIdentifierToken);
    }
    return counter;
}

int Lexer::direct_identifier() {
    return match(constants::alpha, nullptr, false) || match(constants::omega, nullptr, false);
}

int Lexer::distinguished_identifier() {
    int counter = 0;

    if(match(&Lexer::quote_quad, &counter)) {}
    else if(match(&Lexer::quad, &counter)) {
        while(match(&Lexer::letter, &counter) || match(&Lexer::digit, &counter)) {}
    }

    if(counter > 0) {
        create(kepler::DistinguishedIdentifierToken);
    }

    return counter;
}

int Lexer::numeric_literal() {
    int counter = 0;

    if(match(&Lexer::numeric_scalar_literal, &counter)) {
        int blanks = 0;
        while(match(&Lexer::blank, &blanks)) {
            while(match(&Lexer::blank, &blanks)) {}

            if(match(&Lexer::numeric_scalar_literal, &counter)) {
                counter += blanks;
                blanks = 0;
            } else {
                backtrack(blanks);
                break;
            }
        }

        create(kepler::NumericLiteralToken);
    }

    return counter;
}

int Lexer::real_scalar_literal() {
    int counter = 0;

    match(&Lexer::overbar, &counter);

    if(match(&Lexer::digit, &counter)) {
        while(match(&Lexer::digit, &counter)) {}

        if(match(&Lexer::dot, &counter)) {
            while(match(&Lexer::digit, &counter)) {}
        }
    } else if (match(&Lexer::dot, &counter)) {
        if(!match(&Lexer::digit, &counter)) {
            backtrack(counter);
            return 0;
        }

        while(match(&Lexer::digit, &counter)) {}
    } else {
        backtrack(counter);
        return counter;
    }

    match(&Lexer::exponent, &counter);

    return counter;
}

int Lexer::exponent() {
    int counter = 0;

    if(!match(&Lexer::exponent_marker, &counter)) {
        return counter;
    }

    match(&Lexer::overbar, &counter);

    if(!match(&Lexer::digit, &counter)) {
        throw kepler::error(SyntaxError, "Expected at least one digit here.", current);
        backtrack(counter);
        return counter;
    }

    while(match(&Lexer::digit, &counter)) {}

    return counter;
}

int Lexer::numeric_scalar_literal() {
    int counter = 0;

    if(!match(&Lexer::real_scalar_literal, &counter)) {
        return counter;
    }

    match(&Lexer::imaginary_part, &counter);

    return counter;
}

int Lexer::imaginary_part() {
    int counter = 0;

    if(!(match(&Lexer::complex_marker, &counter) && match(&Lexer::real_scalar_literal, &counter))) {
        backtrack(counter);
    }

    return counter;
}

int Lexer::character_literal() {
    int counter = 0;

    while(match(&Lexer::quote, &counter)) {
        while(match(&Lexer::nonquote, &counter)) {}

        if(!match(&Lexer::quote, &counter)) {
            backtrack(counter);
            return counter;
        }
    }

    if(counter >= 2) {
        create(kepler::CharacterLiteralToken);
    } else {
        backtrack(counter);
    }

    return counter;
}

int Lexer::comment() {
    int counter = 0;

    if(!match(&Lexer::lamp, &counter)) {
        return 0;
    }

    while(match(&Lexer::any, &counter)) {}

    clear();

    return counter;
}

int Lexer::any() {
    int counter = 0;

    if(match(&Lexer::quote, &counter)) {}
    else if (match(&Lexer::nonquote, &counter)) {}

    return counter;
}

int Lexer::primitive() {
    if(match(&Lexer::ideogram)) {
        create(kepler::PrimitiveToken);
        return 1;
    }

    return 0;
}

int Lexer::space() {
    if(match(&Lexer::blank)) {
        clear();
        return 1;
    }

    return 0;
}

int Lexer::nonquote() {
    int counter = 0;

    if(match(&Lexer::ideogram, &counter)) {}
    else if (match(&Lexer::digit, &counter)) {}
    else if (match(&Lexer::blank, &counter)) {}
    else if (match(&Lexer::letter, &counter)) {}
    else if (match(&Lexer::lamp, &counter)) {}
    else if (match(&Lexer::del, &counter)) {}
    else if (match(&Lexer::del_tilde, &counter)) {}
    else if (match(&Lexer::quad, &counter)) {}
    else if (match(&Lexer::quote_quad, &counter)) {}
    else if (match(&Lexer::diamond, &counter)) {}

    return counter;
}

int Lexer::statement_separator() {
    return match(&Lexer::diamond);
}

int Lexer::letter() {
    return match({
                         constants::A, constants::B, constants::C,
                         constants::D, constants::E, constants::F,
                         constants::G, constants::H, constants::I,
                         constants::J, constants::K, constants::L,
                         constants::M, constants::N, constants::O,
                         constants::P, constants::Q, constants::R,
                         constants::S, constants::T, constants::U,
                         constants::V, constants::W, constants::X,
                         constants::Y, constants::Z
    });
}

int Lexer::digit() {
    return match({
                         constants::one, constants::two, constants::three,
                         constants::four, constants::five, constants::six,
                         constants::seven, constants::eight, constants::nine,
                         constants::zero
    });
}

int Lexer::ideogram() {
    return match({
                         constants::diaeresis, constants::overbar, constants::left_caret,
                         constants::less_than_or_equal, constants::equal, constants::greater_than_or_equal,
                         constants::right_caret, constants::not_equal, constants::down_caret,
                         constants::up_caret, constants::bar, constants::divide,
                         constants::plus, constants::multiply, constants::query,
                         constants::omega, constants::epsilon, constants::rho,
                         constants::tilde, constants::up_arrow, constants::down_arrow,
                         constants::iota, constants::circle, constants::star,
                         constants::right_arrow, constants::left_arrow, constants::alpha,
                         constants::up_stile, constants::down_stile, constants::underbar,
                         constants::jot, constants::left_parenthesis, constants::right_parenthesis,
                         constants::left_bracket, constants::right_bracket, constants::left_shoe,
                         constants::right_shoe, constants::up_shoe, constants::down_shoe,
                         constants::up_tack, constants::down_tack, constants::stile,
                         constants::semicolon, constants::colon, constants::back_slash,
                         constants::comma, constants::dot, constants::slash,
                         constants::del_stile, constants::delta_stile, constants::circle_stile,
                         constants::circle_back_slash, constants::circle_bar, constants::circle_star,
                         constants::down_caret_tilde, constants::up_caret_tilde, constants::quote_dot,
                         constants::quote_quad, constants::up_tack_jot, constants::down_tack_jot,
                         constants::back_slash_bar, constants::slash_bar, constants::diaeresis_jot,
                         constants::comma_bar, constants::diaeresis_tilde, constants::left_brace,
                         constants::right_brace, constants::right_tack, constants::left_tack,
                         constants::dollar_sign
    });
}

int Lexer::quote() {
    return match(constants::quote);
}

int Lexer::exponent_marker() {
    return match(constants::exponent_marker);
}

int Lexer::complex_marker() {
    return match(constants::complex_marker);
}

int Lexer::dot() {
    return match(constants::dot);
}

int Lexer::underbar() {
    return match(constants::underbar);
}

int Lexer::overbar() {
    return match(constants::overbar);
}

int Lexer::blank() {
    return match(constants::blank);
}

int Lexer::del() {
    return match(constants::del);
}

int Lexer::del_tilde() {
    return match(constants::del_tilde);
}

int Lexer::lamp() {
    return match(constants::up_shoe_jot);
}

int Lexer::quad() {
    return match(constants::quad);
}

int Lexer::quote_quad() {
    return match(constants::quote_quad);
}

int Lexer::diamond() {
    return match(constants::diamond);
}

bool Lexer::match(rule rule, int* counter) {
    if(isAtEnd()) return false;

    int tmp = (this->*rule)();
    if(counter != nullptr) (*counter) += tmp;
    return tmp != 0;
}

bool Lexer::match(kepler::Char character, int *counter, bool append) {
    if(check(character)) {
        if(append) content.push_back(peek());
        if(counter != nullptr) (*counter)++;
        advance();

        return true;
    }

    return false;
}

bool Lexer::match(std::initializer_list<kepler::Char> characters, int *counter, bool append) {
    for(auto& character : characters) {
        if(match(character, counter, append)) {
            return true;
        }
    }

    return false;
}

bool Lexer::check(kepler::Char character) {
    if(isAtEnd()) return false;
    return peek() == character;
}

void Lexer::advance() {
    if(!isAtEnd()) current++;
}

void Lexer::backtrack(int& amount) {
    if(current - amount >= 0) {
        current -= amount;
        content.resize(content.size() - amount);
        amount = 0;
    }
}

void Lexer::clear() {
    content.clear();
}

void Lexer::create(kepler::TokenClass tokenClass) {
    kepler::List<kepler::Char> v;
    std::copy(content.begin(), content.end(), std::back_inserter(v));
    output->emplace_back(tokenClass, std::move(v));
    clear();
}

// One past the end.
bool Lexer::isAtEnd() {
    return current >= input.size();
}

kepler::Char& Lexer::peek() {
    return input.at(current);
}

kepler::Char& Lexer::previous() {
    return input.at(current - 1);
}