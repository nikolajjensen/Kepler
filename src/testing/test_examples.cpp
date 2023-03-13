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
#include "testing/fixtures/file_fixture.h"

TEST_CASE_METHOD(file_fixture, "files", "[files]") {
    CHECK_THAT(run("../src/testing/files/degrees.kpl"), Prints("20"));
    CHECK_THAT(run("../src/testing/files/error_degrees.kpl"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("../src/testing/files/non_existent_file.kpl"), Throws(kepler::FileError));

    //CHECK_THAT(run("../src/testing/files/fib.kpl"), Prints(""));
    //CHECK_THAT(run("../src/testing/files/life.kpl"), Prints(""));
}

TEST_CASE_METHOD(fixture, "corner-cases-input", "[corner-cases]") {
    CHECK_THAT(run(""), Prints(""));
    CHECK_THAT(run("      "), Prints(""));
}

TEST_CASE_METHOD(fixture, "System variables", "[system-variables]") {
    CHECK_THAT(run("⎕IO←1"), Prints(""));
    CHECK_THAT(run("⎕IO←0"), Prints(""));
    CHECK_THAT(run("⎕IO←2"), Throws(kepler::LimitError));
    CHECK_THAT(run("⎕IO←¯2"), Throws(kepler::LimitError));
    CHECK_THAT(run("⎕IO←1.2"), Throws(kepler::LimitError));
    CHECK_THAT(run("⎕IO←'hello'"), Throws(kepler::DomainError));

    CHECK_THAT(run("⎕PP←1"), Prints(""));
    CHECK_THAT(run("⎕PP←30"), Prints(""));
    CHECK_THAT(run("⎕PP←31"), Throws(kepler::LimitError));
    CHECK_THAT(run("⎕PP←0"), Throws(kepler::LimitError));
    CHECK_THAT(run("⎕PP←¯3"), Throws(kepler::LimitError));
    CHECK_THAT(run("⎕PP←¯100"), Throws(kepler::LimitError));
}

TEST_CASE_METHOD(fixture, "Index origin", "[index-origin]") {
    CHECK_THAT(run("⎕IO"), Prints("1"));

    CHECK_THAT(run("+/⍳5"), Prints("15"));
    CHECK_THAT(run("÷/⍳5"), Prints("1.875"));

    CHECK_THAT(run("⎕IO←0"), Prints(""));
    CHECK_THAT(run("⎕IO"), Prints("0"));

    CHECK_THAT(run("+/⍳5"), Prints("10"));
    CHECK_THAT(run("÷/⍳5"), Prints("0"));
}

TEST_CASE_METHOD(fixture, "Print precision", "[print-precision]") {
    CHECK_THAT(run("⎕PP"), Prints("10"));

    CHECK_THAT(run("10÷3"), Prints("3.333333333"));

    CHECK_THAT(run("⎕PP←3"), Prints(""));
    CHECK_THAT(run("⎕PP"), Prints("3"));

    CHECK_THAT(run("10÷3"), Prints("3.33"));
}

TEST_CASE_METHOD(fixture, "Variables", "[variables]") {
    CHECK_THAT(run("Var"), Throws(kepler::DefinitionError));
    CHECK_THAT(run("Var←'Hello, World!'"), Prints(""));
    CHECK_THAT(run("Var"), Prints("Hello, World!"));

    CHECK_THAT(run("Var←5E¯10 2E1 3J¯2.2"), Prints(""));
    CHECK_THAT(run("Var"), Prints("5E¯10 20 3J¯2.2"));

    CHECK_THAT(run("+Var"), Prints("5E¯10 20 3J2.2"));
    CHECK_THAT(run("Var + Var"), Prints("1E¯9 40 6J¯4.4"));
}

TEST_CASE_METHOD(fixture, "user-defined-functions", "[user-defined-functions]") {
    CHECK_THAT(run("Fn"), Throws(kepler::DefinitionError));
    CHECK_THAT(run("Fn←{q←{2-⍵} ◊ 1 - q⍵}"), Prints(""));
    CHECK_THAT(run("Fn 2"), Prints("1"));

    CHECK_THAT(run("tf"), Throws(kepler::DefinitionError));
    CHECK_THAT(run("var"), Throws(kepler::DefinitionError));
    CHECK_THAT(run("tf←{q←{2-⍵} ◊ var - q⍵}"), Prints(""));
    CHECK_THAT(run("tf 2"), Throws(kepler::DefinitionError));
    CHECK_THAT(run("var←10"), Prints(""));
    CHECK_THAT(run("tf 2"), Prints("10"));

    CHECK_THAT(run("f"), Throws(kepler::DefinitionError));
    CHECK_THAT(run("outer"), Throws(kepler::DefinitionError));
    CHECK_THAT(run("outer←10"), Prints(""));
    CHECK_THAT(run("outer"), Prints("10"));
    CHECK_THAT(run("f←{outer←⍵+⍺}"), Prints(""));
    CHECK_THAT(run("1 f 3"), Prints(""));
    CHECK_THAT(run("outer"), Prints("4"));


    CHECK_THAT(run("outer←'abc'"), Prints(""));
    CHECK_THAT(run("outer"), Prints("abc"));
    CHECK_THAT(run("f←{outer←{⍺×⍵}}"), Prints(""));
    CHECK_THAT(run("1 f 2"), Prints(""));
    CHECK_THAT(run("10 outer 2"), Prints("20"));


    CHECK_THAT(run("⎕IO"), Prints("1"));
    CHECK_THAT(run("k←{⎕IO←⍵+⍺}"), Prints(""));
    CHECK_THAT(run("0 k 0"), Prints(""));
    CHECK_THAT(run("⎕IO"), Prints("0"));
}
