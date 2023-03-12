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

TEST_CASE_METHOD(fixture, "plus (+)", "[plus][function]") {
    CHECK_THAT(run("+2 "), Prints("2"));
    CHECK_THAT(run("+2E2"), Prints("200"));
    CHECK_THAT(run("+2E¯2"), Prints("0.02"));
    CHECK_THAT(run("+2J¯2"), Prints("2J2"));
    CHECK_THAT(run("+2J2"), Prints("2J¯2"));
    CHECK_THAT(run("+2 3 5"), Prints("2 3 5"));
    CHECK_THAT(run("+2 3 5 "), Prints("2 3 5"));
    CHECK_THAT(run(" +2 3 5 "), Prints("2 3 5"));
    CHECK_THAT(run("+ 3 ¯4 0 0.5 3J4 ¯3J4 3J¯4"), Prints("3 ¯4 0 0.5 3J¯4 ¯3J¯4 3J4"));

    CHECK_THAT(run("+0"), Prints("0"));
    CHECK_THAT(run("+¯2.43"), Prints("¯2.43"));
    CHECK_THAT(run("+0J1"), Prints("0J¯1"));
    CHECK_THAT(run("+1.3J¯3.8"), Prints("1.3J3.8"));
    CHECK_THAT(run("+ 3 ¯1.3 0J1 2.3J¯3.3"), Prints("3 ¯1.3 0J¯1 2.3J3.3"));
    CHECK_THAT(run("+ 1J1 2J¯1 (10 1J¯0.333) (1J6 92.1 (0J¯0.2 0.1J0.1))"),
               Prints("┌────┬───┬──────────┬──────────────────────────┐\n"
                      "│1J¯1│2J1│10 1J0.333│┌────┬────┬──────────────┐│\n"
                      "│    │   │          ││1J¯6│92.1│0J0.2 0.1J¯0.1││\n"
                      "│    │   │          │└────┴────┴──────────────┘│\n"
                      "└────┴───┴──────────┴──────────────────────────┘"));

    CHECK_THAT(run("0+0"), Prints("0"));
    CHECK_THAT(run("¯0.13 + 0.13"), Prints("0"));
    CHECK_THAT(run("¯3J1 + 1"), Prints("¯2J1"));
    CHECK_THAT(run("¯1J0.5 + 3J5"), Prints("2J5.5"));
    CHECK_THAT(run("1 2 3 + 4 5 6"), Prints("5 7 9"));
    CHECK_THAT(run("0 7.2 ¯0.3 0J1 ¯3J0.5 + 0 5 0.6 0.001 3J7"), Prints("0 12.2 0.3 0.001J1 0J7.5"));
    CHECK_THAT(run("10 + 1 2 3 4 5 6"), Prints("11 12 13 14 15 16"));
    CHECK_THAT(run("2 ¯3 4 ¯5 ¯1 + 0.212"), Prints("2.212 ¯2.788 4.212 ¯4.788 ¯0.788"));
    CHECK_THAT(run("0 (1 2.1) ¯0.1 + (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"),
               Prints("┌─────────┬──────────────────┬────────────────────────┐\n"
                      "│1 2.1 3 4│┌───┬────────────┐│┌─────┬────────────────┐│\n"
                      "│         ││1.7│4.1J12 4.1J3│││532.9│┌───┬──────────┐││\n"
                      "│         │└───┴────────────┘││     ││6.9│6.9 9.9J32│││\n"
                      "│         │                  ││     │└───┴──────────┘││\n"
                      "│         │                  │└─────┴────────────────┘│\n"
                      "└─────────┴──────────────────┴────────────────────────┘"));

    CHECK_THAT(run("0 (1 2.1 3) ¯0.1 + (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"), Throws(kepler::LengthError));

    CHECK_THAT(run("1+2"), Prints("3"));
    CHECK_THAT(run("100+2"), Prints("102"));
    CHECK_THAT(run("23+2"), Prints("25"));
    CHECK_THAT(run("1E1+2J2"), Prints("12J2"));
    CHECK_THAT(run("1J2+1J7"), Prints("2J9"));
    CHECK_THAT(run(" 1J2     + 1J7 "), Prints("2J9"));
    CHECK_THAT(run(" 1J2 2    + 1J7 1"), Prints("2J9 3"));
    CHECK_THAT(run("1J2 2 + 1J7"), Prints("2J9 3J7"));
    CHECK_THAT(run("1J2 + 1J7 2"), Prints("2J9 3J2"));

    CHECK_THAT(run("¯2 ¯1 0 + ¯2 ¯1 0"), Prints("¯4 ¯2 0"));

    CHECK_THAT(run("1J2 2 + 1J7 2 3"), Throws(kepler::LengthError));
    CHECK_THAT(run("1J2 2 3 4 + 1J7 2 3"), Throws(kepler::LengthError));

    CHECK_THAT(run("1+2+2"), Prints("5"));
    CHECK_THAT(run("(1+2)+2"), Prints("5"));
    CHECK_THAT(run("(1+(2+2)"), Prints("5"));
}

TEST_CASE_METHOD(fixture, "minus (-)", "[minus][scalar][func]") {
    CHECK_THAT(run("-2"), Prints("¯2"));
    CHECK_THAT(run("-2E2"), Prints("¯200"));
    CHECK_THAT(run("-2J2"), Prints("¯2J¯2"));
    CHECK_THAT(run("-2J¯2"), Prints("¯2J2"));
    CHECK_THAT(run("- 7 0 ¯7"), Prints("¯7 0 7"));
    CHECK_THAT(run("-2 3 5"), Prints("¯2 ¯3 ¯5"));
    CHECK_THAT(run("-2 3 5 "), Prints("¯2 ¯3 ¯5"));
    CHECK_THAT(run(" -2 3 5 "), Prints("¯2 ¯3 ¯5"));
    CHECK_THAT(run("- 3 ¯4 0 0.5 3J4 ¯3J4 3J¯4"), Prints("¯3 4 0 ¯0.5 ¯3J¯4 3J¯4 ¯3J4"));

    CHECK_THAT(run("-0"), Prints("0"));
    CHECK_THAT(run("-¯2.43"), Prints("2.43"));
    CHECK_THAT(run("-0J1"), Prints("0J¯1"));
    CHECK_THAT(run("-1.3J¯3.8"), Prints("¯1.3J3.8"));
    CHECK_THAT(run("- 3 ¯1.3 0J1 2.3J¯3.3"), Prints("¯3 1.3 0J¯1 ¯2.3J3.3"));
    CHECK_THAT(run("- 1J1 2J¯1 (10 1J¯0.333) (1J6 92.1 (0J¯0.2 0.1J0.1))"),
               Prints("┌─────┬────┬────────────┬─────────────────────────────┐\n"
                      "│¯1J¯1│¯2J1│¯10 ¯1J0.333│┌─────┬─────┬───────────────┐│\n"
                      "│     │    │            ││¯1J¯6│¯92.1│0J0.2 ¯0.1J¯0.1││\n"
                      "│     │    │            │└─────┴─────┴───────────────┘│\n"
                      "└─────┴────┴────────────┴─────────────────────────────┘"));

    CHECK_THAT(run("0-0"), Prints("0"));
    CHECK_THAT(run("¯0.13 - 0.13"), Prints("¯0.26"));
    CHECK_THAT(run("¯3J1 - 1"), Prints("¯4J1"));
    CHECK_THAT(run("¯1J0.5 - 3J5"), Prints("¯4J¯4.5"));
    CHECK_THAT(run("1 2 3 - 4 5 6"), Prints("¯3 ¯3 ¯3"));
    CHECK_THAT(run("0 7.2 ¯0.3 0J1 ¯3J0.5 - 0 5 0.6 0.001 3J7"), Prints("0 2.2 ¯0.9 ¯0.001J1 ¯6J¯6.5"));
    CHECK_THAT(run("10 - 1 2 3 4 5 6"), Prints("9 8 7 6 5 4"));
    CHECK_THAT(run("2 ¯3 4 ¯5 ¯1 - 0.212"), Prints("1.788 ¯3.212 3.788 ¯5.212 ¯1.212"));
    CHECK_THAT(run("0 (1 2.1) ¯0.1 - (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"),
               Prints("┌─────────────┬────────────────────┬──────────────────────────────┐\n"
                      "│¯1 ¯2.1 ¯3 ¯4│┌───┬──────────────┐│┌──────┬─────────────────────┐│\n"
                      "│             ││0.3│0.1J¯12 0.1J¯3│││¯533.1│┌────┬──────────────┐││\n"
                      "│             │└───┴──────────────┘││      ││¯7.1│¯7.1 ¯10.1J¯32│││\n"
                      "│             │                    ││      │└────┴──────────────┘││\n"
                      "│             │                    │└──────┴─────────────────────┘│\n"
                      "└─────────────┴────────────────────┴──────────────────────────────┘"));

    CHECK_THAT(run("0 (1 2.1 3) ¯0.1 - (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"), Throws(kepler::LengthError));

    CHECK_THAT(run("1-2"), Prints("¯1"));
    CHECK_THAT(run("100-2"), Prints("98"));
    CHECK_THAT(run("23-2"), Prints("21"));
    CHECK_THAT(run("1E1-2J2"), Prints("8J¯2"));
    CHECK_THAT(run("1J2-1J7"), Prints("0J¯5"));
    CHECK_THAT(run(" 1J2     - 1J7 "), Prints("0J¯5"));
    CHECK_THAT(run(" 1J2 2    - 1J7 1"), Prints("0J¯5 1"));
    CHECK_THAT(run("1J2 2 - 1J7"), Prints("0J¯5 1J¯7"));
    CHECK_THAT(run("1J2 - 1J7 2"), Prints("0J¯5 ¯1J2"));

    CHECK_THAT(run("¯2 ¯1 0 - ¯2 ¯1 0"), Prints("0 0 0"));

    CHECK_THAT(run("1J2 2 - 1J7 2 3"), Throws(kepler::LengthError));
    CHECK_THAT(run("1J2 2 3 4 - 1J7 2 3"), Throws(kepler::LengthError));

    CHECK_THAT(run("1-2-2"), Prints("1"));
    CHECK_THAT(run("(1-2)-2"), Prints("¯3"));
    CHECK_THAT(run("(1-(2-2)"), Prints("1"));
}

TEST_CASE_METHOD(fixture, "multiply (×)", "[multiply][function]") {
    CHECK_THAT(run("×2"), Prints("1"));
    CHECK_THAT(run("×0"), Prints("0"));
    CHECK_THAT(run("×2E2"), Prints("1"));
    CHECK_THAT(run("×3J4"), Prints("0.6J0.8"));
    CHECK_THAT(run("×1 ¯.5 .33 0 ¯1E¯20"), Prints("1 ¯1 1 0 ¯1"));
    CHECK_THAT(run("×3J4 3J¯4 ¯3J4 ¯3J¯4"), Prints("0.6J0.8 0.6J¯0.8 ¯0.6J0.8 ¯0.6J¯0.8"));

    CHECK_THAT(run("×2J2"), Prints("0.7071067812J0.7071067812"));
    CHECK_THAT(run("×2J¯2"), Prints("0.7071067812J¯0.7071067812"));
    CHECK_THAT(run("× 7 0 ¯7"), Prints("1 0 ¯1"));
    CHECK_THAT(run("×2 3 5"), Prints("1 1 1"));
    CHECK_THAT(run("×2 3 5 "), Prints("1 1 1"));
    CHECK_THAT(run(" ×2 3 5 "), Prints("1 1 1"));
    CHECK_THAT(run("× 3 ¯4 0 0.5 3J4 ¯3J4 3J¯4"), Prints("1 ¯1 0 1 0.6J0.8 ¯0.6J0.8 0.6J¯0.8"));

    CHECK_THAT(run("×¯2.43"), Prints("¯1"));
    CHECK_THAT(run("×0J1"), Prints("0J1"));
    CHECK_THAT(run("×1.3J¯3.8"), Prints("0.3236876791J¯0.946163985"));
    CHECK_THAT(run("× 3 ¯1.3 0J1 2.3J¯3.3"), Prints("1 ¯1 0J1 0.5717926617J¯0.8203981668"));
    CHECK_THAT(run("× 1J1 2J¯1 (10 1J¯0.333) (1J6 92.1 (0J¯0.2 0.1J0.1))"),
               Prints("┌─────────────────────────┬─────────────────────────┬────────────────────────────┬────────────────────────────────────────────────────────────┐\n"
                      "│0.7071067812J0.7071067812│0.894427191J¯0.4472135955│1 0.9487781332J¯0.3159431183│┌─────────────────────────┬─┬──────────────────────────────┐│\n"
                      "│                         │                         │                            ││0.1643989873J0.9863939238│1│0J¯1 0.7071067812J0.7071067812││\n"
                      "│                         │                         │                            │└─────────────────────────┴─┴──────────────────────────────┘│\n"
                      "└─────────────────────────┴─────────────────────────┴────────────────────────────┴────────────────────────────────────────────────────────────┘"));

    CHECK_THAT(run("0×0"), Prints("0"));
    CHECK_THAT(run("1×0"), Prints("0"));
    CHECK_THAT(run("0×1"), Prints("0"));
    CHECK_THAT(run("¯0.13 × 0.13"), Prints("¯0.0169"));
    CHECK_THAT(run("¯3J1 × 1"), Prints("¯3J1"));
    CHECK_THAT(run("¯1J0.5 × 3J5"), Prints("¯5.5J¯3.5"));
    CHECK_THAT(run("1 2 3 × 4 5 6"), Prints("4 10 18"));
    CHECK_THAT(run("0 7.2 ¯0.3 0J1 ¯3J0.5 × 0 5 0.6 0.001 3J7"), Prints("0 36 ¯0.18 0J0.001 ¯12.5J¯19.5"));
    CHECK_THAT(run("10 × 1 2 3 4 5 6"), Prints("10 20 30 40 50 60"));
    CHECK_THAT(run("2 ¯3 4 ¯5 ¯1 × 0.212"), Prints("0.424 ¯0.636 0.848 ¯1.06 ¯0.212"));
    CHECK_THAT(run("0 (1 2.1) ¯0.1 × (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"),
               Prints("┌───────┬──────────────────────┬───────────────────────────┐\n"
                      "│0 0 0 0│┌───┬────────────────┐│┌─────┬───────────────────┐│\n"
                      "│       ││0.7│4.2J25.2 4.2J6.3│││¯53.3│┌────┬────────────┐││\n"
                      "│       │└───┴────────────────┘││     ││¯0.7│¯0.7 ¯1J¯3.2│││\n"
                      "│       │                      ││     │└────┴────────────┘││\n"
                      "│       │                      │└─────┴───────────────────┘│\n"
                      "└───────┴──────────────────────┴───────────────────────────┘"));

    CHECK_THAT(run("0 (1 2.1 3) ¯0.1 × (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"), Throws(kepler::LengthError));

    CHECK_THAT(run("28 1 0 1 132 0J1 01J1 0J1 3J4 × 0 0J1 0 1 1J¯3.3 12 0J¯1 3J5 45.3J¯21"), Prints("0 0J1 0 1 132J¯435.6 0J12 1J¯1 ¯5J3 219.9J118.2"));
    CHECK_THAT(run("1 × 0 0J1 0 1 1J¯3.3 12 0J¯1 3J5 45.3J¯21"), Prints("0 0J1 0 1 1J¯3.3 12 0J¯1 3J5 45.3J¯21"));
    CHECK_THAT(run("0 0J1 0 1 1J¯3.3 12 0J¯1 3J5 45.3J¯21 × 2"), Prints("0 0J2 0 2 2J¯6.6 24 0J¯2 6J10 90.6J¯42"));

    CHECK_THAT(run("1×2"), Prints("2"));
    CHECK_THAT(run("100×2"), Prints("200"));
    CHECK_THAT(run("23×2"), Prints("46"));
    CHECK_THAT(run("1E1×2J2"), Prints("20J20"));
    CHECK_THAT(run("1J2×1J7"), Prints("¯13J9"));
    CHECK_THAT(run(" 1J2     × 1J7 "), Prints("¯13J9"));
    CHECK_THAT(run(" 1J2 2    × 1J7 1"), Prints("¯13J9 2"));
    CHECK_THAT(run("1J2 2 × 1J7"), Prints("¯13J9 2J14"));
    CHECK_THAT(run("1J2 × 1J7 2"), Prints("¯13J9 2J4"));

    CHECK_THAT(run("¯2 ¯1 0 × ¯2 ¯1 0"), Prints("4 1 0"));

    CHECK_THAT(run("1J2 2 × 1J7 2 3"), Throws(kepler::LengthError));
    CHECK_THAT(run("1J2 2 3 4 × 1J7 2 3"), Throws(kepler::LengthError));

    CHECK_THAT(run("1×2×2"), Prints("4"));
    CHECK_THAT(run("(1×2)×2"), Prints("4"));
    CHECK_THAT(run("(1×(2×2)"), Prints("4"));
}

TEST_CASE_METHOD(fixture, "divide (÷)", "[divide][function]") {
    CHECK_THAT(run("÷2"), Prints("0.5"));
    CHECK_THAT(run("÷2E2"), Prints("0.005"));
    CHECK_THAT(run("÷3J4"), Prints("0.12J¯0.16"));
    CHECK_THAT(run("÷1 ¯.5 .33 0 ¯1E¯20"), Throws(kepler::DomainError));
    CHECK_THAT(run("÷3J4 3J¯4 ¯3J4 ¯3J¯4"), Prints("0.12J¯0.16 0.12J0.16 ¯0.12J¯0.16 ¯0.12J0.16"));

    CHECK_THAT(run("÷2J2"), Prints("0.25J¯0.25"));
    CHECK_THAT(run("÷2J¯2"), Prints("0.25J0.25"));
    CHECK_THAT(run("÷ 7 0 ¯7"), Throws(kepler::DomainError));
    CHECK_THAT(run("÷2 3 5"), Prints("0.5 0.3333333333 0.2"));
    CHECK_THAT(run("÷2 3 5 "), Prints("0.5 0.3333333333 0.2"));
    CHECK_THAT(run(" ÷2 3 5 "), Prints("0.5 0.3333333333 0.2"));
    CHECK_THAT(run("÷ 3 ¯4 0 0.5 3J4 ¯3J4 3J¯4"), Throws(kepler::DomainError));

    CHECK_THAT(run("÷¯2.43"), Prints("¯0.4115226337"));
    CHECK_THAT(run("÷0J1"), Prints("0J¯1"));
    CHECK_THAT(run("÷1.3J¯3.8"), Prints("0.08059516429J0.2355858648"));
    CHECK_THAT(run("÷ 3 ¯1.3 0J1 2.3J¯3.3"), Prints("0.3333333333 ¯0.7692307692 0J¯1 0.1421508035J0.2039555006"));
    CHECK_THAT(run("÷ 1J1 2J¯1 (10 1J¯0.333) (1J6 92.1 (0J¯0.2 0.1J0.1))"),
               Prints("┌────────┬───────┬───────────────────────────┬───────────────────────────────────────────────────┐\n"
                      "│0.5J¯0.5│0.4J0.2│0.1 0.900179946J0.299759922│┌───────────────────────────┬────────────┬────────┐│\n"
                      "│        │       │                           ││0.02702702703J¯0.1621621622│0.0108577633│0J5 5J¯5││\n"
                      "│        │       │                           │└───────────────────────────┴────────────┴────────┘│\n"
                      "└────────┴───────┴───────────────────────────┴───────────────────────────────────────────────────┘"));

    CHECK_THAT(run("0÷0"), Prints("1"));
    CHECK_THAT(run("1÷0"), Throws(kepler::DomainError));
    CHECK_THAT(run("0÷1"), Prints("0"));
    CHECK_THAT(run("¯0.13 ÷ 0.13"), Prints("¯1"));
    CHECK_THAT(run("¯3J1 ÷ 1"), Prints("¯3J1"));
    CHECK_THAT(run("¯1J0.5 ÷ 3J5"), Prints("¯0.01470588235J0.1911764706"));
    CHECK_THAT(run("1 2 3 ÷ 4 5 6"), Prints("0.25 0.4 0.5"));
    CHECK_THAT(run("0 7.2 ¯0.3 0J1 ¯3J0.5 ÷ 0 5 0.6 0.001 3J7"), Prints("1 1.44 ¯0.5 0J1000 ¯0.09482758621J0.3879310345"));
    CHECK_THAT(run("10 ÷ 1 2 3 4 5 6"), Prints("10 5 3.333333333 2.5 2 1.666666667"));
    CHECK_THAT(run("2 ¯3 4 ¯5 ¯1 ÷ 0.212"), Prints("9.433962264 ¯14.1509434 18.86792453 ¯23.58490566 ¯4.716981132"));
    CHECK_THAT(run("0 (1 2.1) ¯0.1 ÷ (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"),
               Prints("┌───────┬────────────────────────────────────────────────────────────────────┬──────────────────────────────────────────────────────────────────────────────────┐\n"
                      "│0 0 0 0│┌───────────┬──────────────────────────────────────────────────────┐│┌────────────────┬───────────────────────────────────────────────────────────────┐│\n"
                      "│       ││1.428571429│0.02837837838J¯0.1702702703 0.3230769231J¯0.4846153846│││¯0.0001876172608│┌──────────────┬──────────────────────────────────────────────┐││\n"
                      "│       │└───────────┴──────────────────────────────────────────────────────┘││                ││¯0.01428571429│¯0.01428571429 ¯0.0008896797153J0.002846975089│││\n"
                      "│       │                                                                    ││                │└──────────────┴──────────────────────────────────────────────┘││\n"
                      "│       │                                                                    │└────────────────┴───────────────────────────────────────────────────────────────┘│\n"
                      "└───────┴────────────────────────────────────────────────────────────────────┴──────────────────────────────────────────────────────────────────────────────────┘"));

    CHECK_THAT(run("0 (1 2.1 3) ¯0.1 ÷ (1 2.1 3 4) (0.7 (2J12 2J3)) (533 (7 (7 10J32)))"), Throws(kepler::LengthError));

    CHECK_THAT(run("28 1 0 1 132 0J1 01J1 0J1 3J4 ÷ 0 0J1 0 1 1J¯3.3 12 0J¯1 3J5 45.3J¯21"), Throws(kepler::DomainError));
    CHECK_THAT(run("1 ÷ 0 0J1 0 1 1J¯3.3 12 0J¯1 3J5 45.3J¯21"), Throws(kepler::DomainError));
    CHECK_THAT(run("0 0J1 0 1 1J¯3.3 12 0J¯1 3J5 45.3J¯21 ÷ 2"), Prints("0 0J0.5 0 0.5 0.5J¯1.65 6 0J¯0.5 1.5J2.5 22.65J¯10.5"));

    CHECK_THAT(run("1÷2"), Prints("0.5"));
    CHECK_THAT(run("100÷2"), Prints("50"));
    CHECK_THAT(run("23÷2"), Prints("11.5"));
    CHECK_THAT(run("1E1÷2J2"), Prints("2.5J¯2.5"));
    CHECK_THAT(run("1J2÷1J7"), Prints("0.3J¯0.1"));
    CHECK_THAT(run(" 1J2     ÷ 1J7 "), Prints("0.3J¯0.1"));
    CHECK_THAT(run(" 1J2 2    ÷ 1J7 1"), Prints("0.3J¯0.1 2"));
    CHECK_THAT(run("1J2 2 ÷ 1J7"), Prints("0.3J¯0.1 0.04J¯0.28"));
    CHECK_THAT(run("1J2 ÷ 1J7 2"), Prints("0.3J¯0.1 0.5J1"));

    CHECK_THAT(run("¯2 ¯1 0 ÷ ¯2 ¯1 0"), Prints("1 1 1"));

    CHECK_THAT(run("1J2 2 ÷ 1J7 2 3"), Throws(kepler::LengthError));
    CHECK_THAT(run("1J2 2 3 4 ÷ 1J7 2 3"), Throws(kepler::LengthError));

    CHECK_THAT(run("1÷2÷2"), Prints("1"));
    CHECK_THAT(run("(1÷2)÷2"), Prints("0.25"));
    CHECK_THAT(run("1÷(2÷2)"), Prints("1"));

    CHECK_THAT(run("÷5"), Prints("0.2"));
    CHECK_THAT(run("÷1"), Prints("1"));
    CHECK_THAT(run("÷0.1"), Prints("10"));
    CHECK_THAT(run("÷¯.25 .5 1 2 ¯4"), Prints("¯4 2 1 0.5 ¯0.25"));
    CHECK_THAT(run("÷0"), Throws(kepler::DomainError));

    CHECK_THAT(run("2÷5"), Prints("0.4"));
    CHECK_THAT(run("5÷5"), Prints("1"));
    CHECK_THAT(run("4÷2"), Prints("2"));
    CHECK_THAT(run("4.5÷2"), Prints("2.25"));
    CHECK_THAT(run("2÷0"), Throws(kepler::DomainError));
    CHECK_THAT(run("2.5÷0"), Throws(kepler::DomainError));

}

TEST_CASE_METHOD(fixture, "floor (⌊)", "[floor][function]") {
    CHECK_THAT(run("⌊1"), Prints("1"));
    CHECK_THAT(run("⌊0"), Prints("0"));
    CHECK_THAT(run("⌊¯1"), Prints("¯1"));
    CHECK_THAT(run("⌊0.12"), Prints("0"));
    CHECK_THAT(run("⌊¯0.12"), Prints("¯1"));
    CHECK_THAT(run("⌊2E10"), Prints("2E10"));
    CHECK_THAT(run("⌊2.0001E10"), Prints("2.0001E10"));
    CHECK_THAT(run("⌊2.0001E¯10"), Prints("0"));
    CHECK_THAT(run("⌊2.0001E4"), Prints("20001"));

    CHECK_THAT(run("⌊¯3.1416 3.1416 .99999999999 5E20 ¯0.5E¯10"), Prints("¯4 3 0 5E20 ¯1"));
    CHECK_THAT(run("⌊0.3J0.6 0.6J0.8 0.8J0.6 0.6J0.3 0.8J0.2 0.5J0.5"), Prints("0 0J1 1 0 1 1"));

    CHECK_THAT(run("2.001E4⌊2.0001E4"), Prints("20001"));
    CHECK_THAT(run("2.001E10⌊2.0001E10"), Prints("2.0001E10"));
    CHECK_THAT(run("0⌊1"), Prints("0"));
    CHECK_THAT(run("1.2⌊1.23"), Prints("1.2"));
    CHECK_THAT(run("0⌊0"), Prints("0"));
    CHECK_THAT(run("¯0.01⌊0"), Prints("¯0.01"));
    CHECK_THAT(run("¯0.01⌊¯0.011"), Prints("¯0.011"));
}

TEST_CASE_METHOD(fixture, "ceiling (⌈)", "[floor][function]") {
    CHECK_THAT(run("⌈1"), Prints("1"));
    CHECK_THAT(run("⌈0"), Prints("0"));
    CHECK_THAT(run("⌈¯1"), Prints("¯1"));
    CHECK_THAT(run("⌈0.12"), Prints("1"));
    CHECK_THAT(run("⌈¯0.12"), Prints("0"));
    CHECK_THAT(run("⌈2E10"), Prints("2E10"));
    CHECK_THAT(run("⌈2.0001E10"), Prints("2.0001E10"));
    CHECK_THAT(run("⌈2.0001E¯10"), Prints("1"));
    CHECK_THAT(run("⌈2.0001E4"), Prints("20001"));

    CHECK_THAT(run("⌈¯3.1416 3.1416 .99999999999 5E20 ¯0.5E¯10"), Prints("¯3 4 1 5E20 0"));
    CHECK_THAT(run("⌈0.3J0.6 0.6J0.8 0.8J0.6 0.6J0.3 0.8J0.2 0.5J0.5"), Prints("1J1 1J1 1J1 1J1 1J1 1J1"));

    CHECK_THAT(run("2.001E4⌈2.0001E4"), Prints("20010"));
    CHECK_THAT(run("2.001E10⌈2.0001E10"), Prints("2.001E10"));
    CHECK_THAT(run("0⌈1"), Prints("1"));
    CHECK_THAT(run("1.2⌈1.23"), Prints("1.23"));
    CHECK_THAT(run("0⌈0"), Prints("0"));
    CHECK_THAT(run("¯0.01⌈0"), Prints("0"));
    CHECK_THAT(run("¯0.01⌈¯0.011"), Prints("¯0.01"));
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
    CHECK_THAT(run("Var"), Prints("Hello, World!"));

    CHECK_THAT(run("Var←5E¯10 2E1 3J¯2.2"), Prints(""));
    CHECK_THAT(run("Var"), Prints("5E¯10 20 3J¯2.2"));

    CHECK_THAT(run("+Var"), Prints("5E¯10 20 3J2.2"));
    CHECK_THAT(run("Var + Var"), Prints("1E¯9 40 6J¯4.4"));
}
