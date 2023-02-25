//
// Copyright 2023 Nikolaj Banke Jensen.
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

#include "rules.h"
#include "helpers.h"
#include "context.h"
#include "core/error.h"

namespace kepler::grammar {
    bool rules::line(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(identifier, input, context, head));
        else if(helpers::match(numeric_literal, input, context, head)) {}

        while(helpers::match(primitive, input, context, head)
              || helpers::match(character_literal, input, context, head)
              || helpers::match(space, input, context, head)
              || helpers::match(statement_separator, input, context, head)) {
            if(helpers::match(identifier, input, context, head));
            else if(helpers::match(numeric_literal, input, context, head)) {}
        }
        helpers::match(comment, input, context, head);
        return true;
    }

    bool rules::identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(simple_identifier, input, context, head)) {}
        else if(helpers::match(distinguished_identifier, input, context, head)) {}
        else { return false; }

        return true;
    }

    bool rules::simple_identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(literal_identifier, input, context, head)) {}
        else if(helpers::match(direct_identifier, input, context, head)) {}
        else { return false; }

        return true;
    }

    bool rules::literal_identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(letter, input, context, head)) {
            while(helpers::match(letter, input, context, head)
                    || helpers::match(digit, input, context, head)
                    || helpers::match(underbar, input, context, head)
                    || helpers::match(overbar, input, context, head)) {}

            return true;
        }

        return false;
    }

    bool rules::direct_identifier(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(constants::alpha, input, context, head)) {}
        else if(helpers::match(constants::omega, input, context, head)) {}
        else { return false; }

        return true;
    }

    bool rules::distinguished_identifier(const std::vector<Char> &input, context<Char>& context, int &head) {
        if(helpers::match(quote_quad, input, context, head)) {
            return true;
        } else if(helpers::match(quad, input, context, head)) {
            while(helpers::match(letter, input, context, head) || helpers::match(digit, input, context, head)) {}
            return true;
        }

        return false;
    }

    bool rules::numeric_literal(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(numeric_scalar_literal, input, context, head)) {
            int counter = head;

            while(helpers::match(blank, input, context, counter)) {
                while(helpers::match(blank, input, context, counter)) {}

                if(helpers::match(numeric_scalar_literal, input, context, counter)) {
                    head = counter;
                } else {
                    context.backtrack(counter - head);
                }
            }

            return true;
        }

        return false;
    }

    bool rules::real_scalar_literal(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;

        helpers::match(overbar, input, context, counter);

        if(helpers::match(digit, input, context, counter)) {
            while(helpers::match(digit, input, context, counter)) {}
            helpers::match(dot, input, context, counter);
            while(helpers::match(digit, input, context, counter)) {}
        } else {
            if(!helpers::match(dot, input, context, counter)) {
                return false;
            }
            if(!helpers::match(digit, input, context, counter)) {
                throw error(SyntaxError, "Expected at least one digit", counter, input);
            }
            while(helpers::match(digit, input, context, counter)) {}
        }

        helpers::match(exponent, input, context, counter);

        head = counter;
        return true;
    }

    bool rules::exponent(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;
        if(helpers::match(exponent_marker, input, context, counter)) {
            helpers::match(overbar, input, context, counter);

            if(!helpers::match(digit, input, context, counter)) {
                throw error(SyntaxError, "Expected at least one digit", counter, input);
            }

            while(helpers::match(digit, input, context, counter)) {}
            head = counter;
            return true;
        }

        return false;
    }

    bool rules::numeric_scalar_literal(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(real_scalar_literal, input, context, head)) {
            helpers::match(imaginary_part, input, context, head);

            return true;
        }

        return false;
    }

    bool rules::imaginary_part(const std::vector<Char> &input, context<Char> &context, int &head) {
        int counter = head;
        if(helpers::match(complex_marker, input, context, counter)) {
            if(helpers::match(real_scalar_literal, input, context, counter)) {
                head = counter;
                return true;
            }

            throw error(SyntaxError, "Expected a real scalar", counter, input);
        }

        return false;
    }

    bool rules::character_literal(const std::vector<Char> &input, context<Char>& context, int &head) {
        int counter = head;
        if(helpers::match(quote, input, context, counter)) {
            int end = helpers::peek(constants::quote, input, counter);
            if(end != -1) {
                while(helpers::match(nonquote, input, context, counter, end)) {}
                helpers::match(quote, input, context, counter);

                head = counter;
                return true;
            }

            throw error(SyntaxError, "Expected a matching end quote", counter - 1, input);
        }

        return false;
    }

    bool rules::comment(const std::vector<Char> &input, context<Char>& context, int &head) {
        if(helpers::match(lamp, input, context, head)) {
            while(helpers::match(letter, input, context, head)) {}
            return true;
        }
        return false;
    }

    bool rules::any(const std::vector<Char> &input, context<Char> &context, int &head) {
        if(helpers::match(quote, input, context, head)) {}
        else if(helpers::match(nonquote, input, context, head)) {}
        else { return false; }

        return true;
    }

    bool rules::primitive(const std::vector<Char> &input, context<Char> &context, int &head) {
        return helpers::match(ideogram, input, context, head);
    }

    bool rules::space(const std::vector<Char> &input, context<Char> &context, int &head) {
        return helpers::match(constants::blank, input, context, head);
    }

    bool rules::nonquote(const std::vector<Char> &input, context<Char>& context, int &head) {
        if(helpers::match(ideogram, input, context, head)) {}
        else if(helpers::match(digit, input, context, head)) {}
        else if(helpers::match(blank, input, context, head)) {}
        else if(helpers::match(letter, input, context, head)) {}
        else if(helpers::match(lamp, input, context, head)) {}
        else if(helpers::match(del, input, context, head)) {}
        else if(helpers::match(del_tilde, input, context, head)) {}
        else if(helpers::match(quad, input, context, head)) {}
        else if(helpers::match(quote_quad, input, context, head)) {}
        else if(helpers::match(diamond, input, context, head)) {}
        else { return false; }

        return true;
    }

    bool rules::statement_separator(const std::vector<Char> &input, context<Char> &context, int &head) {
        return helpers::match(diamond, input, context, head);
    }

    bool rules::letter(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(
                {
                    constants::A, constants::B, constants::C,
                    constants::D, constants::E, constants::F,
                    constants::G, constants::H, constants::I,
                    constants::J, constants::K, constants::L,
                    constants::M, constants::N, constants::O,
                    constants::P, constants::Q, constants::R,
                    constants::S, constants::T, constants::U,
                    constants::V, constants::W, constants::X,
                    constants::Y, constants::Z,
                    constants::a, constants::b, constants::c,
                    constants::d, constants::e, constants::f,
                    constants::g, constants::h, constants::i,
                    constants::j, constants::k, constants::l,
                    constants::m, constants::n, constants::o,
                    constants::p, constants::q, constants::r,
                    constants::s, constants::t, constants::u,
                    constants::v, constants::w, constants::x,
                    constants::y, constants::z
                }, input, context, head);
    }

    bool rules::digit(const std::vector<Char> &input, context<Char> &context, int &head) {
        return helpers::match(
                {
                    constants::one, constants::two, constants::three,
                    constants::four, constants::five, constants::six,
                    constants::seven, constants::eight, constants::nine,
                    constants::zero
                }, input, context, head);
    }

    bool rules::ideogram(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(
                {
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
                    constants::dollar_sign,
                }, input, context, head);
    }

    bool rules::quote(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::quote, input, context, head);
    }

    bool rules::exponent_marker(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::E, input, context, head);
    }

    bool rules::complex_marker(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::J, input, context, head);
    }

    bool rules::dot(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::dot, input, context, head);
    }

    bool rules::underbar(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::underbar, input, context, head);
    }

    bool rules::overbar(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::overbar, input, context, head);
    }

    bool rules::blank(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::blank, input, context, head);
    }

    bool rules::del(const std::vector<Char>& input, context<Char>& context, int &head) {
        return helpers::match(constants::del, input, context, head);
    }

    bool rules::del_tilde(const std::vector<Char>& input, context<Char>& context, int &head) {
        return helpers::match(constants::del_tilde, input, context, head);
    }

    bool rules::lamp(const std::vector<Char>& input, context<Char>& context, int &head) {
        return helpers::match(constants::up_shoe_jot, input, context, head);
    }

    bool rules::quad(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::quad, input, context, head);
    }

    bool rules::quote_quad(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::quote_quad, input, context, head);
    }

    bool rules::diamond(const std::vector<Char> &input, context<Char>& context, int &head) {
        return helpers::match(constants::diamond, input, context, head);
    }
};