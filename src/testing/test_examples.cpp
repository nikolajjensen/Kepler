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

TEST_CASE_METHOD(fixture, "corner-cases-input", "[corner-cases]") {
    CHECK_THAT(run(""), Prints(""));
    CHECK_THAT(run("      "), Prints(""));
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
    CHECK_THAT(run("Var"), Prints("Hello, World!"));

    CHECK_THAT(run("Var←5E¯10 2E1 3J¯2.2"), Prints(""));
    CHECK_THAT(run("Var"), Prints("5E¯10 20 3J¯2.2"));

    CHECK_THAT(run("+Var"), Prints("5E¯10 20 3J2.2"));
    CHECK_THAT(run("Var + Var"), Prints("1E¯9 40 6J¯4.4"));
}
