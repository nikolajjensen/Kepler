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
#include "fixture.h"
#include "matcher.h"
#include "core/token_class.h"
#include "core/datatypes.h"
#include "string_maker.h"
#include "core/error_type.h"
#include "macros.h"

TEST_CASE_METHOD(fixture, "System var", "[sys][scalar][func]") {
    CHECK_THAT(run("⎕IO←1"), Outputs("1"));
    CHECK_THAT(run("⎕IO←0"), Outputs("0"));
    CHECK_THAT_THROWS(run("⎕IO←2"), Throws(kepler::LimitError));
}

TEST_CASE_METHOD(fixture, "conjugate (+)", "[conjugate][scalar][func]") {
    CHECK_THAT(run("+2 "), Outputs("2"));
    CHECK_THAT(run("+2E2"), Outputs("200"));
    CHECK_THAT(run("+2E¯2"), Outputs("0.02"));
    CHECK_THAT(run("+2J¯2"), Outputs("2J2"));
    CHECK_THAT(run("+2J2"), Outputs("2J¯2"));
    CHECK_THAT(run("+2 3 5"), Outputs("2 3 5"));
    CHECK_THAT(run("+2 3 5 "), Outputs("2 3 5"));
    CHECK_THAT(run(" +2 3 5 "), Outputs("2 3 5"));
    CHECK_THAT(run("+ 3 ¯4 0 0.5 3J4 ¯3J4 3J¯4"), Outputs("3 ¯4 0 0.5 3J¯4 ¯3J¯4 3J4"));
}

TEST_CASE_METHOD(fixture, "negative (-)", "[negative][scalar][func]") {
    CHECK_THAT(run("-2"), Outputs("¯2"));
    CHECK_THAT(run("-2E2"), Outputs("¯200"));
    CHECK_THAT(run("-2J2"), Outputs("¯2J¯2"));
    CHECK_THAT(run("-2J¯2"), Outputs("¯2J2"));
    CHECK_THAT(run("- 7 0 ¯7"), Outputs("¯7 0 7"));
}

TEST_CASE_METHOD(fixture, "direction (×)", "[direction][scalar][func]") {
    CHECK_THAT(run("×2"), Outputs("1"));
    CHECK_THAT(run("×0"), Outputs("0"));
    CHECK_THAT(run("×2E2"), Outputs("1"));
    CHECK_THAT(run("×3J4"), Outputs("0.6J0.8"));
}

TEST_CASE_METHOD(fixture, "plus (+)", "[plus][scalar][func]") {
    CHECK_THAT(run("1+2"), Outputs("3"));
    CHECK_THAT(run("100+2"), Outputs("102"));
    CHECK_THAT(run("23+2"), Outputs("25"));
    CHECK_THAT(run("1E1+2J2"), Outputs("12J2"));
    CHECK_THAT(run("1J2+1J7"), Outputs("2J9"));
}

TEST_CASE_METHOD(fixture, "divide (÷)", "[divide][scalar][func]") {
    CHECK_THAT(run("2÷5"), Outputs("0.4"));
    CHECK_THAT_THROWS(run("2÷0"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(fixture, "shape (⍴)", "[shape][scalar][func]") {
    CHECK_THAT(run("⍴1 2 3"), Outputs("3"));
    CHECK_THAT(run("⍴1 2 3 4"), Outputs("4"));
}

TEST_CASE_METHOD(fixture, "negative and conjugate", "[negative][conjugate][scalar][func]") {
    CHECK_THAT(run("-+2"), Outputs("¯2"));
    CHECK_THAT(run("-+2E2"), Outputs("¯200"));
    CHECK_THAT(run("-+2J2"), Outputs("¯2J2"));
}