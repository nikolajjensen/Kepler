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

TEST_CASE_METHOD(fixture, "conjugate (+)", "[conjugate][scalar][func]") {
    CHECK_THAT(run("+2"), Outputs("2"));
    CHECK_THAT(run("+2E2"), Outputs("200"));
    CHECK_THAT(run("+2E¯2"), Outputs("0.02"));
    CHECK_THAT(run("+2J¯2"), Outputs("2J2"));
    CHECK_THAT(run("+2J2"), Outputs("2J¯2"));
}

TEST_CASE_METHOD(fixture, "negation (-)", "[negation][scalar][func]") {
    CHECK_THAT(run("-2"), Outputs("¯2"));
    CHECK_THAT(run("-2E2"), Outputs("¯200"));
    CHECK_THAT(run("-2J2"), Outputs("¯2J¯2"));
    CHECK_THAT(run("-2J¯2"), Outputs("¯2J2"));
}

TEST_CASE_METHOD(fixture, "direction (×)", "[multiply][scalar][func]") {
    CHECK_THAT(run("×2"), Outputs("1"));
    CHECK_THAT(run("×0"), Outputs("0"));
    CHECK_THAT(run("×2E2"), Outputs("1"));
    //CHECK_THAT(run("×2J2"), Outputs("0.7071067812J0.7071067812"));
}

TEST_CASE_METHOD(fixture, "negation and conjugate", "[negation][conjugate][scalar][func]") {
    CHECK_THAT(run("-+2"), Outputs("¯2"));
    CHECK_THAT(run("-+2E2"), Outputs("¯200"));
    CHECK_THAT(run("-+2J2"), Outputs("¯2J2"));
}