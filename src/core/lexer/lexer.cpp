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
#include "../characters.h"
#include "../token.h"
#include "../error/error.h"

#include <utility>

using namespace kepler::lexer;

Lexer::Lexer(List<Char> input_, kepler::List<kepler::Token>* output_) : input(std::move(input_)), content(), output(output_) {}

void Lexer::lex(kepler::Context *context) {
    Lexer l(context->current_line, &context->currentStatement);
    if(!l.lex()) {
        throw kepler::error(SyntaxError, "Could not tokenize input.");
    }
}

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
    return match(characters::alpha, nullptr, false) || match(characters::omega, nullptr, false);
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
         characters::A, characters::B, characters::C,
         characters::D, characters::E, characters::F,
         characters::G, characters::H, characters::I,
         characters::J, characters::K, characters::L,
         characters::M, characters::N, characters::O,
         characters::P, characters::Q, characters::R,
         characters::S, characters::T, characters::U,
         characters::V, characters::W, characters::X,
         characters::Y, characters::Z
    });
}

int Lexer::digit() {
    return match({
        characters::one, characters::two, characters::three,
        characters::four, characters::five, characters::six,
        characters::seven, characters::eight, characters::nine,
        characters::zero
    });
}

int Lexer::ideogram() {
    return match({
         characters::diaeresis, characters::overbar, characters::left_caret,
         characters::less_than_or_equal, characters::equal, characters::greater_than_or_equal,
         characters::right_caret, characters::not_equal, characters::down_caret,
         characters::up_caret, characters::bar, characters::divide,
         characters::plus, characters::multiply, characters::query,
         characters::omega, characters::epsilon, characters::rho,
         characters::tilde, characters::up_arrow, characters::down_arrow,
         characters::iota, characters::circle, characters::star,
         characters::right_arrow, characters::left_arrow, characters::alpha,
         characters::up_stile, characters::down_stile, characters::underbar,
         characters::jot, characters::left_parenthesis, characters::right_parenthesis,
         characters::left_bracket, characters::right_bracket, characters::left_shoe,
         characters::right_shoe, characters::up_shoe, characters::down_shoe,
         characters::up_tack, characters::down_tack, characters::stile,
         characters::semicolon, characters::colon, characters::back_slash,
         characters::comma, characters::dot, characters::slash,
         characters::del_stile, characters::delta_stile, characters::circle_stile,
         characters::circle_back_slash, characters::circle_bar, characters::circle_star,
         characters::down_caret_tilde, characters::up_caret_tilde, characters::quote_dot,
         characters::quote_quad, characters::up_tack_jot, characters::down_tack_jot,
         characters::back_slash_bar, characters::slash_bar, characters::diaeresis_jot,
         characters::comma_bar, characters::diaeresis_tilde, characters::left_brace,
         characters::right_brace, characters::right_tack, characters::left_tack,
         characters::dollar_sign
    });
}

int Lexer::quote() {
    return match(characters::quote);
}

int Lexer::exponent_marker() {
    return match(characters::exponent_marker);
}

int Lexer::complex_marker() {
    return match(characters::complex_marker);
}

int Lexer::dot() {
    return match(characters::dot);
}

int Lexer::underbar() {
    return match(characters::underbar);
}

int Lexer::overbar() {
    return match(characters::overbar);
}

int Lexer::blank() {
    return match(characters::blank);
}

int Lexer::del() {
    return match(characters::del);
}

int Lexer::del_tilde() {
    return match(characters::del_tilde);
}

int Lexer::lamp() {
    return match(characters::up_shoe_jot);
}

int Lexer::quad() {
    return match(characters::quad);
}

int Lexer::quote_quad() {
    return match(characters::quote_quad);
}

int Lexer::diamond() {
    return match(characters::diamond);
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