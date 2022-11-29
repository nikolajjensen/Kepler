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

#include "models.h"
#include "models_adapted.h"
#include "rules.h"

namespace kepler {
    namespace lexer {
        // Employee parser definition
        namespace rules {
            namespace x3 = boost::spirit::x3;
            namespace unicode = boost::spirit::x3::unicode;

            using x3::int_;
            using x3::omit;
            using x3::skip;
            using unicode::lit;
            using x3::eps;
            using x3::_val;
            using x3::_attr;
            using x3::attr;
            using x3::double_;
            using x3::lexeme;
            using unicode::char_;

            /*
            //auto const quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];

            // Explicit rule definitions.
            x3::rule<class token_list, models::TokenList> const token_list = "token_list";
            x3::rule<class token, models::Token> const token = "token";

            // Grammar non-terminals.
            auto const alpha = char_(U"⍺");
            auto const omega = char_(U"⍵");
            auto const diamond = char_(U"⋄");
            auto const quote_quad = char_(U"⍞");
            auto const quad = char_(U"⎕");
            auto const lamp = char_(U"⍝");
            auto const del_tilde = char_(U"⍫");
            auto const del = char_(U"∇");
            auto const blank = char_(U" ");
            auto const overbar = char_(U"‾");
            auto const underbar = char_(U"_");
            auto const dot = char_(U".");
            auto const complex_marker = char_(U"J");
            auto const exponent_marker = char_(U"E");
            auto const quote = char_(U"'");

            auto const letter = char_(U"a-zA-Z");
            auto const digit = char_(U"0-9");

            x3::rule<class ideogram, char32_t> const ideogram = "ideogram";
            x3::rule<class nonquote, char32_t> const nonquote = "nonquote";
            x3::rule<class any, char32_t> const any = "any";
            x3::rule<class character_literal, std::u32string> const character_literal = "character_literal";
            x3::rule<class exponent, std::u32string> const exponent = "exponent";
            x3::rule<class real_scalar_literal, std::u32string> const real_scalar_literal = "real_scalar_literal";
            x3::rule<class imaginary_part, std::u32string> const imaginary_part = "imaginary_part";
            x3::rule<class numeric_scalar_literal, std::u32string> const numeric_scalar_literal = "numeric_scalar_literal";
            x3::rule<class numeric_literal, std::u32string> const numeric_literal = "numeric_literal";
            x3::rule<class direct_identifier, std::u32string> const direct_identifier = "direct_identifier";
            x3::rule<class literal_identifier, std::u32string> const literal_identifier = "literal_identifier";
            x3::rule<class distinguished_identifier, std::u32string> const distinguished_identifier = "distinguished_identifier";

            auto const ideogram_def = (char_(U"¨‾<≤=≥>≠∨∧÷+×?⍵∊⍴~↑↓⍳○*→←⍺⌈⌊_∘()[]⊂⊃∩∪⊥⊤|;:\\,./⍒⍋⌽⍉⊖⍟⍱⍲!⌹⍎⍕⍀⌿⍤⍪⍨{}⊢⊣$") | char_(U"-"));
            auto const nonquote_def = ideogram | digit | blank | letter | lamp | del | del_tilde | quad | quote_quad | diamond;
            auto const space = blank;                                                   // Should not generate token.
            auto const any_def = (quote | nonquote);
            auto const character_literal_def = +nonquote;
            auto const exponent_def = exponent_marker >> -overbar >> +digit;
            auto const real_scalar_literal_def = -overbar >> ((+digit >> -dot >> *digit) | dot >> +digit) >> -exponent;
            auto const imaginary_part_def = complex_marker >> real_scalar_literal;
            auto const numeric_scalar_literal_def = real_scalar_literal >> -imaginary_part;
            auto const numeric_literal_def = +(numeric_scalar_literal >> +blank);
            auto const direct_identifier_def = alpha | omega;
            auto const literal_identifier_def = letter >> *(letter | digit | underbar | overbar);
            auto const distinguished_identifier_def = (quote_quad | (quad >> *(letter | digit)));

            //auto const comment = lamp >> *any;                                          // Should not generate token.

            //x3::rule<class primitive_token, models::Token> primitive_token = "primitive_token";
            auto const primitive_token = attr(models::TokenType::Primitive) >> ideogram;
            auto const character_literal_token = attr(models::TokenType::CharacterLiteral) >> character_literal;
            auto const numeric_literal_token = attr(models::TokenType::NumericLiteral) >> numeric_literal;
            auto const literal_identifier_token = attr(models::TokenType::SimpleIdentifier) >> literal_identifier;
            //x3::rule<class distinguished_identifier_token, models::Token> distinguished_identifier_token = "distinguished_identifier_token";
            auto const distinguished_identifier_token = attr(models::TokenType::DistinguishedIdentifier) >> distinguished_identifier;

            //auto const simple_identifier_token = literal_identifier_token | direct_identifier;
            //auto const identifier_token = simple_identifier_token | distinguished_identifier_token;
            //x3::rule<class identifier_token, models::Token> identifier_token = "identifier_token";
            //auto const identifier_token_def = literal_identifier_token | distinguished_identifier_token;

            auto const token_def = primitive_token | distinguished_identifier_token;

            auto const token_list_def = *token_def;

            BOOST_SPIRIT_DEFINE(
                    ideogram, nonquote, any, character_literal, exponent,
                    real_scalar_literal, imaginary_part, numeric_scalar_literal,
                    numeric_literal, direct_identifier, literal_identifier, distinguished_identifier,
                    token, token_list)
            */


            // Basic parsers.
            auto const alpha = char_(U"⍺");
            auto const omega = char_(U"⍵");
            auto const diamond = char_(U"⋄");
            auto const quote_quad = char_(U"⍞");
            auto const quad = char_(U"⎕");
            auto const lamp = char_(U"⍝");
            auto const del_tilde = char_(U"⍫");
            auto const del = char_(U"∇");
            auto const blank = char_(U" ");
            auto const overbar = char_(U"‾");
            auto const underbar = char_(U"_");
            auto const dot = char_(U".");
            auto const complex_marker = char_(U"J");
            auto const exponent_marker = char_(U"E");
            auto const quote = char_(U"'");
            auto const ideogram = (char_(U"¨‾<≤=≥>≠∨∧÷+×?⍵∊⍴~↑↓⍳○*→←⍺⌈⌊_∘()[]⊂⊃∩∪⊥⊤|;:\\,./⍒⍋⌽⍉⊖⍟⍱⍲!⌹⍎⍕⍀⌿⍤⍪⍨{}⊢⊣$") | char_(U"-"));
            auto const digit = char_(U"0-9");
            auto const letter = char_(U"a-zA-Z") | char_(U"∆⍙");

            // Complex parsers.
            auto const statement_separator = x3::rule<class statement_separator, char32_t>{"statement_separator"}
                = diamond;
            auto const nonquote = x3::rule<class nonquote, char32_t>{"nonquote"}
                = ideogram | digit | blank | letter | lamp | del | del_tilde | quad | quote_quad | diamond;
            auto const space = x3::rule<class space>{"space"}
                = blank;
            auto const primitive = x3::rule<class primitive, char32_t>{"primitive"}
                = ideogram;
            auto const any = x3::rule<class any, char32_t>{"any"}
                = quote | nonquote;
            auto const comment = x3::rule<class comment>{"comment"}
                = lamp >> *any;
            auto const character_literal = x3::rule<class character_literal, std::u32string>{"character_literal"}
                = lexeme[+(quote >> *nonquote >> quote)];
            auto const exponent = x3::rule<class exponent, std::u32string>{"exponent"}
                = exponent_marker >> -overbar >> +digit;
            auto const real_scalar_literal = x3::rule<class real_scalar_literal, std::u32string>{"real_scalar_literal"}
                = -overbar >> ((+digit >> -dot >> *digit) | dot >> +digit) >> -exponent;
            auto const imaginary_part = x3::rule<class imaginary_part, std::u32string>{"imaginary_part"}
                = complex_marker >> real_scalar_literal;
            auto const numeric_scalar_literal = x3::rule<class numeric_scalar_literal, std::u32string>{"numeric_scalar_literal"}
                = real_scalar_literal >> -imaginary_part;
            auto const numeric_literal = x3::rule<class numeric_literal, std::u32string>{"numeric_literal"}
                = lexeme[numeric_scalar_literal >> *(+blank >> numeric_scalar_literal)];

            auto const quad_identifier = x3::rule<class quad_identifier, std::u32string>{"quad_identifier"}
                = quad >> *(letter | digit);
            auto const distinguished_identifier = x3::rule<class distinguished_identifier, boost::variant<char32_t, std::u32string>>{"distinguished_identifier"}
                = quote_quad | quad_identifier;

            auto const direct_identifier = x3::rule<class direct_identifier, char32_t>{"direct_identifier"}
                = alpha | omega;
            auto const literal_identifier = x3::rule<class literal_identifier, std::u32string>{"literal_identifier"}
                = letter >> *(letter | digit | underbar | overbar);



            // Token parsers.
            auto const primitive_token = x3::rule<class primitive_token, models::Token>{"primitive_token"}
                = attr(models::TokenType::Primitive) >> primitive;

            auto const character_literal_token = x3::rule<class character_literal_token, models::Token>{"character_literal_token"}
                = attr(models::TokenType::CharacterLiteral) >> character_literal;

            auto const numeric_literal_token = x3::rule<class numeric_literal_token, models::Token>{"numeric_literal_token"}
                = attr(models::TokenType::NumericLiteral) >> numeric_literal;

            auto const distinguished_identifier_token = x3::rule<class distinguished_identifier_token, models::Token>{"distinguished_identifier_token"}
                = attr(models::TokenType::DistinguishedIdentifier) >> distinguished_identifier;

            auto const literal_identifier_token = x3::rule<class literal_identifier_token, models::Token>{"literal_identifier_token"}
                = attr(models::TokenType::SimpleIdentifier) >> literal_identifier;

            auto const direct_identifier_token = x3::rule<class direct_identifier_token, models::Token>{"direct_identifier_token"}
                = attr(models::TokenType::DirectIdentifier) >> direct_identifier;

            auto const statement_separator_token = x3::rule<class statement_separator_token, models::Token>{"statement_separator_token"}
                = attr(models::TokenType::StatementSeparator) >> statement_separator;

            auto const simple_identifier_token = x3::rule<class simple_identifier_token, models::Token>{"simple_identifier_token"}
                = literal_identifier_token | direct_identifier_token;

            auto const identifier_token = x3::rule<class identifier_token, models::Token>{"identifier_token"}
                = simple_identifier_token | distinguished_identifier_token;


            // Token List parser.
            x3::rule<class token_list, models::TokenList> const token_list = "token_list";
            auto const token_list_def = *(identifier_token | numeric_literal_token | primitive_token | character_literal_token | statement_separator_token);


            x3::rule<class skipper, x3::unused_type const> skipper = "skipper";
            auto skipper_def = comment | space;

            BOOST_SPIRIT_DEFINE(skipper, token_list)
        };

        rules::token_list_type token_list() {
            return rules::token_list;
        }

        rules::skipper_parser skipper() {
            return rules::skipper;
        }
    };
};