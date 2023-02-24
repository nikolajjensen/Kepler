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
#include <catch2/catch_test_macros.hpp>
#include "macros.h"
#include "testing/matcher.h"
#include "core/token_class.h"
#include "core/token.h"
#include "testing/fixtures/lexer_fixture.h"
#include "string_maker.h"

TEST_CASE_METHOD(lexer_fixture, "iso-example", "[lexer][iso]") {
    CHECK_NOTHROW(run("ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT"));

    CHECK_THAT(run("ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT"),
               Outputs({
                   {kepler::SimpleIdentifierToken, "ABC"},
                   {kepler::PrimitiveToken, "←"},
                   {kepler::SimpleIdentifierToken, "FN"},
                   {kepler::DistinguishedIdentifierToken, "⎕"},
                   {kepler::PrimitiveToken, "⌽"},
                   {kepler::PrimitiveToken, "["},
                   {kepler::NumericLiteralToken, "1"},
                   {kepler::PrimitiveToken, "+"},
                   {kepler::NumericLiteralToken, "0"},
                   {kepler::PrimitiveToken, "]"},
                   {kepler::SimpleIdentifierToken, "DEF"},
                   {kepler::PrimitiveToken, "["},
                   {kepler::NumericLiteralToken, "1"},
                   {kepler::PrimitiveToken, ";"},
                   {kepler::NumericLiteralToken, "5 6"},
                   {kepler::PrimitiveToken, "]"},
                   {kepler::PrimitiveToken, "×"},
                   {kepler::NumericLiteralToken, "3.45E4"},
                   {kepler::PrimitiveToken, ","},
                   {kepler::PrimitiveToken, "⍴"},
                   {kepler::CharacterLiteralToken, "'ABC'"},
               }));
}

TEST_CASE_METHOD(lexer_fixture, "comment", "[lexer][comment]") {
    CHECK_NOTHROW(run("⍝This is a comment!"));
    CHECK_THAT(run("⍝This is a comment!"), Outputs({}));

    CHECK_NOTHROW(run("⍝ This is a comment!"));
    CHECK_THAT(run("⍝ This is a comment!"), Outputs({}));

    CHECK_NOTHROW(run("⍝"));
    CHECK_THAT(run("⍝"), Outputs({}));

    CHECK_NOTHROW(run("⍝''"));
    CHECK_THAT(run("⍝''"), Outputs({}));

    CHECK_NOTHROW(run("⍝∇"));
    CHECK_THAT(run("⍝∇"), Outputs({}));

    CHECK_NOTHROW(run("⍝◊"));
    CHECK_THAT(run("⍝◊"), Outputs({}));
}

TEST_CASE_METHOD(lexer_fixture, "character-literal", "[lexer][character-literal]") {

    CHECK_NOTHROW(run("'ABC'"));
    CHECK_THAT(run("'ABC'"),
               Outputs({{kepler::CharacterLiteralToken, "'ABC'"}}));

    CHECK_THAT_THROWS(run("'ABC"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("ABC'"), Throws(kepler::SyntaxError));

    CHECK_NOTHROW(run("''"));
    CHECK_THAT(run("''"),
               Outputs({{kepler::CharacterLiteralToken, "''"}}));

    CHECK_NOTHROW(run("'   ABC '"));
    CHECK_THAT(run("'   ABC '"),
               Outputs({{kepler::CharacterLiteralToken, "'   ABC '"}}));

    CHECK_NOTHROW(run("'  '"));
    CHECK_THAT(run("'  '"),
               Outputs({{kepler::CharacterLiteralToken, "'  '"}}));

    CHECK_NOTHROW(run("'  '"));
    CHECK_THAT(run("'  '"),
               Outputs({{kepler::CharacterLiteralToken, "'  '"}}));

    CHECK_THAT_THROWS(run("'''"), Throws(kepler::SyntaxError));

    CHECK_NOTHROW(run("'a1 ⍝Not removed! ⌊⎕◊123ABC acb ⍫ ⍞'"));
    CHECK_THAT(run("'a1 ⍝Not removed! ⌊⎕◊123ABC acb ⍫ ⍞'"),
               Outputs({{kepler::CharacterLiteralToken, "'a1 ⍝Not removed! ⌊⎕◊123ABC acb ⍫ ⍞'"}}));

    CHECK_NOTHROW(run("'abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ'"));
    CHECK_THAT(run("'abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ'"),
               Outputs({{kepler::CharacterLiteralToken, "'abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ'"}}));

    CHECK_NOTHROW(run("'1234567890'"));
    CHECK_THAT(run("'1234567890'"),
               Outputs({{kepler::CharacterLiteralToken, "'1234567890'"}}));
}

TEST_CASE_METHOD(lexer_fixture, "real-scalar-literal", "[lexer][real-scalar-literal]") {
    CHECK_NOTHROW(run("1"));
    CHECK_THAT(run("1"),
               Outputs({
                   {kepler::NumericLiteralToken, "1"}
               }));

    CHECK_NOTHROW(run("123"));
    CHECK_THAT(run("123"),
               Outputs({
                   {kepler::NumericLiteralToken, "123"}
               }));

    CHECK_NOTHROW(run("1."));
    CHECK_THAT(run("1."),
               Outputs({
                   {kepler::NumericLiteralToken, "1."}
               }));

    CHECK_NOTHROW(run("123."));
    CHECK_THAT(run("123."),
               Outputs({
                   {kepler::NumericLiteralToken, "123."}
               }));

    CHECK_NOTHROW(run("1.5"));
    CHECK_THAT(run("1.5"),
               Outputs({
                   {kepler::NumericLiteralToken, "1.5"}
               }));

    CHECK_NOTHROW(run("123.567"));
    CHECK_THAT(run("123.567"),
               Outputs({
                   {kepler::NumericLiteralToken, "123.567"}
               }));

    CHECK_NOTHROW(run(".567"));
    CHECK_THAT(run(".567"),
               Outputs({
                   {kepler::NumericLiteralToken, ".567"}
               }));

    CHECK_NOTHROW(run("¯1"));
    CHECK_THAT(run("¯1"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1"}
               }));

    CHECK_NOTHROW(run("¯123"));
    CHECK_THAT(run("¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123"}
               }));

    CHECK_NOTHROW(run("¯1."));
    CHECK_THAT(run("¯1."),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1."}
               }));

    CHECK_NOTHROW(run("¯123."));
    CHECK_THAT(run("¯123."),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123."}
               }));

    CHECK_NOTHROW(run("¯1.5"));
    CHECK_THAT(run("¯1.5"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1.5"}
               }));

    CHECK_NOTHROW(run("¯123.567"));
    CHECK_THAT(run("¯123.567"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123.567"}
               }));

    CHECK_NOTHROW(run("¯.567"));
    CHECK_THAT(run("¯.567"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯.567"}
               }));

    CHECK_NOTHROW(run("1E123"));
    CHECK_THAT(run("1E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "1E123"}
               }));

    CHECK_NOTHROW(run("123E123"));
    CHECK_THAT(run("123E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "123E123"}
               }));

    CHECK_NOTHROW(run("1.E123"));
    CHECK_THAT(run("1.E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "1.E123"}
               }));

    CHECK_NOTHROW(run("123.E123"));
    CHECK_THAT(run("123.E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "123.E123"}
               }));

    CHECK_NOTHROW(run("1.5E123"));
    CHECK_THAT(run("1.5E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "1.5E123"}
               }));

    CHECK_NOTHROW(run("123.567E123"));
    CHECK_THAT(run("123.567E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "123.567E123"}
               }));

    CHECK_NOTHROW(run(".567E123"));
    CHECK_THAT(run(".567E123"),
               Outputs({
                   {kepler::NumericLiteralToken, ".567E123"}
               }));

    CHECK_NOTHROW(run("¯1E123"));
    CHECK_THAT(run("¯1E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1E123"}
               }));

    CHECK_NOTHROW(run("¯123E123"));
    CHECK_THAT(run("¯123E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123E123"}
               }));

    CHECK_NOTHROW(run("¯1.E123"));
    CHECK_THAT(run("¯1.E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1.E123"}
               }));

    CHECK_NOTHROW(run("¯123.E123"));
    CHECK_THAT(run("¯123.E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123.E123"}
               }));

    CHECK_NOTHROW(run("¯1.5E123"));
    CHECK_THAT(run("¯1.5E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1.5E123"}
               }));

    CHECK_NOTHROW(run("¯123.567E123"));
    CHECK_THAT(run("¯123.567E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123.567E123"}
               }));

    CHECK_NOTHROW(run("¯.567E123"));
    CHECK_THAT(run("¯.567E123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯.567E123"}
               }));

    CHECK_NOTHROW(run("1E¯123"));
    CHECK_THAT(run("1E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "1E¯123"}
               }));

    CHECK_NOTHROW(run("123E¯123"));
    CHECK_THAT(run("123E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "123E¯123"}
               }));

    CHECK_NOTHROW(run("1.E¯123"));
    CHECK_THAT(run("1.E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "1.E¯123"}
               }));

    CHECK_NOTHROW(run("123.E¯123"));
    CHECK_THAT(run("123.E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "123.E¯123"}
               }));

    CHECK_NOTHROW(run("1.5E¯123"));
    CHECK_THAT(run("1.5E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "1.5E¯123"}
               }));

    CHECK_NOTHROW(run("123.567E¯123"));
    CHECK_THAT(run("123.567E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "123.567E¯123"}
               }));

    CHECK_NOTHROW(run(".567E¯123"));
    CHECK_THAT(run(".567E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, ".567E¯123"}
               }));

    CHECK_NOTHROW(run("¯1E¯123"));
    CHECK_THAT(run("¯1E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1E¯123"}
               }));

    CHECK_NOTHROW(run("¯123E¯123"));
    CHECK_THAT(run("¯123E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123E¯123"}
               }));

    CHECK_NOTHROW(run("¯1.E¯123"));
    CHECK_THAT(run("¯1.E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1.E¯123"}
               }));

    CHECK_NOTHROW(run("¯123.E¯123"));
    CHECK_THAT(run("¯123.E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123.E¯123"}
               }));

    CHECK_NOTHROW(run("¯1.5E¯123"));
    CHECK_THAT(run("¯1.5E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯1.5E¯123"}
               }));

    CHECK_NOTHROW(run("¯123.567E¯123"));
    CHECK_THAT(run("¯123.567E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯123.567E¯123"}
               }));

    CHECK_NOTHROW(run("¯.567E¯123"));
    CHECK_THAT(run("¯.567E¯123"),
               Outputs({
                   {kepler::NumericLiteralToken, "¯.567E¯123"}
               }));

    CHECK_THAT_THROWS(run("1E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.5E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.567E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run(".567E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.5E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.567E"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯.567E"), Throws(kepler::SyntaxError));

    CHECK_THAT_THROWS(run("1E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.5E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.567E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run(".567E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.5E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.567E¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯.567E¯"), Throws(kepler::SyntaxError));

    CHECK_NOTHROW(run("1.."));
    CHECK_THAT(run("1.."),
               Outputs({
                   {kepler::NumericLiteralToken, "1."},
                   {kepler::PrimitiveToken, "."}
               }));

    CHECK_NOTHROW(run("..1"));
    CHECK_THAT(run("..1"),
               Outputs({
                   {kepler::PrimitiveToken, "."},
                   {kepler::NumericLiteralToken, ".1"},
               }));

    CHECK_NOTHROW(run("1.2.2"));
    CHECK_THAT(run("1.2.2"),
               Outputs({
                   {kepler::NumericLiteralToken, "1.2"},
                   {kepler::PrimitiveToken, "."},
                   {kepler::NumericLiteralToken, "2"},
               }));
}

TEST_CASE_METHOD(lexer_fixture, "numeric-scalar-literal", "[lexer][numeric-scalar-literal]") {
    CHECK_NOTHROW(run("1.5J12"));
    CHECK_THAT(run("1.5J12"),
               Outputs({{kepler::NumericLiteralToken, "1.5J12"}}));

    CHECK_NOTHROW(run("1.5J12.5"));
    CHECK_THAT(run("1.5J12.5"),
               Outputs({{kepler::NumericLiteralToken, "1.5J12.5"}}));

    CHECK_NOTHROW(run("1.5E1J12.5E1"));
    CHECK_THAT(run("1.5E1J12.5E1"),
               Outputs({{kepler::NumericLiteralToken, "1.5E1J12.5E1"}}));

    CHECK_NOTHROW(run("1.5J¯12"));
    CHECK_THAT(run("1.5J¯12"),
               Outputs({{kepler::NumericLiteralToken, "1.5J¯12"}}));

    CHECK_NOTHROW(run("¯1.5J¯12.5"));
    CHECK_THAT(run("¯1.5J¯12.5"),
               Outputs({{kepler::NumericLiteralToken, "¯1.5J¯12.5"}}));

    CHECK_NOTHROW(run("¯1.5E1J12.5E¯1"));
    CHECK_THAT(run("¯1.5E1J12.5E¯1"),
               Outputs({{kepler::NumericLiteralToken, "¯1.5E1J12.5E¯1"}}));

    CHECK_THAT_THROWS(run("1J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.5J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.567J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run(".567J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.5J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.567J"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯.567J"), Throws(kepler::SyntaxError));

    CHECK_THAT_THROWS(run("1J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("1.5J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("123.567J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run(".567J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯1.5J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯123.567J¯"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("¯.567J¯"), Throws(kepler::SyntaxError));
}

TEST_CASE_METHOD(lexer_fixture, "numeric-literal", "[lexer][numeric-literal]") {
    CHECK_NOTHROW(run("1.5J12 1.5J12"));
    CHECK_THAT(run("1.5J12 1.5J12"),
               Outputs({{kepler::NumericLiteralToken, "1.5J12 1.5J12"}}));

    CHECK_NOTHROW(run("1.5J12.5 1.5J12.5 1.5J12.5"));
    CHECK_THAT(run("1.5J12.5 1.5J12.5 1.5J12.5"),
               Outputs({{kepler::NumericLiteralToken, "1.5J12.5 1.5J12.5 1.5J12.5"}}));

    CHECK_NOTHROW(run("      1.5E1J12.5E1     1.5E1J12.5E1       1.5E1J12.5E1 "));
    CHECK_THAT(run("      1.5E1J12.5E1     1.5E1J12.5E1       1.5E1J12.5E1 "),
               Outputs({{kepler::NumericLiteralToken, "1.5E1J12.5E1     1.5E1J12.5E1       1.5E1J12.5E1"}}));

    CHECK_NOTHROW(run("     1.5J¯12 1.5J¯12 1.5J¯12"));
    CHECK_THAT(run("     1.5J¯12 1.5J¯12 1.5J¯12"),
               Outputs({{kepler::NumericLiteralToken, "1.5J¯12 1.5J¯12 1.5J¯12"}}));

    CHECK_NOTHROW(run("   ¯1.5J¯12.5    "));
    CHECK_THAT(run("   ¯1.5J¯12.5    "),
               Outputs({{kepler::NumericLiteralToken, "¯1.5J¯12.5"}}));

    CHECK_NOTHROW(run("¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 "));
    CHECK_THAT(run("¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 "),
               Outputs({{kepler::NumericLiteralToken, "¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1"}}));
}

TEST_CASE_METHOD(lexer_fixture, "distinguished-identifier", "[lexer][distinguished-identifier]") {
    CHECK_NOTHROW(run("⍞"));
    CHECK_THAT(run("⍞"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⍞"}}));

    CHECK_NOTHROW(run("⎕"));
    CHECK_THAT(run("⎕"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⎕"}}));

    CHECK_THAT_THROWS(run("⍞Hello"), Throws(kepler::SyntaxError));

    CHECK_NOTHROW(run("⍞ Hello"));
    CHECK_THAT(run("⍞ Hello"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⍞"}, {kepler::SimpleIdentifierToken, "Hello"}}));

    CHECK_THAT_THROWS(run("⍞⎕"), Throws(kepler::SyntaxError));

    CHECK_NOTHROW(run("⍞ ⎕"));
    CHECK_THAT(run("⍞ ⎕"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⍞"}, {kepler::DistinguishedIdentifierToken, "⎕"}}));

    CHECK_NOTHROW(run("⎕ Hello"));
    CHECK_THAT(run("⎕ Hello"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⎕"}, {kepler::SimpleIdentifierToken, "Hello"}}));

    CHECK_NOTHROW(run("⎕Hello"));
    CHECK_THAT(run("⎕Hello"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⎕Hello"}}));

    CHECK_NOTHROW(run("⎕Hello123"));
    CHECK_THAT(run("⎕Hello123"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⎕Hello123"}}));

    CHECK_NOTHROW(run("⎕123"));
    CHECK_THAT(run("⎕123"),
               Outputs({{kepler::DistinguishedIdentifierToken, "⎕123"}}));
}

TEST_CASE_METHOD(lexer_fixture, "direct-identifier", "[lexer][direct-identifier]") {
    CHECK_NOTHROW(run("⍺"));
    CHECK_THAT(run("⍺"),
               Outputs({}));

    CHECK_NOTHROW(run("⍵"));
    CHECK_THAT(run("⍵"),
               Outputs({}));

    CHECK_NOTHROW(run(" ⍵ "));
    CHECK_NOTHROW(run(" ⍺ "));

    CHECK_NOTHROW(run("⍺+⍵"));
    CHECK_THAT(run("⍺+⍵"),
               Outputs({{kepler::PrimitiveToken, "+"}}));

    CHECK_NOTHROW(run(" ⍺ +⍵"));
    CHECK_THAT(run(" ⍺ +⍵"),
               Outputs({{kepler::PrimitiveToken, "+"}}));
}

TEST_CASE_METHOD(lexer_fixture, "literal-identifier", "[lexer][literal-identifier]") {
    CHECK_NOTHROW(run("a"));
    CHECK_THAT(run("a"),
               Outputs({{kepler::SimpleIdentifierToken, "a"}}));

    CHECK_NOTHROW(run("Q"));
    CHECK_THAT(run("Q"),
               Outputs({{kepler::SimpleIdentifierToken, "Q"}}));

    CHECK_NOTHROW(run("ab"));
    CHECK_THAT(run("ab"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"}}));

    CHECK_NOTHROW(run("aQ"));
    CHECK_THAT(run("aQ"),
               Outputs({{kepler::SimpleIdentifierToken, "aQ"}}));

    CHECK_NOTHROW(run("Aq"));
    CHECK_THAT(run("Aq"),
               Outputs({{kepler::SimpleIdentifierToken, "Aq"}}));

    CHECK_NOTHROW(run("AqW"));
    CHECK_THAT(run("AqW"),
               Outputs({{kepler::SimpleIdentifierToken, "AqW"}}));

    CHECK_NOTHROW(run("a1"));
    CHECK_THAT(run("a1"),
               Outputs({{kepler::SimpleIdentifierToken, "a1"}}));

    CHECK_NOTHROW(run("a1a"));
    CHECK_THAT(run("a1a"),
               Outputs({{kepler::SimpleIdentifierToken, "a1a"}}));

    CHECK_NOTHROW(run("Q¯1"));
    CHECK_THAT(run("Q¯1"),
               Outputs({{kepler::SimpleIdentifierToken, "Q¯1"}}));

    CHECK_NOTHROW(run("a¯_1"));
    CHECK_THAT(run("a¯_1"),
               Outputs({{kepler::SimpleIdentifierToken, "a¯_1"}}));

    CHECK_NOTHROW(run("a¯_1bT582"));
    CHECK_THAT(run("a¯_1bT582"),
               Outputs({{kepler::SimpleIdentifierToken, "a¯_1bT582"}}));
}

TEST_CASE_METHOD(lexer_fixture, "line", "[lexer][line]") {
    CHECK_NOTHROW(run("a"));
    CHECK_THAT(run("a"),
               Outputs({{kepler::SimpleIdentifierToken, "a"}}));

    CHECK_NOTHROW(run("ab qt"));
    CHECK_THAT(run("ab qt"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::SimpleIdentifierToken, "qt"}}));

    CHECK_NOTHROW(run("ab 1 2 3"));
    CHECK_THAT(run("ab 1 2 3"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::NumericLiteralToken, "1 2 3"}}));

    CHECK_NOTHROW(run("ab 1 2 3⌽123"));
    CHECK_THAT(run("ab 1 2 3⌽123"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("ab 1 2 3⌽123 ⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3⌽123 ⍝This is discarded"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("ab 1 2 3⌽123⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3⌽123⍝This is discarded"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("ab 1 2 3 ⌽ 123"));
    CHECK_THAT(run("ab 1 2 3 ⌽ 123"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("ab 1 2 3 ⌽ 123 ⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3 ⌽ 123 ⍝This is discarded"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("ab 1 2 3 ⌽ 123⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3 ⌽ 123⍝This is discarded"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("ab ◊ 1 2 3 ⌽ 123⍝This is discarded"));
    CHECK_THAT(run("ab ◊ 1 2 3 ⌽ 123⍝This is discarded"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::StatementSeparatorToken, "◊"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("ab◊1 2 3 ⌽ 123⍝This is discarded"));
    CHECK_THAT(run("ab◊1 2 3 ⌽ 123⍝This is discarded"),
               Outputs({{kepler::SimpleIdentifierToken, "ab"},
                        {kepler::StatementSeparatorToken, "◊"},
                        {kepler::NumericLiteralToken, "1 2 3"},
                        {kepler::PrimitiveToken, "⌽"},
                        {kepler::NumericLiteralToken, "123"}}));

    CHECK_NOTHROW(run("◊◊  ◊◊     1 2 3.5⍝This is discarded"));
    CHECK_THAT(run("◊◊  ◊◊     1 2 3.5⍝This is discarded"),
               Outputs({{kepler::StatementSeparatorToken, "◊"},
                        {kepler::StatementSeparatorToken, "◊"},
                        {kepler::StatementSeparatorToken, "◊"},
                        {kepler::StatementSeparatorToken, "◊"},
                        {kepler::NumericLiteralToken, "1 2 3.5"}}));
}