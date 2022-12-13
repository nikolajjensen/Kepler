//
// Copyright 2022 Nikolaj Banke Jensen.
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

#pragma once

#define BOOST_SPIRIT_X3_UNICODE
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/std_tuple.hpp>
#include <boost/spirit/home/x3/support/utility/annotate_on_success.hpp>

#include "rules.h"
#include "error_handler.h"
#include "../datatypes.h"
#include "../token_class.h"
#include "../token.h"

namespace kepler {
    namespace lexer {
        // Employee parser definition
        namespace rules {
            namespace x3 = boost::spirit::x3;
            namespace unicode = boost::spirit::x3::unicode;

            using x3::_attr;
            using x3::attr;
            using x3::lexeme;
            using unicode::char_;

            // https://stackoverflow.com/questions/71281614/how-do-i-get-which-to-work-correctly-in-boost-spirit-x3-expectation-failure
            template <typename T = x3::unused_type>
            auto as(auto p, char const* name = typeid(decltype(p)).name()) {
                return x3::rule<struct _, T>{name} = p;
            }

            // Basic parsers.
            auto const alpha = x3::rule<struct alpha, Char>{"alpha"} = char_(U"⍺");
            auto const omega = x3::rule<struct omega, Char>{"omega"} = char_(U"⍵");
            auto const diamond = x3::rule<struct diamond, Char>{"diamond"} = char_(U"⋄");
            auto const quote_quad = x3::rule<struct quote_quad, Char>{"quote quad"} = char_(U"⍞");
            auto const quad = x3::rule<struct quad, Char>{"quad"} = char_(U"⎕");
            auto const lamp = x3::rule<struct lamp, Char>{"lamp"} = char_(U"⍝");
            auto const del_tilde = x3::rule<struct del_tilde, Char>{"del tilde"} = char_(U"⍫");
            auto const del = x3::rule<struct del, Char>{"del"} = char_(U"∇");
            auto const blank = x3::rule<struct blank, Char>{"blank"} = char_(U" ");
            auto const overbar = x3::rule<struct overbar, Char>{"overbar"} = char_(U"‾");
            auto const underbar = x3::rule<struct underbar, Char>{"underbar"} = char_(U"_");
            auto const dot = x3::rule<struct dot, Char>{"dot"} = char_(U".");
            auto const complex_marker = x3::rule<struct complex_marker, Char>{"complex marker"} = char_(U"J");
            auto const exponent_marker = x3::rule<struct exponent_marker, Char>{"exponent marker"} = char_(U"E");
            auto const quote = x3::rule<struct quote, Char>{"quote"} = char_(U"'");
            auto const ideogram = x3::rule<struct ideogram, Char>{"ideogram"} = (char_(U"¨‾<≤=≥>≠∨∧÷+×?⍵∊⍴~↑↓⍳○*→←⍺⌈⌊_∘()[]⊂⊃∩∪⊥⊤|;:\\,./⍒⍋⌽⍉⊖⍟⍱⍲!⌹⍎⍕⍀⌿⍤⍪⍨{}⊢⊣$") | char_(U"-"));
            auto const digit = x3::rule<struct digit, Char>{"digit"} = char_(U"0-9");
            auto const letter = x3::rule<struct letter, Char>{"letter"} = char_(U"a-zA-Z") | char_(U"∆⍙");

            // Complex parsers.
            auto const statement_separator = x3::rule<struct statement_separator, Char>{"statement separator"} = diamond;
            auto const nonquote = x3::rule<struct nonquote, Char>{"nonquote"} = ideogram | digit | blank | letter | lamp | del | del_tilde | quad | quote_quad | diamond;
            auto const space = x3::rule<struct space, Char>{"space"} = blank;
            auto const primitive = x3::rule<struct primitive, Char>{"primitive"} = ideogram;
            auto const any = x3::rule<struct any, Char>{"any"} = quote | nonquote;
            auto const comment = x3::rule<struct comment, List<Char>>{"comment"} = lamp >> *any;
            auto const character_literal = x3::rule<struct character_literal, List<Char>>{"character literal"} = lexeme[+(quote > *nonquote > quote)];
            auto const exponent = x3::rule<struct exponent, List<Char>>{"exponent"} = exponent_marker > -overbar > as<List<Char>>(+digit, "one or more digits");
            auto const real_scalar_literal = x3::rule<struct real_scalar_literal, List<Char>>{"real scalar"} = -overbar >> ((+digit >> -dot >> *digit) | dot >> +digit) >> -exponent;
            auto const imaginary_part = x3::rule<struct imaginary_part, List<Char>>{"imaginary part"} = complex_marker >> real_scalar_literal;
            auto const numeric_scalar_literal = x3::rule<struct numeric_scalar_literal, List<Char>>{"numeric scalar"} = real_scalar_literal >> -imaginary_part;
            auto const numeric_literal = x3::rule<struct numeric_literal, List<Char>>{"numeric literal"} = lexeme[numeric_scalar_literal >> *(+blank >> numeric_scalar_literal)];
            auto const quad_identifier = x3::rule<struct quad_identifier, List<Char>>{"quad identifier"} = quad >> *(letter | digit);
            auto const distinguished_identifier = x3::rule<struct distinguished_identifier, boost::variant<Char, List<Char>>>{"distinguished identifier"} = quote_quad | quad_identifier;
            auto const direct_identifier = x3::rule<struct direct_identifier, Char>{"direct identifier"} = alpha | omega;
            auto const literal_identifier = x3::rule<struct literal_identifier, List<Char>>{"literal identifier"} = lexeme[letter >> *(letter | digit | underbar | overbar)];


            // Token parsers.
            auto const primitive_token = x3::rule<struct primitive_token, Token>{"primitive_token"} = attr(TokenClass::PrimitiveToken) >> primitive;
            auto const character_literal_token = x3::rule<struct character_literal_token, Token>{"character_literal_token"} = attr(TokenClass::CharacterLiteralToken) >> character_literal;
            auto const numeric_literal_token = x3::rule<struct numeric_literal_token, Token>{"numeric_literal_token"} = attr(TokenClass::NumericLiteralToken) >> numeric_literal;
            auto const distinguished_identifier_token = x3::rule<struct distinguished_identifier_token, Token>{"distinguished_identifier_token"} = attr(TokenClass::DistinguishedIdentifierToken) >> distinguished_identifier;
            auto const literal_identifier_token = x3::rule<struct literal_identifier_token, Token>{"literal_identifier_token"} = (attr(TokenClass::SimpleIdentifierToken) >> literal_identifier);
            auto const direct_identifier_token = x3::rule<struct direct_identifier_token, Token>{"direct_identifier_token"} = attr(TokenClass::DirectIdentifierToken) >> direct_identifier;
            auto const simple_identifier_token = x3::rule<struct simple_identifier_token, Token>{"simple_identifier_token"} = literal_identifier_token | direct_identifier_token;
            auto const identifier_token = x3::rule<struct identifier_token, Token>{"identifier_token"} = simple_identifier_token | distinguished_identifier_token;



            // Token List parser.
            struct token_list_class;
            x3::rule<token_list_class, List<Token>> token_list = "token_list";
            auto const token_list_def = *(identifier_token | numeric_literal_token | primitive_token | character_literal_token);
            struct token_list_class : x3::annotate_on_success, error_handler_base {};

            // Skipper.
            x3::rule<class skipper_class, x3::unused_type const> skipper = "skipper";
            auto skipper_def = comment | space | statement_separator;


            BOOST_SPIRIT_DEFINE(skipper, token_list)
        };

        rules::token_list_type const& token_list() {
            return rules::token_list;
        }

        rules::skipper_type const& skipper() {
            return rules::skipper;
        }
    };
};