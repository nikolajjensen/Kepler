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
#include "testing/fixtures/fixture.h"
#include "matcher.h"
#include "core/error_type.h"

TEST_CASE_METHOD(fixture, "commute (⍨)", "[commute][operators]") {
    CHECK_THAT(run("+⍨2"), Prints("4"));
    CHECK_THAT(run("2+⍨1"), Prints("3"));
    CHECK_THAT(run("2÷⍨1"), Prints("0.5"));
    CHECK_THAT(run("2÷1"), Prints("2"));

    CHECK_THAT(run("+⍨1 2 3"), Prints("2 4 6"));
    CHECK_THAT(run("1 2 3+⍨4 5 6"), Prints("5 7 9"));
    CHECK_THAT(run("1 2 3÷⍨4 5 6"), Prints("4 2.5 2"));
    CHECK_THAT(run("1 2 3÷4 5 6"), Prints("0.25 0.4 0.5"));
}

TEST_CASE_METHOD(fixture, "slash (/)", "[slash][operators]") {
    CHECK_THAT(run("+/2"), Prints("2"));
    CHECK_THAT(run("+/1 3 4"), Prints("8"));
    CHECK_THAT(run("-/⍳10"), Prints("¯5"));
    CHECK_THAT(run("1 2 3 +/ 1 2 3"), Throws(kepler::NotImplemented));
}

TEST_CASE_METHOD(fixture, "diaeresis (¨)", "[diaeresis][operators]") {
    CHECK_THAT(run("{2+⍵}¨2 3 4"), Prints("4 5 6"));
    CHECK_THAT(run("2 3 4{2+⍵}¨2"), Prints("4 4 4"));
    CHECK_THAT(run("2 3 4{2+⍺}¨2"), Prints("4 5 6"));
    CHECK_THAT(run("1 2 3{⍺+⍵}¨2 3 4"), Prints("3 5 7"));
    CHECK_THAT(run("1 2 3{0.5+⍵}¨2 3 4"), Prints("2.5 3.5 4.5"));
    CHECK_THAT(run("1 3 +¨ 1 2 3"), Throws(kepler::LengthError));

    CHECK_THAT(run("2 3⍴1 +¨ 1 2 3"), Prints("2 3 4\n"
                                             "2 3 4"));

    CHECK_THAT(run("2 3⍴1 +¨ 5 2 3⍴1"), Prints("2 2 2\n"
                                               "2 2 2"));

    CHECK_THAT(run("3 4 2+¨5 2 3⍴1"), Throws(kepler::RankError));
}

TEST_CASE_METHOD(fixture, "jot (∘)", "[jot][operators]") {
    CHECK_THAT(run("2-∘×2"), Prints("1"));
    CHECK_THAT(run("(2-∘×2)=(2-(×2))"), Prints("1"));
    CHECK_THAT(run("(2E10-∘-2J23)=(2E10-(-2J23))"), Prints("1"));

    CHECK_THAT(run("-∘×2"), Prints("¯1"));
    CHECK_THAT(run("-∘×2J12"), Prints("¯0.1643989873J¯0.9863939238"));
}

TEST_CASE_METHOD(fixture, "atop (⍤)", "[atop][operators]") {
    CHECK_THAT(run("2-⍤×2"), Prints("¯4"));
    CHECK_THAT(run("(2-⍤×2)=(-(2×2))"), Prints("1"));
    CHECK_THAT(run("(2E10-⍤-2J23)=(-(2E10-2J23))"), Prints("1"));

    CHECK_THAT(run("-⍤×2"), Prints("¯1"));
    CHECK_THAT(run("-⍤×2J12"), Prints("¯0.1643989873J¯0.9863939238"));
}

TEST_CASE_METHOD(fixture, "over (⍥)", "[over][operators]") {
    CHECK_THAT(run("2-⍥×2"), Prints("0"));
    CHECK_THAT(run("(2-⍥×2)=((×2)-(×2))"), Prints("1"));
    CHECK_THAT(run("(2E10-⍥-2J23)=((-2E10)-(-2J23))"), Prints("1"));

    CHECK_THAT(run("-⍥×2"), Prints("¯1"));
    CHECK_THAT(run("-⍥×2J12"), Prints("¯0.1643989873J¯0.9863939238"));
}