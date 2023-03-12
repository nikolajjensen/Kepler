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

TEST_CASE_METHOD(fixture, "numbers", "[numbers][datatypes]") {
    CHECK_THAT(run("0"), Prints("0"));
    CHECK_THAT(run("0000001"), Prints("1"));
    CHECK_THAT(run("0.000001"), Prints("0.000001"));
    CHECK_THAT(run("1000000"), Prints("1000000"));
    CHECK_THAT(run("11111111111111111"), Prints("1.111111111E16"));
    CHECK_THAT(run("(((1000000)))"), Prints("1000000"));

    CHECK_THAT(run("1E6"), Prints("1000000"));
    CHECK_THAT(run("1E10"), Prints("1E10"));
    CHECK_THAT(run("1E9"), Prints("1000000000"));
    CHECK_THAT(run("(((1.923E9)))"), Prints("1923000000"));

    CHECK_THAT(run("1E6J20"), Prints("1000000J20"));
    CHECK_THAT(run("1E10J10"), Prints("1E10J10"));
    CHECK_THAT(run("1E9J¯2"), Prints("1000000000J¯2"));
    CHECK_THAT(run("(((((((((1.923J2.3E9)))))))))"), Prints("1.923J2300000000"));

    // Many more corner cases (and negative tests) are in test_lexer.cpp.
}

TEST_CASE_METHOD(fixture, "arrays", "[arrays][datatypes]") {
    CHECK_THAT(run("1 2 3"), Prints("1 2 3"));
    CHECK_THAT(run("1 ¯2 3"), Prints("1 ¯2 3"));
    CHECK_THAT(run("1 (¯2 3)"), Prints("┌─┬────┐\n"
                                       "│1│¯2 3│\n"
                                       "└─┴────┘"));
    CHECK_THAT(run("1 (¯2J2E¯32 3)"), Prints("┌─┬──────────┐\n"
                                             "│1│¯2J2E¯32 3│\n"
                                             "└─┴──────────┘"));
    CHECK_THAT(run("1 (2 (3 4 (5 6)))"), Prints("┌─┬─────────────┐\n"
                                                "│1│┌─┬─────────┐│\n"
                                                "│ ││2│┌─┬─┬───┐││\n"
                                                "│ ││ ││3│4│5 6│││\n"
                                                "│ ││ │└─┴─┴───┘││\n"
                                                "│ │└─┴─────────┘│\n"
                                                "└─┴─────────────┘"));
    CHECK_THAT(run("1 (2 (3 4E¯9 (5J2 6) 3) 11111111111111111)"), Prints("┌─┬───────────────────────────────────┐\n"
                                                                         "│1│┌─┬────────────────┬──────────────┐│\n"
                                                                         "│ ││2│┌─┬────┬─────┬─┐│1.111111111E16││\n"
                                                                         "│ ││ ││3│4E¯9│5J2 6│3││              ││\n"
                                                                         "│ ││ │└─┴────┴─────┴─┘│              ││\n"
                                                                         "│ │└─┴────────────────┴──────────────┘│\n"
                                                                         "└─┴───────────────────────────────────┘"));
}