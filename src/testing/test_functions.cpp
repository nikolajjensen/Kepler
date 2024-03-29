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
#include "testing/fixtures/general_fixture.h"
#include "matcher.h"
#include "core/error_type.h"

TEST_CASE_METHOD(GeneralFixture, "plus (+)", "[plus][function]") {
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
    CHECK_THAT(run("(1+(2+2))"), Prints("5"));
}

TEST_CASE_METHOD(GeneralFixture, "minus (-)", "[minus][scalar][func]") {
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
    CHECK_THAT(run("(1-(2-2))"), Prints("1"));

    CHECK_THAT(run("'abc' - 'xyz'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'abc' - ('xyz' 2)"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "multiply (×)", "[multiply][function]") {
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
    CHECK_THAT(run("(1×(2×2))"), Prints("4"));
}

TEST_CASE_METHOD(GeneralFixture, "divide (÷)", "[divide][function]") {
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

TEST_CASE_METHOD(GeneralFixture, "floor (⌊)", "[floor][function]") {
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
    CHECK_THAT(run("⌊0.3J0.6 0.6J0.8 0.8J0.6 0.6J0.3 0.8J0.2 0.5J0.5"), Prints("0 0J1 1 0 1 0J1"));

    CHECK_THAT(run("2.001E4⌊2.0001E4"), Prints("20001"));
    CHECK_THAT(run("2.001E10⌊2.0001E10"), Prints("2.0001E10"));
    CHECK_THAT(run("0⌊1"), Prints("0"));
    CHECK_THAT(run("1.2⌊1.23"), Prints("1.2"));
    CHECK_THAT(run("0⌊0"), Prints("0"));
    CHECK_THAT(run("¯0.01⌊0"), Prints("¯0.01"));
    CHECK_THAT(run("¯0.01⌊¯0.011"), Prints("¯0.011"));

    CHECK_THAT(run("2J10⌊2.1J9.8"), Throws(kepler::DomainError));


    CHECK_THAT(run("¯0.01 0 1 2E¯1 232E100 ⌊ ¯0.011"), Prints("¯0.011 ¯0.011 ¯0.011 ¯0.011 ¯0.011"));
    CHECK_THAT(run("¯0.01 0 1 2E¯1 232E100 ⌊ 2"), Prints("¯0.01 0 1 0.2 2"));
    CHECK_THAT(run("¯0.01 0 1 2E¯1 232E100 ⌊ -0.0001 1 0.23 2E¯0 ¯232E100"), Prints("¯0.01 ¯1 ¯0.23 ¯2 2.32E102"));
}

TEST_CASE_METHOD(GeneralFixture, "ceiling (⌈)", "[ceiling][function]") {
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
    CHECK_THAT(run("⌈0.3J0.6 0.6J0.8 0.8J0.6 0.6J0.3 0.8J0.2 0.5J0.5"), Prints("0J1 1J1 1J1 1 1 1"));

    CHECK_THAT(run("2.001E4⌈2.0001E4"), Prints("20010"));
    CHECK_THAT(run("2.001E10⌈2.0001E10"), Prints("2.001E10"));
    CHECK_THAT(run("0⌈1"), Prints("1"));
    CHECK_THAT(run("1.2⌈1.23"), Prints("1.23"));
    CHECK_THAT(run("0⌈0"), Prints("0"));
    CHECK_THAT(run("¯0.01⌈0"), Prints("0"));
    CHECK_THAT(run("¯0.01⌈¯0.011"), Prints("¯0.01"));

    CHECK_THAT(run("2J10⌈2.1J9.8"), Throws(kepler::DomainError));

    CHECK_THAT(run("¯0.01 0 1 2E¯1 232E100 ⌈ ¯0.011"), Prints("¯0.01 0 1 0.2 2.32E102"));
    CHECK_THAT(run("¯0.01 0 1 2E¯1 232E100 ⌈ 2"), Prints("2 2 2 2 2.32E102"));
    CHECK_THAT(run("¯0.01 0 1 2E¯1 232E100 ⌈ -0.0001 1 0.23 2E¯0 ¯232E100"), Prints("¯0.0001 0 1 0.2 2.32E102"));
}

TEST_CASE_METHOD(GeneralFixture, "left-tack (⊣)", "[left-tack][function]") {
    CHECK_THAT(run("1 2 3 ⊣ 4 5 6"), Prints("1 2 3"));
    CHECK_THAT(run("3 ⊣ 4 5 6"), Prints("3"));
    CHECK_THAT(run("1 2 (3 4) ⊣ 4 5 6"),
               Prints("┌─┬─┬───┐\n"
                      "│1│2│3 4│\n"
                      "└─┴─┴───┘"));

    CHECK_THAT(run("⊣ 4 5 6"), Prints("4 5 6"));
    CHECK_THAT(run("⊣ 4"), Prints("4"));
    CHECK_THAT(run("⊣"), Prints(""));

    CHECK_THAT(run("'abc' ⊣ 1 2 3"), Prints("abc"));
    CHECK_THAT(run("⊣ 'columbus'"), Prints("columbus"));
}

TEST_CASE_METHOD(GeneralFixture, "right-tack (⊢)", "[right-tack][function]") {
    CHECK_THAT(run("1 2 3 ⊢ 4 5 6"), Prints("4 5 6"));
    CHECK_THAT(run("4 5 6 ⊢ 3"), Prints("3"));
    CHECK_THAT(run("4 5 6 ⊢ 1 2 (3 4)"),
               Prints("┌─┬─┬───┐\n"
                      "│1│2│3 4│\n"
                      "└─┴─┴───┘"));

    CHECK_THAT(run("⊢ 4 5 6"), Prints("4 5 6"));
    CHECK_THAT(run("⊢ 4"), Prints("4"));
    CHECK_THAT(run("1 2 3 ⊢"), Prints(""));
    CHECK_THAT(run("⊢"), Prints(""));

    CHECK_THAT(run("1 2 3 ⊢ 'abc'"), Prints("abc"));
    CHECK_THAT(run("⊢ 'columbus'"), Prints("columbus"));
}

TEST_CASE_METHOD(GeneralFixture, "less (<)", "[less][function]") {
    CHECK_THAT(run("5 < ¯4 2 0 5 20.21"), Prints("0 0 0 0 1"));
    CHECK_THAT(run("¯3.3 < ¯4 2 0 5 20.21"), Prints("0 1 1 1 1"));
    CHECK_THAT(run("(1 2) < (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│1 1│0 0│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) (0 5) < (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│1 1│1 0│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) < (3 4)"), Prints("1 1"));
    CHECK_THAT(run("1 2 3 1 2 3 < 1 2 0 ¯1 0.2 120"), Prints("0 0 0 0 0 1"));

    CHECK_THAT(run("'a' < 'b'"), Prints("1"));
    CHECK_THAT(run("'b' < 'b'"), Prints("0"));
    CHECK_THAT(run("'c' < 'b'"), Prints("0"));
    CHECK_THAT(run("'aa' < 'bb'"), Throws(kepler::DomainError));

    CHECK_THAT(run("2J1 < 3J1"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "less-equal (≤)", "[less-equal][function]") {
    CHECK_THAT(run("5 ≤ ¯4 2 0 5 20.21"), Prints("0 0 0 1 1"));
    CHECK_THAT(run("¯3.3 ≤ ¯4 2 0 5 20.21"), Prints("0 1 1 1 1"));
    CHECK_THAT(run("(1 2) ≤ (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│1 1│0 1│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) (0 5) ≤ (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│1 1│1 0│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) ≤ (3 4)"), Prints("1 1"));
    CHECK_THAT(run("1 2 3 1 2 3 ≤ 1 2 0 ¯1 0.2 120"), Prints("1 1 0 0 0 1"));

    CHECK_THAT(run("'a' ≤ 'b'"), Prints("1"));
    CHECK_THAT(run("'b' ≤ 'b'"), Prints("1"));
    CHECK_THAT(run("'c' ≤ 'b'"), Prints("0"));
    CHECK_THAT(run("'aa' ≤ 'bb'"), Throws(kepler::DomainError));

    CHECK_THAT(run("2J1 ≤ 3J1"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "equal (=)", "[equal][function]") {
    CHECK_THAT(run("5 = ¯4 2 0 5 20.21"), Prints("0 0 0 1 0"));
    CHECK_THAT(run("¯3.3 = ¯4 2 0 5 20.21"), Prints("0 0 0 0 0"));
    CHECK_THAT(run("(1 2) = (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│0 0│0 1│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) (0 5) = (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│0 0│0 0│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) = (3 4)"), Prints("0 0"));
    CHECK_THAT(run("1 2 3 1 2 3 = 1 2 0 ¯1 0.2 120"), Prints("1 1 0 0 0 0"));

    CHECK_THAT(run("'a' = 'b'"), Prints("0"));
    CHECK_THAT(run("'b' = 'b'"), Prints("1"));
    CHECK_THAT(run("'c' = 'b'"), Prints("0"));
    CHECK_THAT(run("'aa' = 'bb'"), Prints("0 0"));
    CHECK_THAT(run("'aa' = 'bbc'"), Throws(kepler::LengthError));

    CHECK_THAT(run("'a' = 'abca'"), Prints("1 0 0 1"));
    CHECK_THAT(run("'quiz-quaz' = 'q'"), Prints("1 0 0 0 0 1 0 0 0"));

    CHECK_THAT(run("1 ¯1.3 9.5J¯0.5 = (1 ¯1.3 9.5J¯0.5) (1 ¯1.3 9.5J¯0.5) (1 ¯1.3 9.5J¯0.5)"),
               Prints("┌─────┬─────┬─────┐\n"
                      "│1 0 0│0 1 0│0 0 1│\n"
                      "└─────┴─────┴─────┘"));
}

TEST_CASE_METHOD(GeneralFixture, "greater-equal (≥)", "[greater-equal][function]") {
    CHECK_THAT(run("5 ≥ ¯4 2 0 5 20.21"), Prints("1 1 1 1 0"));
    CHECK_THAT(run("¯3.3 ≥ ¯4 2 0 5 20.21"), Prints("1 0 0 0 0"));
    CHECK_THAT(run("(1 2) ≥ (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│0 0│1 1│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) (0 5) ≥ (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│0 0│0 1│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) ≥ (3 4)"), Prints("0 0"));
    CHECK_THAT(run("1 2 3 1 2 3 ≥ 1 2 0 ¯1 0.2 120"), Prints("1 1 1 1 1 0"));

    CHECK_THAT(run("'a' ≥ 'b'"), Prints("0"));
    CHECK_THAT(run("'b' ≥ 'b'"), Prints("1"));
    CHECK_THAT(run("'c' ≥ 'b'"), Prints("1"));
    CHECK_THAT(run("'aa' ≥ 'bb'"), Throws(kepler::DomainError));

    CHECK_THAT(run("2J1 ≥ 3J1"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "greater (>)", "[greater][function]") {
    CHECK_THAT(run("5 > ¯4 2 0 5 20.21"), Prints("1 1 1 0 0"));
    CHECK_THAT(run("¯3.3 > ¯4 2 0 5 20.21"), Prints("1 0 0 0 0"));
    CHECK_THAT(run("(1 2) > (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│0 0│1 0│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) (0 5) > (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│0 0│0 1│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) > (3 4)"), Prints("0 0"));
    CHECK_THAT(run("1 2 3 1 2 3 > 1 2 0 ¯1 0.2 120"), Prints("0 0 1 1 1 0"));

    CHECK_THAT(run("'a' > 'b'"), Prints("0"));
    CHECK_THAT(run("'b' > 'b'"), Prints("0"));
    CHECK_THAT(run("'c' > 'b'"), Prints("1"));
    CHECK_THAT(run("'aa' > 'bb'"), Throws(kepler::DomainError));

    CHECK_THAT(run("2J1 > 3J1"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "not-equal (≠)", "[not-equal][function]") {
    CHECK_THAT(run("5 ≠ ¯4 2 0 5 20.21"), Prints("1 1 1 0 1"));
    CHECK_THAT(run("¯3.3 ≠ ¯4 2 0 5 20.21"), Prints("1 1 1 1 1"));
    CHECK_THAT(run("(1 2) ≠ (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│1 1│1 0│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) (0 5) ≠ (3 4) (1 2)"),
               Prints("┌───┬───┐\n"
                      "│1 1│1 1│\n"
                      "└───┴───┘"));

    CHECK_THAT(run("(1 2) ≠ (3 4)"), Prints("1 1"));
    CHECK_THAT(run("1 2 3 1 2 3 ≠ 1 2 0 ¯1 0.2 120"), Prints("0 0 1 1 1 1"));

    CHECK_THAT(run("'a' ≠ 'b'"), Prints("1"));
    CHECK_THAT(run("'b' ≠ 'b'"), Prints("0"));
    CHECK_THAT(run("'c' ≠ 'b'"), Prints("1"));
    CHECK_THAT(run("'aa' ≠ 'bb'"), Prints("1 1"));

    CHECK_THAT(run("1 ¯1.3 9.5J¯0.5 ≠ (1 ¯1.3 9.5J¯0.5) (1 ¯1.3 9.5J¯0.5) (1 ¯1.3 9.5J¯0.5)"),
               Prints("┌─────┬─────┬─────┐\n"
                      "│0 1 1│1 0 1│1 1 0│\n"
                      "└─────┴─────┴─────┘"));

    CHECK_THAT(run("≠ 1 2 3 4 5 6"), Prints("1 1 1 1 1 1"));
    CHECK_THAT(run("≠ 1 2 3 1 2 3"), Prints("1 1 1 0 0 0"));
    CHECK_THAT(run("≠ 1 2 3 1 2 3 9"), Prints("1 1 1 0 0 0 1"));
    CHECK_THAT(run("≠ 1 (1 2) (1 2 3) (1 2 3) 1 2 3 (2 2)"), Prints("1 1 1 0 0 1 1 1"));
    CHECK_THAT(run("≠ 0J23 0J¯23"), Prints("1 1"));
    CHECK_THAT(run("≠ 0J23 0J¯23 0J23 1J23"), Prints("1 1 0 1"));
}

TEST_CASE_METHOD(GeneralFixture, "left shoe (⊂)", "[left-shoe][function]") {
    CHECK_THAT(run("⊂5"), Prints("5"));
    CHECK_THAT(run("⊂⊂23J¯12"), Prints("23J¯12"));
    CHECK_THAT(run("⊂⊂⊂⊂⊂⊂⊂⊂⊂23J¯12"), Prints("23J¯12"));
    CHECK_THAT(run("⊂1 2"),
               Prints("┌───┐\n"
                      "│1 2│\n"
                      "└───┘"));

    CHECK_THAT(run("⊂1 2 (3 4)"),
               Prints("┌─────────┐\n"
                      "│┌─┬─┬───┐│\n"
                      "││1│2│3 4││\n"
                      "│└─┴─┴───┘│\n"
                      "└─────────┘"));

    CHECK_THAT(run("⊂⊂1 2 (3 4)"),
               Prints("┌───────────┐\n"
                      "│┌─────────┐│\n"
                      "││┌─┬─┬───┐││\n"
                      "│││1│2│3 4│││\n"
                      "││└─┴─┴───┘││\n"
                      "│└─────────┘│\n"
                      "└───────────┘"));

    CHECK_THAT(run("⊂⊂⊂1 2 (3 4)"),
               Prints("┌─────────────┐\n"
                      "│┌───────────┐│\n"
                      "││┌─────────┐││\n"
                      "│││┌─┬─┬───┐│││\n"
                      "││││1│2│3 4││││\n"
                      "│││└─┴─┴───┘│││\n"
                      "││└─────────┘││\n"
                      "│└───────────┘│\n"
                      "└─────────────┘"));

    CHECK_THAT(run("0 1 0 1 ⊂ 1 2 3 4"),
               Prints("┌───┬─┐\n"
                      "│2 3│4│\n"
                      "└───┴─┘"));

    CHECK_THAT(run("0 1 1 1 ⊂ 1 2 3 4"),
               Prints("┌─┬─┬─┐\n"
                      "│2│3│4│\n"
                      "└─┴─┴─┘"));

    CHECK_THAT(run("0 0 0 0 ⊂ 1 2 3 4"), Prints(""));
    CHECK_THAT(run("0 1 0 1 ⊂ 1 2 3 4 6 7 8"),
               Prints("┌───┬─┐\n"
                      "│2 3│4│\n"
                      "└───┴─┘"));
    CHECK_THAT(run("0 0 0 0 ⊂ 1 2"), Throws(kepler::LengthError));
    CHECK_THAT(run("0 0 0 0 0 ⊂ 'Hello'"), Prints(""));
    CHECK_THAT(run("0 1 0 1 1 ⊂ 'Hello'"), Prints("el l o"));
    CHECK_THAT(run("1 1 1 1 1 ⊂ 'Hello'"), Prints("H e l l o"));
    CHECK_THAT(run("1 1 1 1 1 ⊂ ''"), Throws(kepler::LengthError));
    CHECK_THAT(run("1 1 1 1 1 ⊂ 'Hello, World!'"), Prints("H e l l o"));
}

TEST_CASE_METHOD(GeneralFixture, "without (~)", "[without][function]") {
    CHECK_THAT(run("~0 1 0 1 0 1 1"), Prints("1 0 1 0 1 0 0"));
    CHECK_THAT(run("~0 1 0.0 1J0 0J0 1 1"), Prints("1 0 1 0 1 0 0"));

    CHECK_THAT(run("~1.23 2.3 ¯1.1"), Throws(kepler::DomainError));

    CHECK_THAT(run("1 2 3 4 5 1.23 ~ 10"), Prints("1 2 3 4 5 1.23"));
    CHECK_THAT(run("1 2 3 4 5 1.23 ~ 1 10"), Prints("2 3 4 5 1.23"));
    CHECK_THAT(run("1 2 3 4 5 1.23 ~ 1 2 3"), Prints("4 5 1.23"));
    CHECK_THAT(run("1 2 3 4 5 1.23 ~ 1 2 3 4 5 1.23"), Prints(""));
    CHECK_THAT(run("1 ~ 120"), Prints("1"));

    CHECK_THAT(run("(3 3 3⍴1) ~ 1"), Throws(kepler::RankError));
    CHECK_THAT(run("3 3 3⍴1 ~ 1"),
               Prints("0 0 0\n"
                      "0 0 0\n"
                      "0 0 0\n"
                      "\n"
                      "0 0 0\n"
                      "0 0 0\n"
                      "0 0 0\n"
                      "\n"
                      "0 0 0\n"
                      "0 0 0\n"
                      "0 0 0"));

    CHECK_THAT(run("'Hello, World!' ~ 'o'"), Prints("Hell, Wrld!"));
    CHECK_THAT(run("'Hello, World!' ~ 'Hello, World!'"), Prints(""));
    CHECK_THAT(run("'Hello, World!' ~ 'Quiz'"), Prints("Hello, World!"));
}

TEST_CASE_METHOD(GeneralFixture, "iota (⍳)", "[iota][function]") {
    CHECK_THAT(run("⍳0"), Prints(""));
    CHECK_THAT(run("⍳¯0"), Prints(""));
    CHECK_THAT(run("⍳1"), Prints("1"));
    CHECK_THAT(run("⍳5"), Prints("1 2 3 4 5"));

    CHECK_THAT(run("⍳5.2"), Throws(kepler::DomainError));
    CHECK_THAT(run("⍳⍳5"), Throws(kepler::RankError));
    CHECK_THAT(run("⍳2 3⍴0"), Throws(kepler::RankError));
    CHECK_THAT(run("⍳¯2"), Throws(kepler::DomainError));
    CHECK_THAT(run("⍳2J2"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "rho (⍴)", "[rho][function]") {
    CHECK_THAT(run("⍴1 2 3"), Prints("3"));
    CHECK_THAT(run("⍴1 2 3 4"), Prints("4"));
    CHECK_THAT(run("⍴1"), Prints(""));
    CHECK_THAT(run("⍴(1 3 2) (0 1 2)"), Prints("2"));
    CHECK_THAT(run("⍴⍴(1 3 2) (0 1 2)"), Prints("1"));

    CHECK_THAT(run("0⍴1 2 3"), Prints(""));
    CHECK_THAT(run("10⍴1 2 3"), Prints("1 2 3 1 2 3 1 2 3 1"));

    CHECK_THAT(run("(3 3⍴1)⍴1 2 3"), Throws(kepler::RankError));
    CHECK_THAT(run("¯10 ¯10⍴1 2 3"), Throws(kepler::ValueError));

    CHECK_THAT(run("3 3⍴(3 3⍴1)"),
               Prints("1 1 1\n"
                      "1 1 1\n"
                      "1 1 1"));

    CHECK_THAT(run("2⍴(1 2 3) (1 2 3)"),
               Prints("┌─────┬─────┐\n"
                      "│1 2 3│1 2 3│\n"
                      "└─────┴─────┘"));

    CHECK_THAT(run("2 2⍴1 2 3"),
               Prints("1 2\n"
                      "3 1"));

    CHECK_THAT(run("2 2⍴1 2 3 4 5 6"),
               Prints("1 2\n"
                      "3 4"));

    CHECK_THAT(run("2 2 2⍴1"),
               Prints("1 1\n"
                      "1 1\n"
                      "\n"
                      "1 1\n"
                      "1 1"));

    CHECK_THAT(run("2 2 2 2⍴1"),
               Prints("1 1\n"
                      "1 1\n"
                      "\n"
                      "1 1\n"
                      "1 1\n"
                      "\n"
                      "\n"
                      "1 1\n"
                      "1 1\n"
                      "\n"
                      "1 1\n"
                      "1 1"));

    CHECK_THAT(run("2 3 4 6⍴1"),
               Prints("1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "\n"
                      "\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1\n"
                      "1 1 1 1 1 1"));


    CHECK_THAT(run("⍴⍴(3 3⍴0)"), Prints("2"));
}

TEST_CASE_METHOD(GeneralFixture, "and (∧)", "[and][function]") {
    CHECK_THAT(run("1 ∧ 1"), Prints("1"));
    CHECK_THAT(run("0 ∧ 1"), Prints("0"));
    CHECK_THAT(run("1 ∧ 0"), Prints("0"));
    CHECK_THAT(run("0 ∧ 0"), Prints("0"));
    CHECK_THAT(run("0 ∧ 0 1 0 1 1 1"), Prints("0 0 0 0 0 0"));
    CHECK_THAT(run("1 ∧ 0 1 0 1 1 1"), Prints("0 1 0 1 1 1"));
    CHECK_THAT(run("0 1 0 1 1 1 ∧ 1"), Prints("0 1 0 1 1 1"));
    CHECK_THAT(run("0 1 0 1 1 1 ∧ 0 1 0 1 1 1"), Prints("0 1 0 1 1 1"));

    CHECK_THAT(run("1J2 ∧ 1J2"), Throws(kepler::DomainError));
    CHECK_THAT(run(".1 ∧  0.1"), Throws(kepler::DomainError));

    CHECK_THAT(run("0 1 0 1 1 1 ∧"), Throws(kepler::LengthError));
    CHECK_THAT(run("∧ 0 1 0 1 1 1"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("0 1 0 1 1 1 ∧ 0 1 0 1"), Throws(kepler::LengthError));
    CHECK_THAT(run("'abc' ∧ 'loc'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ∧ 'a'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ∧ 1"), Throws(kepler::DomainError));
    CHECK_THAT(run("1 ∧ 'a'"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "or (∨)", "[or][function]") {
    CHECK_THAT(run("1 ∨ 1"), Prints("1"));
    CHECK_THAT(run("0 ∨ 1"), Prints("1"));
    CHECK_THAT(run("1 ∨ 0"), Prints("1"));
    CHECK_THAT(run("0 ∨ 0"), Prints("0"));
    CHECK_THAT(run("0 ∨ 0 1 0 1 1 1"), Prints("0 1 0 1 1 1"));
    CHECK_THAT(run("1 ∨ 0 1 0 1 1 1"), Prints("1 1 1 1 1 1"));
    CHECK_THAT(run("0 1 0 1 1 1 ∨ 1"), Prints("1 1 1 1 1 1"));
    CHECK_THAT(run("0 1 0 1 1 1 ∨ 0 1 0 1 1 1"), Prints("0 1 0 1 1 1"));

    CHECK_THAT(run("1J2 ∨ 1J2"), Throws(kepler::DomainError));
    CHECK_THAT(run(".1 ∨  0.1"), Throws(kepler::DomainError));

    CHECK_THAT(run("0 1 0 1 1 1 ∨"), Throws(kepler::LengthError));
    CHECK_THAT(run("∨ 0 1 0 1 1 1"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("0 1 0 1 1 1 ∨ 0 1 0 1"), Throws(kepler::LengthError));
    CHECK_THAT(run("'abc' ∨ 'loc'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ∨ 'a'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ∨ 1"), Throws(kepler::DomainError));
    CHECK_THAT(run("1 ∨ 'a'"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "nand (⍲)", "[nand][function]") {
    CHECK_THAT(run("1 ⍲ 1"), Prints("0"));
    CHECK_THAT(run("0 ⍲ 1"), Prints("1"));
    CHECK_THAT(run("1 ⍲ 0"), Prints("1"));
    CHECK_THAT(run("0 ⍲ 0"), Prints("1"));
    CHECK_THAT(run("0 ⍲ 0 1 0 1 1 1"), Prints("1 1 1 1 1 1"));
    CHECK_THAT(run("1 ⍲ 0 1 0 1 1 1"), Prints("1 0 1 0 0 0"));
    CHECK_THAT(run("0 1 0 1 1 1 ⍲ 1"), Prints("1 0 1 0 0 0"));
    CHECK_THAT(run("0 1 0 1 1 1 ⍲ 0 1 0 1 1 1"), Prints("1 0 1 0 0 0"));

    CHECK_THAT(run("1J2 ⍲ 1J2"), Throws(kepler::DomainError));
    CHECK_THAT(run(".1 ⍲  0.1"), Throws(kepler::DomainError));

    CHECK_THAT(run("0 1 0 1 1 1 ⍲"), Throws(kepler::LengthError));
    CHECK_THAT(run("⍲ 0 1 0 1 1 1"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("0 1 0 1 1 1 ⍲ 0 1 0 1"), Throws(kepler::LengthError));
    CHECK_THAT(run("'abc' ⍲ 'loc'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ⍲ 'a'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ⍲ 1"), Throws(kepler::DomainError));
    CHECK_THAT(run("1 ⍲ 'a'"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "nor (⍱)", "[nor][function]") {
    CHECK_THAT(run("1 ⍱ 1"), Prints("0"));
    CHECK_THAT(run("0 ⍱ 1"), Prints("0"));
    CHECK_THAT(run("1 ⍱ 0"), Prints("0"));
    CHECK_THAT(run("0 ⍱ 0"), Prints("1"));
    CHECK_THAT(run("0 ⍱ 0 1 0 1 1 1"), Prints("1 0 1 0 0 0"));
    CHECK_THAT(run("1 ⍱ 0 1 0 1 1 1"), Prints("0 0 0 0 0 0"));
    CHECK_THAT(run("0 1 0 1 1 1 ⍱ 1"), Prints("0 0 0 0 0 0"));
    CHECK_THAT(run("0 1 0 1 1 1 ⍱ 0 1 0 1 1 1"), Prints("1 0 1 0 0 0"));

    CHECK_THAT(run("1J2 ⍱ 1J2"), Throws(kepler::DomainError));
    CHECK_THAT(run(".1 ⍱  0.1"), Throws(kepler::DomainError));

    CHECK_THAT(run("0 1 0 1 1 1 ⍱"), Throws(kepler::LengthError));
    CHECK_THAT(run("⍱ 0 1 0 1 1 1"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("0 1 0 1 1 1 ⍱ 0 1 0 1"), Throws(kepler::LengthError));
    CHECK_THAT(run("'abc' ⍱ 'loc'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ⍱ 'a'"), Throws(kepler::DomainError));
    CHECK_THAT(run("'a' ⍱ 1"), Throws(kepler::DomainError));
    CHECK_THAT(run("1 ⍱ 'a'"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "Circle bar (⊖)", "[circle-bar][function]") {
    CHECK_THAT(run("⊖123"), Prints("123"));
    CHECK_THAT(run("2⊖123"), Prints("123"));
    CHECK_THAT(run("⊖'123'"), Prints("321"));
    CHECK_THAT(run("2⊖'123'"), Prints("312"));

    CHECK_THAT(run("⊖3 3⍴⍳10"), Prints("7 8 9\n"
                                       "4 5 6\n"
                                       "1 2 3"));

    CHECK_THAT(run("'a'⊖'123'"), Throws(kepler::DomainError));
    CHECK_THAT(run("1 2⊖'123'"), Throws(kepler::LengthError));

    CHECK_THAT(run("1 2 3⊖(3 3⍴⍳9)"), Prints("4 8 3\n"
                                             "7 2 6\n"
                                             "1 5 9"));

    CHECK_THAT(run("(3 3⍴1 2 3)⊖(2 3 3⍴⍳100)"), Prints("10  2 12\n"
                                                       "13  5 15\n"
                                                       "16  8 18\n"
                                                       "\n"
                                                       " 1 11  3\n"
                                                       " 4 14  6\n"
                                                       " 7 17  9"));

    CHECK_THAT(run("(3 3 2⍴1 2 3)⊖(2 3 3 2⍴⍳100)"), Prints("19  2\n"
                                                           "21 22\n"
                                                           " 5 24\n"
                                                           "\n"
                                                           "25  8\n"
                                                           "27 28\n"
                                                           "11 30\n"
                                                           "\n"
                                                           "31 14\n"
                                                           "33 34\n"
                                                           "17 36\n"
                                                           "\n"
                                                           "\n"
                                                           " 1 20\n"
                                                           " 3  4\n"
                                                           "23  6\n"
                                                           "\n"
                                                           " 7 26\n"
                                                           " 9 10\n"
                                                           "29 12\n"
                                                           "\n"
                                                           "13 32\n"
                                                           "15 16\n"
                                                           "35 18"));

    CHECK_THAT(run("(3 3 3⍴1 2 3)⊖(2 3 3 2⍴⍳100)"), Throws(kepler::LengthError));
}

TEST_CASE_METHOD(GeneralFixture, "Circle stile (⌽)", "[circle-stile][function]") {
    CHECK_THAT(run("⌽123"), Prints("123"));
    CHECK_THAT(run("2⌽123"), Prints("123"));
    CHECK_THAT(run("⌽'123'"), Prints("321"));
    CHECK_THAT(run("2⌽'123'"), Prints("312"));

    CHECK_THAT(run("⌽3 3⍴⍳10"), Prints("3 2 1\n"
                                       "6 5 4\n"
                                       "9 8 7"));

    CHECK_THAT(run("'a'⌽'123'"), Throws(kepler::DomainError));
    CHECK_THAT(run("1 2⌽'123'"), Throws(kepler::LengthError));

    CHECK_THAT(run("1 2 3⌽(3 3⍴⍳9)"), Prints("2 3 1\n"
                                             "6 4 5\n"
                                             "7 8 9"));

    CHECK_THAT(run("(2 3⍴1 2 3)⌽(2 3 3⍴⍳100)"), Prints(" 2  3  1\n"
                                                       " 6  4  5\n"
                                                       " 7  8  9\n"
                                                       "\n"
                                                       "11 12 10\n"
                                                       "15 13 14\n"
                                                       "16 17 18"));

    CHECK_THAT(run("(2 3 3⍴1 2 3)⌽(2 3 3 2⍴⍳100)"), Prints(" 2  1\n"
                                                           " 3  4\n"
                                                           " 6  5\n"
                                                           "\n"
                                                           " 8  7\n"
                                                           " 9 10\n"
                                                           "12 11\n"
                                                           "\n"
                                                           "14 13\n"
                                                           "15 16\n"
                                                           "18 17\n"
                                                           "\n"
                                                           "\n"
                                                           "20 19\n"
                                                           "21 22\n"
                                                           "24 23\n"
                                                           "\n"
                                                           "26 25\n"
                                                           "27 28\n"
                                                           "30 29\n"
                                                           "\n"
                                                           "32 31\n"
                                                           "33 34\n"
                                                           "36 35"));

    CHECK_THAT(run("(3 3 3⍴1 2 3)⌽(2 3 3 2⍴⍳100)"), Throws(kepler::LengthError));
}

TEST_CASE_METHOD(GeneralFixture, "Arrow Up (↑)", "[arrow-up][function]") {
    CHECK_THAT(run("¯10 'a'↑(2 2⍴⍳100)"), Throws(kepler::DomainError));
    CHECK_THAT(run("(3 3⍴1)↑(2 2⍴⍳100)"), Throws(kepler::DomainError));
    CHECK_THAT(run("3 3 3↑(2 2⍴⍳100)"), Throws(kepler::LengthError));

    CHECK_THAT(run("¯10 10↑(2 2⍴⍳100)"), Prints("0 0 0 0 0 0 0 0 0 0\n"
                                                "0 0 0 0 0 0 0 0 0 0\n"
                                                "0 0 0 0 0 0 0 0 0 0\n"
                                                "0 0 0 0 0 0 0 0 0 0\n"
                                                "0 0 0 0 0 0 0 0 0 0\n"
                                                "0 0 0 0 0 0 0 0 0 0\n"
                                                "0 0 0 0 0 0 0 0 0 0\n"
                                                "0 0 0 0 0 0 0 0 0 0\n"
                                                "1 2 0 0 0 0 0 0 0 0\n"
                                                "3 4 0 0 0 0 0 0 0 0"));

    CHECK_THAT(run("10↑(2 2⍴⍳100)"), Prints("1 2\n"
                                            "3 4\n"
                                            "0 0\n"
                                            "0 0\n"
                                            "0 0\n"
                                            "0 0\n"
                                            "0 0\n"
                                            "0 0\n"
                                            "0 0\n"
                                            "0 0"));

    CHECK_THAT(run("¯10↑(2 2⍴⍳100)"), Prints("0 0\n"
                                             "0 0\n"
                                             "0 0\n"
                                             "0 0\n"
                                             "0 0\n"
                                             "0 0\n"
                                             "0 0\n"
                                             "0 0\n"
                                             "1 2\n"
                                             "3 4"));

    CHECK_THAT(run("↑((2 2⍴⍳100) (3 3⍴⍳100))"), Prints("1 2 0\n"
                                                       "3 4 0\n"
                                                       "0 0 0\n"
                                                       "\n"
                                                       "1 2 3\n"
                                                       "4 5 6\n"
                                                       "7 8 9"));
}

TEST_CASE_METHOD(GeneralFixture, "Comma (,)", "[comma][function]") {
    CHECK_THAT(run(",↑((2 2⍴⍳100) (3 3⍴⍳100))"), Prints("1 2 0 3 4 0 0 0 0 1 2 3 4 5 6 7 8 9"));
    CHECK_THAT(run(",((2 2⍴⍳100) (3 3⍴⍳100))"), Prints("┌───┬─────┐\n"
                                                       "│1 2│1 2 3│\n"
                                                       "│3 4│4 5 6│\n"
                                                       "│   │7 8 9│\n"
                                                       "└───┴─────┘"));
}

TEST_CASE_METHOD(GeneralFixture, "Roll (?)", "[roll][function]") {
    CHECK_NOTHROW(run("?(0 3 1900 20)"));
    CHECK_THAT(run("?0.1"), Throws(kepler::DomainError));
    CHECK_THAT(run("?1J2"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "Star (*)", "[star][function]") {
    CHECK_THAT(run("*(0 3 10 20)"), Prints("1 20.08553692 22026.46579 485165195.4"));
    CHECK_THAT(run("*1J2"), Prints("¯1.131204384J2.471726672"));
    CHECK_THAT(run("*'abc'"), Throws(kepler::DomainError));

    CHECK_THAT(run("23*(0 3 10 20)"), Prints("1 12167 4.142651121E13 1.716155831E27"));
    CHECK_THAT(run("4*1J2"), Prints("¯3.730748307J1.442746363"));
    CHECK_THAT(run("'xyz'*2"), Throws(kepler::DomainError));
    CHECK_THAT(run("0*0"), Prints("1"));
    CHECK_THAT(run("0*100"), Prints("0"));
    CHECK_THAT(run("0*¯100"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "Log (⍟)", "[log][function]") {
    CHECK_THAT(run("⍟(1 3 10 20)"), Prints("0 1.098612289 2.302585093 2.995732274"));
    CHECK_THAT(run("⍟1J2"), Prints("0.8047189562J1.107148718"));
    CHECK_THAT(run("⍟'abc'"), Throws(kepler::DomainError));
    CHECK_THAT(run("⍟0"), Throws(kepler::DomainError));

    CHECK_THAT(run("23⍟(2 3 10 20)"), Prints("0.2210647295 0.3503793064 0.7343611356 0.955425865"));
    CHECK_THAT(run("4⍟1J2"), Prints("0.5804820237J0.7986389823"));
    CHECK_THAT(run("'xyz'⍟2"), Throws(kepler::DomainError));
    CHECK_THAT(run("0⍟0"), Prints("1"));
    CHECK_THAT(run("0⍟100"), Prints("0"));
    CHECK_THAT(run("1⍟¯100"), Throws(kepler::DomainError));
    CHECK_THAT(run("0⍟¯100"), Prints("0"));
}

TEST_CASE_METHOD(GeneralFixture, "Bar (|)", "[bar][function]") {
    CHECK_THAT(run("|(1 ¯3 10J10 20J¯1023)"), Prints("1 3 14.14213562 1023.195485"));
    CHECK_THAT(run("|1J2"), Prints("2.236067977"));
    CHECK_THAT(run("|'abc'"), Throws(kepler::DomainError));
    CHECK_THAT(run("|0"), Prints("0"));

    CHECK_THAT(run("23|(2 3 10 20 201)"), Prints("2 3 10 20 17"));
    CHECK_THAT(run("1.2|1J2"), Prints("¯0.2J0.8"));
    CHECK_THAT(run("'xyz'|2"), Throws(kepler::DomainError));
    CHECK_THAT(run("0|0"), Throws(kepler::DomainError));
    CHECK_THAT(run("0|100"), Throws(kepler::DomainError));
    CHECK_THAT(run("1|¯100"), Prints("0"));
    CHECK_THAT(run("0|¯100"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "Exclamation Mark (!)", "[exclamation-mark][function]") {
    CHECK_THAT(run("!0"), Prints("1"));
    CHECK_THAT(run("!¯10"), Throws(kepler::DomainError));
    CHECK_THAT(run("!¯0.1"), Prints("1.068628702"));
    CHECK_THAT(run("!0.1"), Prints("0.9513507699"));
    CHECK_THAT(run("!2"), Prints("2"));
    CHECK_THAT(run("!13.2"), Prints("1.049559019E10"));

    CHECK_THAT(run("!¯12"), Throws(kepler::DomainError));
    CHECK_THAT(run("!¯1000"), Throws(kepler::DomainError));
    CHECK_THAT(run("!¯1"), Throws(kepler::DomainError));

    CHECK_THAT(run("'a'!1.3"), Throws(kepler::DomainError));
    CHECK_THAT(run("(1 2 3)!1.3"), Prints("1.3 0.195 ¯0.0455"));

    CHECK_THAT(run("1!1.3"), Prints("1.3"));
    CHECK_THAT(run("2!2"), Prints("1"));
    CHECK_THAT(run("2!2J1"), Throws(kepler::DomainError));
}

TEST_CASE_METHOD(GeneralFixture, "Circle (○)", "[circle][function]") {
    CHECK_THAT(run("○(2 3 10 20 201 ¯1.2 ¯1.3J22)"), Prints("6.283185307 9.424777961 31.41592654 62.83185307 631.4601234 ¯3.769911184 ¯4.08407045J69.11503838"));
    CHECK_THAT(run("○'abc'"), Throws(kepler::DomainError));

    CHECK_THAT(run("0J1.2○1"), Throws(kepler::DomainError));
    CHECK_THAT(run("0.1○1"), Throws(kepler::DomainError));
    CHECK_THAT(run("¯13○1"), Throws(kepler::DomainError));
    CHECK_THAT(run("13○1"), Throws(kepler::DomainError));
    for(int i = -12; i <= 12; ++i) {
        std::string str = std::to_string(i);
        if(str.front() == '-') {
            str.erase(str.begin());
            str.insert(0, "¯");
        }
        CHECK_NOTHROW(run(std::to_string(i) + "○1"));
    }

    CHECK_THAT(run("¯12○3"), Prints("¯0.9899924966J0.1411200081"));
    CHECK_THAT(run("¯11○3"), Prints("0J3"));
    CHECK_THAT(run("¯10○3J¯123"), Prints("3J123"));
    CHECK_THAT(run("¯9○3J¯123"), Prints("3J¯123"));
    CHECK_THAT(run("¯8○3J¯123"), Prints("¯122.9959373J¯3.000099093"));
    CHECK_THAT(run("¯7○3J¯123"), Prints("0.0001981636936J¯1.562671258"));
    CHECK_THAT(run("¯7○¯1"), Throws(kepler::DomainError));
    CHECK_THAT(run("¯7○1"), Throws(kepler::DomainError));
    CHECK_THAT(run("¯6○3J¯123"), Prints("5.505645384J¯1.546411723"));
    CHECK_THAT(run("¯5○3J¯123"), Prints("5.505612394J¯1.546410112"));
    CHECK_THAT(run("¯4○3J¯123"), Prints("2.999900917J¯123.0040626"));
    CHECK_THAT(run("¯4○¯1"), Prints("0"));
    CHECK_THAT(run("¯3○3J¯123"), Prints("1.570598137J¯0.008125426218"));
    CHECK_THAT(run("¯2○3J¯123"), Prints("1.546411723J5.505645384"));
    CHECK_THAT(run("¯1○3J¯123"), Prints("0.02438460409J¯5.505645384"));
    CHECK_THAT(run("0○3J¯123"), Throws(kepler::DomainError));
    CHECK_THAT(run("0○¯1.2"), Throws(kepler::DomainError));
    CHECK_THAT(run("0○¯0.9"), Prints("0.4358898944"));
    CHECK_THAT(run("0○1.2"), Throws(kepler::DomainError));
    CHECK_THAT(run("0○0.9"), Prints("0.4358898944"));
    CHECK_THAT(run("1○3J¯123"), Prints("1.848331526E52J1.296651245E53"));
    CHECK_THAT(run("2○3J¯123"), Prints("¯1.296651245E53J1.848331526E52"));
    CHECK_THAT(run("3○3J¯12"), Prints("¯2.109662199E¯11J¯0.9999999999"));
    CHECK_THAT(run("4○3J¯123"), Prints("3.000099093J¯122.9959373"));
    CHECK_THAT(run("5○3J¯123"), Prints("¯8.895561447J4.630152895"));
    CHECK_THAT(run("6○3J¯123"), Prints("¯8.939770815J4.607255648"));
    CHECK_THAT(run("7○3J¯123"), Prints("0.9971355538J¯0.004037517657"));
    CHECK_THAT(run("8○3J¯123"), Prints("122.9959373J3.000099093"));
    CHECK_THAT(run("9○3J¯123"), Prints("3"));
    CHECK_THAT(run("10○3J¯123"), Prints("123.0365799"));
    CHECK_THAT(run("11○3J¯123"), Prints("¯123"));
    CHECK_THAT(run("12○3J¯123"), Prints("¯1.546410918"));
}