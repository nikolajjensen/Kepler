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
#include "core/token_class.h"
#include "core/datatypes.h"
#include "string_maker.h"
#include "core/error_type.h"
#include "macros.h"

TEST_CASE_METHOD(fixture, "conjugate (+)", "[conjugate][scalar][func]") {
    CHECK_THAT(run("+2 "), Prints("2"));
    CHECK_THAT(run("+2E2"), Prints("200"));
    CHECK_THAT(run("+2E¯2"), Prints("0.02"));
    CHECK_THAT(run("+2J¯2"), Prints("2J2"));
    CHECK_THAT(run("+2J2"), Prints("2J¯2"));
    CHECK_THAT(run("+2 3 5"), Prints("2 3 5"));
    CHECK_THAT(run("+2 3 5 "), Prints("2 3 5"));
    CHECK_THAT(run(" +2 3 5 "), Prints("2 3 5"));
    CHECK_THAT(run("+ 3 ¯4 0 0.5 3J4 ¯3J4 3J¯4"), Prints("3 ¯4 0 0.5 3J¯4 ¯3J¯4 3J4"));
}

TEST_CASE_METHOD(fixture, "negative (-)", "[negative][scalar][func]") {
    CHECK_THAT(run("-2"), Prints("¯2"));
    CHECK_THAT(run("-2E2"), Prints("¯200"));
    CHECK_THAT(run("-2J2"), Prints("¯2J¯2"));
    CHECK_THAT(run("-2J¯2"), Prints("¯2J2"));
    CHECK_THAT(run("- 7 0 ¯7"), Prints("¯7 0 7"));
}

TEST_CASE_METHOD(fixture, "direction (×)", "[direction][scalar][func]") {
    CHECK_THAT(run("×2"), Prints("1"));
    CHECK_THAT(run("×0"), Prints("0"));
    CHECK_THAT(run("×2E2"), Prints("1"));
    CHECK_THAT(run("×3J4"), Prints("0.6J0.8"));
    CHECK_THAT(run("×1 ¯.5 .33 0 ¯1E¯20"), Prints("1 ¯1 1 0 ¯1"));
    CHECK_THAT(run("×3J4 3J¯4 ¯3J4 ¯3J¯4"), Prints("0.6J0.8 0.6J¯0.8 ¯0.6J0.8 ¯0.6J¯0.8"));
}

TEST_CASE_METHOD(fixture, "reciprocal (÷)", "[reciprocal][scalar][func]") {
    CHECK_THAT(run("÷5"), Prints("0.2"));
    CHECK_THAT(run("÷1"), Prints("1"));
    CHECK_THAT(run("÷0.1"), Prints("10"));
    CHECK_THAT(run("÷¯.25 .5 1 2 ¯4"), Prints("¯4 2 1 0.5 ¯0.25"));
    CHECK_THAT(run("÷0"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(fixture, "floor (⌊)", "[floor][scalar][func]") {
    CHECK_THAT(run("⌊¯3.1416 3.1416 .99999999999 5E20 ¯0.5E¯10"), Prints("¯4 3 1 5E20 0"));
    //CHECK_THAT(run("⌊0.3J0.6 0.6J0.8 0.8J0.6 0.6J0.3 0.8J0.2 0.5J0.5"), Prints("0 0J1 1 0 1 1", session));
}

TEST_CASE_METHOD(fixture, "plus (+)", "[plus][scalar][func]") {
    CHECK_THAT(run("1+2"), Prints("3"));
    CHECK_THAT(run("100+2"), Prints("102"));
    CHECK_THAT(run("23+2"), Prints("25"));
    CHECK_THAT(run("1E1+2J2"), Prints("12J2"));
    CHECK_THAT(run("1J2+1J7"), Prints("2J9"));
}

TEST_CASE_METHOD(fixture, "divide (÷)", "[divide][scalar][func]") {
    CHECK_THAT(run("2÷5"), Prints("0.4"));
    CHECK_THAT(run("5÷5"), Prints("1"));
    CHECK_THAT(run("4÷2"), Prints("2"));
    CHECK_THAT(run("4.5÷2"), Prints("2.25"));
    CHECK_THAT(run("2÷0"), Throws(kepler::DomainError));
    CHECK_THAT(run("2.5÷0"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(fixture, "shape (⍴)", "[shape][scalar][func]") {
    CHECK_THAT(run("⍴1 2 3"), Prints("3"));
    CHECK_THAT(run("⍴1 2 3 4"), Prints("4"));
}

TEST_CASE_METHOD(fixture, "negative and conjugate", "[negative][conjugate][scalar][func]") {
    CHECK_THAT(run("-+2"), Prints("¯2"));
    CHECK_THAT(run("-+2E2"), Prints("¯200"));
    CHECK_THAT(run("-+2J2"), Prints("¯2J2"));
}

TEST_CASE_METHOD(fixture, "System var", "[sys][scalar][func]") {
    CHECK_THAT(run("⎕IO←1"), Prints(""));
    CHECK_THAT(run("⎕IO←0"), Prints(""));
    CHECK_THAT(run("⎕IO←2"), Throws(kepler::LimitError));
}

TEST_CASE_METHOD(fixture, "Index origin demo", "[sys][scalar][func]") {
    CHECK_THAT(run("⎕IO"), Prints("1"));

    CHECK_THAT(run("+/⍳5"), Prints("15"));
    CHECK_THAT(run("÷/⍳5"), Prints("1.875"));

    CHECK_THAT(run("⎕IO←0"), Prints(""));
    CHECK_THAT(run("⎕IO"), Prints("0"));

    CHECK_THAT(run("+/⍳5"), Prints("10"));
    CHECK_THAT(run("÷/⍳5"), Prints("0"));
}

TEST_CASE_METHOD(fixture, "Variable demo", "[sys][scalar][func]") {
    CHECK_THAT(run("Var←'Hello, World!'"), Prints(""));
    CHECK_THAT(run("Var"), Prints("H e l l o ,   W o r l d !"));

    CHECK_THAT(run("Var←5E¯10 2E1 3J¯2.2"), Prints(""));
    CHECK_THAT(run("Var"), Prints("5E¯10 20 3J¯2.2"));

    CHECK_THAT(run("+Var"), Prints("5E¯10 20 3J2.2"));
    CHECK_THAT(run("Var + Var"), Prints("1E¯9 40 6J¯4.4"));
}
