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
#include "core/token_type.h"
#include "testing/fixtures/tokenizer_fixture.h"

TEST_CASE_METHOD(TokenizerFixture, "comment", "[comment][lexer]") {
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

TEST_CASE_METHOD(TokenizerFixture, "character-literal", "[character-literal][lexer]") {

    CHECK_NOTHROW(run("'ABC'"));
    CHECK_THAT(run("'ABC'"), Outputs({{kepler::STRING, U"ABC"}}));

    CHECK_THAT_THROWS(run("'ABC"), Throws(kepler::SyntaxError));
    CHECK_THAT_THROWS(run("ABC'"), Throws(kepler::SyntaxError));

    CHECK_NOTHROW(run("''"));
    CHECK_THAT(run("''"), Outputs({{kepler::STRING, U""}}));

    CHECK_NOTHROW(run("'   ABC '"));
    CHECK_THAT(run("'   ABC '"), Outputs({{kepler::STRING, U"   ABC "}}));

    CHECK_NOTHROW(run("'  '"));
    CHECK_THAT(run("'  '"), Outputs({{kepler::STRING, U"  "}}));

    CHECK_NOTHROW(run("'  '"));
    CHECK_THAT(run("'  '"), Outputs({{kepler::STRING, U"  "}}));

    CHECK_THAT_THROWS(run("'''"), Throws(kepler::SyntaxError));

    CHECK_NOTHROW(run("'a1 ⍝Not removed! ⌊⎕◊123ABC acb ⍫ ⍞'"));
    CHECK_THAT(run("'a1 ⍝Not removed! ⌊⎕◊123ABC acb ⍫ ⍞'"),
               Outputs({{kepler::STRING, U"a1 ⍝Not removed! ⌊⎕◊123ABC acb ⍫ ⍞"}}));

    CHECK_NOTHROW(run("'abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ'"));
    CHECK_THAT(run("'abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ'"),
               Outputs({{kepler::STRING, U"abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ"}}));

    CHECK_NOTHROW(run("'1234567890'"));
    CHECK_THAT(run("'1234567890'"),
               Outputs({{kepler::STRING, U"1234567890"}}));
}

TEST_CASE_METHOD(TokenizerFixture, "real-scalar-literal", "[tokenizer][real-scalar-literal]") {
    CHECK_NOTHROW(run("1"));
    CHECK_THAT(run("1"), Outputs({{kepler::NUMBER, U"1"}}));

    CHECK_NOTHROW(run("123"));
    CHECK_THAT(run("123"), Outputs({{kepler::NUMBER, U"123"}}));

    CHECK_NOTHROW(run("1."));
    CHECK_THAT(run("1."), Outputs({{kepler::NUMBER, U"1."}}));

    CHECK_NOTHROW(run("123."));
    CHECK_THAT(run("123."), Outputs({{kepler::NUMBER, U"123."}}));

    CHECK_NOTHROW(run("1.5"));
    CHECK_THAT(run("1.5"), Outputs({{kepler::NUMBER, U"1.5"}}));

    CHECK_NOTHROW(run("123.567"));
    CHECK_THAT(run("123.567"), Outputs({{kepler::NUMBER, U"123.567"}}));

    CHECK_NOTHROW(run(".567"));
    CHECK_THAT(run(".567"), Outputs({{kepler::NUMBER, U".567"}}));

    CHECK_NOTHROW(run("¯1"));
    CHECK_THAT(run("¯1"), Outputs({{kepler::NUMBER, U"-1"}}));

    CHECK_NOTHROW(run("¯123"));
    CHECK_THAT(run("¯123"), Outputs({{kepler::NUMBER, U"-123"}}));

    CHECK_NOTHROW(run("¯1."));
    CHECK_THAT(run("¯1."), Outputs({{kepler::NUMBER, U"-1."}}));

    CHECK_NOTHROW(run("¯123."));
    CHECK_THAT(run("¯123."), Outputs({{kepler::NUMBER, U"-123."}}));

    CHECK_NOTHROW(run("¯1.5"));
    CHECK_THAT(run("¯1.5"), Outputs({{kepler::NUMBER, U"-1.5"}}));

    CHECK_NOTHROW(run("¯123.567"));
    CHECK_THAT(run("¯123.567"), Outputs({{kepler::NUMBER, U"-123.567"}}));

    CHECK_NOTHROW(run("¯.567"));
    CHECK_THAT(run("¯.567"), Outputs({{kepler::NUMBER, U"-.567"}}));

    CHECK_NOTHROW(run("1E123"));
    CHECK_THAT(run("1E123"), Outputs({{kepler::NUMBER, U"1E123"}}));

    CHECK_NOTHROW(run("123E123"));
    CHECK_THAT(run("123E123"), Outputs({{kepler::NUMBER, U"123E123"}}));

    CHECK_NOTHROW(run("1.E123"));
    CHECK_THAT(run("1.E123"), Outputs({{kepler::NUMBER, U"1.E123"}}));

    CHECK_NOTHROW(run("123.E123"));
    CHECK_THAT(run("123.E123"), Outputs({{kepler::NUMBER, U"123.E123"}}));

    CHECK_NOTHROW(run("1.5E123"));
    CHECK_THAT(run("1.5E123"), Outputs({{kepler::NUMBER, U"1.5E123"}}));

    CHECK_NOTHROW(run("123.567E123"));
    CHECK_THAT(run("123.567E123"), Outputs({{kepler::NUMBER, U"123.567E123"}}));

    CHECK_NOTHROW(run(".567E123"));
    CHECK_THAT(run(".567E123"), Outputs({{kepler::NUMBER, U".567E123"}}));

    CHECK_NOTHROW(run("¯1E123"));
    CHECK_THAT(run("¯1E123"), Outputs({{kepler::NUMBER, U"-1E123"}}));

    CHECK_NOTHROW(run("¯123E123"));
    CHECK_THAT(run("¯123E123"), Outputs({{kepler::NUMBER, U"-123E123"}}));

    CHECK_NOTHROW(run("¯1.E123"));
    CHECK_THAT(run("¯1.E123"), Outputs({{kepler::NUMBER, U"-1.E123"}}));

    CHECK_NOTHROW(run("¯123.E123"));
    CHECK_THAT(run("¯123.E123"), Outputs({{kepler::NUMBER, U"-123.E123"}}));

    CHECK_NOTHROW(run("¯1.5E123"));
    CHECK_THAT(run("¯1.5E123"), Outputs({{kepler::NUMBER, U"-1.5E123"}}));

    CHECK_NOTHROW(run("¯123.567E123"));
    CHECK_THAT(run("¯123.567E123"), Outputs({{kepler::NUMBER, U"-123.567E123"}}));

    CHECK_NOTHROW(run("¯.567E123"));
    CHECK_THAT(run("¯.567E123"), Outputs({{kepler::NUMBER, U"-.567E123"}}));

    CHECK_NOTHROW(run("1E¯123"));
    CHECK_THAT(run("1E¯123"), Outputs({{kepler::NUMBER, U"1E-123"}}));

    CHECK_NOTHROW(run("123E¯123"));
    CHECK_THAT(run("123E¯123"), Outputs({{kepler::NUMBER, U"123E-123"}}));

    CHECK_NOTHROW(run("1.E¯123"));
    CHECK_THAT(run("1.E¯123"), Outputs({{kepler::NUMBER, U"1.E-123"}}));

    CHECK_NOTHROW(run("123.E¯123"));
    CHECK_THAT(run("123.E¯123"), Outputs({{kepler::NUMBER, U"123.E-123"}}));

    CHECK_NOTHROW(run("1.5E¯123"));
    CHECK_THAT(run("1.5E¯123"), Outputs({{kepler::NUMBER, U"1.5E-123"}}));

    CHECK_NOTHROW(run("123.567E¯123"));
    CHECK_THAT(run("123.567E¯123"), Outputs({{kepler::NUMBER, U"123.567E-123"}}));

    CHECK_NOTHROW(run(".567E¯123"));
    CHECK_THAT(run(".567E¯123"), Outputs({{kepler::NUMBER, U".567E-123"}}));

    CHECK_NOTHROW(run("¯1E¯123"));
    CHECK_THAT(run("¯1E¯123"), Outputs({{kepler::NUMBER, U"-1E-123"}}));

    CHECK_NOTHROW(run("¯123E¯123"));
    CHECK_THAT(run("¯123E¯123"), Outputs({{kepler::NUMBER, U"-123E-123"}}));

    CHECK_NOTHROW(run("¯1.E¯123"));
    CHECK_THAT(run("¯1.E¯123"), Outputs({{kepler::NUMBER, U"-1.E-123"}}));

    CHECK_NOTHROW(run("¯123.E¯123"));
    CHECK_THAT(run("¯123.E¯123"), Outputs({{kepler::NUMBER, U"-123.E-123"}}));

    CHECK_NOTHROW(run("¯1.5E¯123"));
    CHECK_THAT(run("¯1.5E¯123"), Outputs({{kepler::NUMBER, U"-1.5E-123"}}));

    CHECK_NOTHROW(run("¯123.567E¯123"));
    CHECK_THAT(run("¯123.567E¯123"), Outputs({{kepler::NUMBER, U"-123.567E-123"}}));

    CHECK_NOTHROW(run("¯.567E¯123"));
    CHECK_THAT(run("¯.567E¯123"), Outputs({{kepler::NUMBER, U"-.567E-123"}}));

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

    CHECK_THAT_THROWS(run("1.."), Throws(kepler::SyntaxError));
    // Not a lexer error, because first dot is Product. Parser should catch SyntaxError.
    CHECK_NOTHROW(run("..1"));

    CHECK_NOTHROW(run("1.2.2"));
    CHECK_THAT(run("1.2.2"), Outputs({{kepler::NUMBER, U"1.2"}, {kepler::NUMBER, U".2"}}));
}

TEST_CASE_METHOD(TokenizerFixture, "numeric-scalar-literal", "[numeric-scalar-literal][lexer]") {
    CHECK_NOTHROW(run("1.5J12"));
    CHECK_THAT(run("1.5J12"), Outputs({{kepler::NUMBER, U"1.5J12"}}));

    CHECK_NOTHROW(run("1.5J12.5"));
    CHECK_THAT(run("1.5J12.5"), Outputs({{kepler::NUMBER, U"1.5J12.5"}}));

    CHECK_NOTHROW(run("1.5E1J12.5E1"));
    CHECK_THAT(run("1.5E1J12.5E1"), Outputs({{kepler::NUMBER, U"1.5E1J12.5E1"}}));

    CHECK_NOTHROW(run("1.5J¯12"));
    CHECK_THAT(run("1.5J¯12"), Outputs({{kepler::NUMBER, U"1.5J-12"}}));

    CHECK_NOTHROW(run("¯1.5J¯12.5"));
    CHECK_THAT(run("¯1.5J¯12.5"), Outputs({{kepler::NUMBER, U"-1.5J-12.5"}}));

    CHECK_NOTHROW(run("¯1.5E1J12.5E¯1"));
    CHECK_THAT(run("¯1.5E1J12.5E¯1"), Outputs({{kepler::NUMBER, U"-1.5E1J12.5E-1"}}));

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

TEST_CASE_METHOD(TokenizerFixture, "numeric-literal", "[numeric-literal][lexer]") {
    CHECK_NOTHROW(run("1.5J12 1.5J12"));
    CHECK_THAT(run("1.5J12 1.5J12"),
               Outputs({
                   {kepler::NUMBER, U"1.5J12"},
                   {kepler::NUMBER, U"1.5J12"}
               }));

    CHECK_NOTHROW(run("1.5J12.5 1.5J12.5 1.5J12.5"));
    CHECK_THAT(run("1.5J12.5 1.5J12.5 1.5J12.5"),
               Outputs({
                   {kepler::NUMBER, U"1.5J12.5"},
                   {kepler::NUMBER, U"1.5J12.5"},
                   {kepler::NUMBER, U"1.5J12.5"},
               }));

    CHECK_NOTHROW(run("      1.5E1J12.5E1     1.5E1J12.5E1       1.5E1J12.5E1 "));
    CHECK_THAT(run("      1.5E1J12.5E1     1.5E1J12.5E1       1.5E1J12.5E1 "),
               Outputs({
                   {kepler::NUMBER, U"1.5E1J12.5E1"},
                   {kepler::NUMBER, U"1.5E1J12.5E1"},
                   {kepler::NUMBER, U"1.5E1J12.5E1"},
               }));

    CHECK_NOTHROW(run("     1.5J¯12 1.5J¯12 1.5J¯12"));
    CHECK_THAT(run("     1.5J¯12 1.5J¯12 1.5J¯12"),
               Outputs({
                   {kepler::NUMBER, U"1.5J-12"},
                   {kepler::NUMBER, U"1.5J-12"},
                   {kepler::NUMBER, U"1.5J-12"},
               }));

    CHECK_NOTHROW(run("   ¯1.5J¯12.5    "));
    CHECK_THAT(run("   ¯1.5J¯12.5    "), Outputs({{kepler::NUMBER, U"-1.5J-12.5"}}));

    CHECK_NOTHROW(run("¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 "));
    CHECK_THAT(run("¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 ¯1.5E1J12.5E¯1 "),
               Outputs({
                   {kepler::NUMBER, U"-1.5E1J12.5E-1"},
                   {kepler::NUMBER, U"-1.5E1J12.5E-1"},
                   {kepler::NUMBER, U"-1.5E1J12.5E-1"},
                   {kepler::NUMBER, U"-1.5E1J12.5E-1"},
                   {kepler::NUMBER, U"-1.5E1J12.5E-1"},
                   {kepler::NUMBER, U"-1.5E1J12.5E-1"},
               }));
}


TEST_CASE_METHOD(TokenizerFixture, "literal-identifier", "[literal-identifier][lexer]") {
    CHECK_NOTHROW(run("a"));
    CHECK_THAT(run("a"), Outputs({{kepler::ID, U"a"}}));

    CHECK_NOTHROW(run("Q"));
    CHECK_THAT(run("Q"), Outputs({{kepler::ID, U"Q"}}));

    CHECK_NOTHROW(run("ab"));
    CHECK_THAT(run("ab"), Outputs({{kepler::ID, U"ab"}}));

    CHECK_NOTHROW(run("aQ"));
    CHECK_THAT(run("aQ"), Outputs({{kepler::ID, U"aQ"}}));

    CHECK_NOTHROW(run("Aq"));
    CHECK_THAT(run("Aq"), Outputs({{kepler::ID, U"Aq"}}));

    CHECK_NOTHROW(run("AqW"));
    CHECK_THAT(run("AqW"), Outputs({{kepler::ID, U"AqW"}}));

    CHECK_NOTHROW(run("a1"));
    CHECK_THAT(run("a1"), Outputs({{kepler::ID, U"a1"}}));

    CHECK_NOTHROW(run("a1a"));
    CHECK_THAT(run("a1a"), Outputs({{kepler::ID, U"a1a"}}));
}

TEST_CASE_METHOD(TokenizerFixture, "line", "[line][lexer]") {
    CHECK_NOTHROW(run("a"));
    CHECK_THAT(run("a"), Outputs({{kepler::ID, U"a"}}));

    CHECK_NOTHROW(run("ab qt"));
    CHECK_THAT(run("ab qt"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::ID, U"qt"},
               }));

    CHECK_NOTHROW(run("ab 1 2 3"));
    CHECK_THAT(run("ab 1 2 3"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
               }));

    CHECK_NOTHROW(run("ab 1 2 3+123"));
    CHECK_THAT(run("ab 1 2 3+123"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("ab 1 2 3+123 ⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3+123 ⍝This is discarded"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("ab 1 2 3+123⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3+123⍝This is discarded"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("ab 1 2 3 + 123"));
    CHECK_THAT(run("ab 1 2 3 + 123"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("ab 1 2 3 + 123 ⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3 + 123 ⍝This is discarded"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("ab 1 2 3 + 123⍝This is discarded"));
    CHECK_THAT(run("ab 1 2 3 + 123⍝This is discarded"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("ab ◊ 1 2 3 + 123⍝This is discarded"));
    CHECK_THAT(run("ab ◊ 1 2 3 + 123⍝This is discarded"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::DIAMOND, U"◊"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("ab◊1 2 3 + 123⍝This is discarded"));
    CHECK_THAT(run("ab◊1 2 3 + 123⍝This is discarded"),
               Outputs({
                   {kepler::ID, U"ab"},
                   {kepler::DIAMOND, U"◊"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3"},
                   {kepler::PLUS, U"+"},
                   {kepler::NUMBER, U"123"},
               }));

    CHECK_NOTHROW(run("◊◊  ◊◊     1 2 3.5⍝This is discarded"));
    CHECK_THAT(run("◊◊  ◊◊     1 2 3.5⍝This is discarded"),
               Outputs({
                   {kepler::DIAMOND, U"◊"},
                   {kepler::DIAMOND, U"◊"},
                   {kepler::DIAMOND, U"◊"},
                   {kepler::DIAMOND, U"◊"},
                   {kepler::NUMBER, U"1"},
                   {kepler::NUMBER, U"2"},
                   {kepler::NUMBER, U"3.5"},
               }));
}

TEST_CASE_METHOD(TokenizerFixture, "corner-cases", "[corner-cases][lexer]") {
    CHECK_THAT_THROWS(run("∂∂"), Throws(kepler::SyntaxError));
    CHECK_THAT(run(""), Outputs({}));
}