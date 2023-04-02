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

TEST_CASE_METHOD(fixture, "Inner product (.)", "[inner-product][operators]") {
    CHECK_THAT(run("4 2 1 +.× 1 0 1"), Prints("5"));
    CHECK_THAT(run("1 2 3 +.× 4 5 6"), Prints("32"));
    CHECK_THAT(run("3 3 ∧.= 3 3 3 3"), Throws(kepler::LengthError));
}

TEST_CASE_METHOD(fixture, "Power (⍣)", "[power][operators]") {
    run("f←{⍵+1}");

    CHECK_THAT(run("(f⍣3)0"), Prints("3"));
    CHECK_THAT(run("(f⍣0)0"), Prints("0"));
    CHECK_THAT(run("(f⍣0)102301"), Prints("102301"));
    CHECK_THAT(run("(f⍣0)102301"), Prints("102301"));
    CHECK_THAT(run("(f⍣102301)0"), Prints("102301"));
    CHECK_THAT(run("(f⍣'abc')4"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(fixture, "Outer product (.)", "[outer-product][operators]") {
    CHECK_THAT(run("4 2 1 ∘.× 1 0 1"), Prints("4 0 4\n"
                                              "2 0 2\n"
                                              "1 0 1"));
    CHECK_THAT(run("1 2 3 ∘.× 4 5 6"), Prints(" 4  5  6\n"
                                              " 8 10 12\n"
                                              "12 15 18"));
    CHECK_THAT(run("3 ∘.× 3 3 3 3"), Prints("9 9 9 9"));
    CHECK_THAT(run("3 3 3 3 ∘.× 3"), Prints("9 9 9 9"));
    CHECK_THAT(run("(3 3⍴⍳10) ∘.× (3 3⍴⍳10)"), Prints(" 1  2  3\n"
                                                      " 4  5  6\n"
                                                      " 7  8  9\n"
                                                      "\n"
                                                      " 2  4  6\n"
                                                      " 8 10 12\n"
                                                      "14 16 18\n"
                                                      "\n"
                                                      " 3  6  9\n"
                                                      "12 15 18\n"
                                                      "21 24 27\n"
                                                      "\n"
                                                      "\n"
                                                      " 4  8 12\n"
                                                      "16 20 24\n"
                                                      "28 32 36\n"
                                                      "\n"
                                                      " 5 10 15\n"
                                                      "20 25 30\n"
                                                      "35 40 45\n"
                                                      "\n"
                                                      " 6 12 18\n"
                                                      "24 30 36\n"
                                                      "42 48 54\n"
                                                      "\n"
                                                      "\n"
                                                      " 7 14 21\n"
                                                      "28 35 42\n"
                                                      "49 56 63\n"
                                                      "\n"
                                                      " 8 16 24\n"
                                                      "32 40 48\n"
                                                      "56 64 72\n"
                                                      "\n"
                                                      " 9 18 27\n"
                                                      "36 45 54\n"
                                                      "63 72 81"));
}