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
#include "testing/matcher.h"
#include "testing/fixtures/parser_fixture.h"

using namespace kepler;

TEST_CASE_METHOD(parser_fixture, "dyadic-functions", "[dyadic-functions][parser]") {
    CHECK_THAT(run("1+2"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) Scalar(Token(NUMBER, 2))))"));

    CHECK_THAT(run("1-2"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(MINUS, -)) Scalar(Token(NUMBER, 2))))"));

    CHECK_THAT(run("1×2"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(TIMES, ×)) Scalar(Token(NUMBER, 2))))"));

    CHECK_THAT(run("1÷2"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(DIVIDE, ÷)) Scalar(Token(NUMBER, 2))))"));

    CHECK_THAT(run("1+2 3 4"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) Vector(Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 4)))))"));
    CHECK_THAT(run("2 3 4+1"),
               Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 4))) Function(Token(PLUS, +)) Scalar(Token(NUMBER, 1))))"));

    CHECK_THAT(run("1 2 3 - 4 3 2"),
               Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3))) Function(Token(MINUS, -)) Vector(Scalar(Token(NUMBER, 4)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 2)))))"));

    // Parser should accept mismatched argument length - interpreter should flag it.
    CHECK_THAT(run("1 2 - 4 3 2"),
               Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2))) Function(Token(MINUS, -)) Vector(Scalar(Token(NUMBER, 4)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 2)))))"));

}

TEST_CASE_METHOD(parser_fixture, "statement-separation", "[statement-separation][parser]") {
    CHECK_THAT(run("1+2◊3-2"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) Scalar(Token(NUMBER, 2))), DyadicFunction(Scalar(Token(NUMBER, 3)) Function(Token(MINUS, -)) Scalar(Token(NUMBER, 2))))"));

    CHECK_THAT(run("1-2 ◊ +23J1"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(MINUS, -)) Scalar(Token(NUMBER, 2))), MonadicFunction(Function(Token(PLUS, +)) Scalar(Token(NUMBER, 23J1))))"));

    CHECK_THAT(run("1×2 ◊ -/⍳2"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(TIMES, ×)) Scalar(Token(NUMBER, 2))), MonadicFunction(MonadicOperator(Token(SLASH, /) Function(Token(MINUS, -))) MonadicFunction(Function(Token(IOTA, ⍳)) Scalar(Token(NUMBER, 2)))))"));

    CHECK_THAT(run("1÷2 ◊ 1 2 - 3 4"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(DIVIDE, ÷)) Scalar(Token(NUMBER, 2))), DyadicFunction(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2))) Function(Token(MINUS, -)) Vector(Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 4)))))"));

    CHECK_THAT(run("1+2 3 4◊1111"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) Vector(Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 4)))), Scalar(Token(NUMBER, 1111)))"));

    CHECK_THAT(run("2 3 4+1◊"),
               Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 4))) Function(Token(PLUS, +)) Scalar(Token(NUMBER, 1))), Vector())"));

    CHECK_THAT(run("1 2 3 - 4 3 2 ◊ 12 - 13"),
               Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3))) Function(Token(MINUS, -)) Vector(Scalar(Token(NUMBER, 4)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 2)))), DyadicFunction(Scalar(Token(NUMBER, 12)) Function(Token(MINUS, -)) Scalar(Token(NUMBER, 13))))"));

    CHECK_THAT(run("1 2 - 4 3 2 ◊ ◊ ◊"),
               Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2))) Function(Token(MINUS, -)) Vector(Scalar(Token(NUMBER, 4)), Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 2)))), Vector(), Vector(), Vector())"));

    CHECK_THAT(run("◊ ◊ ◊"),
               Prints("Statements(Vector(), Vector(), Vector())"));

}

TEST_CASE_METHOD(parser_fixture, "user-defined-functions", "[user-defined-functions][parser]") {
    CHECK_THAT(run("{⍺+⍵}1 2 3"),
               Prints("Statements(MonadicFunction(AnonymousFunction(Statements(DyadicFunction(Variable(Token(ALPHA, ⍺)) Function(Token(PLUS, +)) Variable(Token(OMEGA, ⍵))))) Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3)))))"));

    CHECK_THAT(run("{}1 2 3"),
               Prints("Statements(MonadicFunction(AnonymousFunction(Statements()) Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3)))))"));

    CHECK_THAT(run("fn ← {⍺+⍵}"),
               Prints("Statements(FunctionAssignment(Token(ID, fn) ← AnonymousFunction(Statements(DyadicFunction(Variable(Token(ALPHA, ⍺)) Function(Token(PLUS, +)) Variable(Token(OMEGA, ⍵)))))))"));

    CHECK_THAT(run("fn ← {}"),
               Prints("Statements(FunctionAssignment(Token(ID, fn) ← AnonymousFunction(Statements())))"));

    CHECK_THAT(run("fn ← {q ← {-⍵} ◊ q⍵ }"),
               Prints("Statements(FunctionAssignment(Token(ID, fn) ← AnonymousFunction(Statements(FunctionAssignment(Token(ID, q) ← AnonymousFunction(Statements(MonadicFunction(Function(Token(MINUS, -)) Variable(Token(OMEGA, ⍵)))))), MonadicFunction(FunctionVariable(Token(ID, q)) Variable(Token(OMEGA, ⍵)))))))"));

    CHECK_THAT(run("fn ← {q ← {-⍵} ◊ q⍵ } ◊ fn 20J¯1"),
               Prints("Statements(FunctionAssignment(Token(ID, fn) ← AnonymousFunction(Statements(FunctionAssignment(Token(ID, q) ← AnonymousFunction(Statements(MonadicFunction(Function(Token(MINUS, -)) Variable(Token(OMEGA, ⍵)))))), MonadicFunction(FunctionVariable(Token(ID, q)) Variable(Token(OMEGA, ⍵)))))), MonadicFunction(FunctionVariable(Token(ID, fn)) Scalar(Token(NUMBER, 20J-1))))"));


    CHECK_THAT(run("{⍺+⍵}"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("←{⍺+⍵}"), Throws(kepler::SyntaxError));

    CHECK_THAT(run("FN←{⍺+⍵"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("FN←⍺+⍵}"), Throws(kepler::SyntaxError));
}

TEST_CASE_METHOD(parser_fixture, "variables", "[variables][parser]") {
    CHECK_THAT(run("var←12"),
               Prints("Statements(Assignment(Token(ID, var) ← Scalar(Token(NUMBER, 12))))"));

    CHECK_THAT(run("var ← 12 2 2 2J23"),
               Prints("Statements(Assignment(Token(ID, var) ← Vector(Scalar(Token(NUMBER, 12)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 2J23)))))"));

    CHECK_THAT(run("var ← ⍳10"),
               Prints("Statements(Assignment(Token(ID, var) ← MonadicFunction(Function(Token(IOTA, ⍳)) Scalar(Token(NUMBER, 10)))))"));

    CHECK_THAT(run("CAP ← 1+2"),
               Prints("Statements(Assignment(Token(ID, CAP) ← DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) Scalar(Token(NUMBER, 2)))))"));

    CHECK_THAT(run("←12"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("←12 2 2 2J23"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("←⍳10"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("←1+2"), Throws(kepler::SyntaxError));

    CHECK_THAT(run("v ← 12 ◊ 1 2 v 1 2"), Prints("Statements(Assignment(Token(ID, v) ← Scalar(Token(NUMBER, 12))), Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Variable(Token(ID, v)), Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2))))"));
    CHECK_THAT(run("v ← 2J¯1 ◊ 1 2 'abc' ¯5 ¯2E3 v 100"), Prints("Statements(Assignment(Token(ID, v) ← Scalar(Token(NUMBER, 2J-1))), Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(STRING, abc)), Scalar(Token(NUMBER, -5)), Scalar(Token(NUMBER, -2E3)), Variable(Token(ID, v)), Scalar(Token(NUMBER, 100))))"));
}

TEST_CASE_METHOD(parser_fixture, "parenthesis", "[parenthesis][parser]") {
    CHECK_THAT(run("1 2 (3 4) 5 6"),
               Prints("Statements(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Vector(Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 4))), Scalar(Token(NUMBER, 5)), Scalar(Token(NUMBER, 6))))"));

    CHECK_THAT(run("1 2 (((3 4))) 5 6"),
               Prints("Statements(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Vector(Scalar(Token(NUMBER, 3)), Scalar(Token(NUMBER, 4))), Scalar(Token(NUMBER, 5)), Scalar(Token(NUMBER, 6))))"));


    CHECK_THAT(run("(1+2)÷2"),
               Prints("Statements(DyadicFunction(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) Scalar(Token(NUMBER, 2))) Function(Token(DIVIDE, ÷)) Scalar(Token(NUMBER, 2))))"));

    CHECK_THAT(run("(1+2)÷(2-2)"),
               Prints("Statements(DyadicFunction(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) Scalar(Token(NUMBER, 2))) Function(Token(DIVIDE, ÷)) DyadicFunction(Scalar(Token(NUMBER, 2)) Function(Token(MINUS, -)) Scalar(Token(NUMBER, 2)))))"));

    CHECK_THAT(run("1+2÷2-2"),
               Prints("Statements(DyadicFunction(Scalar(Token(NUMBER, 1)) Function(Token(PLUS, +)) DyadicFunction(Scalar(Token(NUMBER, 2)) Function(Token(DIVIDE, ÷)) DyadicFunction(Scalar(Token(NUMBER, 2)) Function(Token(MINUS, -)) Scalar(Token(NUMBER, 2))))))"));

    CHECK_THAT(run("1 2 3 (+ 2 3)"), Prints("Statements(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3)), MonadicFunction(Function(Token(PLUS, +)) Vector(Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3))))))"));
    CHECK_THAT(run("1 2 3 (2 3 +)"), Throws(kepler::SyntaxError));

    CHECK_THAT(run(")"), Throws(kepler::SyntaxError));
    CHECK_THAT(run("("), Throws(kepler::SyntaxError));

}

TEST_CASE_METHOD(parser_fixture, "functions", "[functions][parser]") {
    CHECK_THAT(run("1 2 3 (+) 4 5 6"), Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3))) Function(Token(PLUS, +)) Vector(Scalar(Token(NUMBER, 4)), Scalar(Token(NUMBER, 5)), Scalar(Token(NUMBER, 6)))))"));

    CHECK_THAT(run("1 2 3 (+∘-) 4 5 6"), Prints("Statements(DyadicFunction(Vector(Scalar(Token(NUMBER, 1)), Scalar(Token(NUMBER, 2)), Scalar(Token(NUMBER, 3))) DyadicOperator(Function(Token(PLUS, +)) Token(JOT, ∘) Function(Token(MINUS, -))) Vector(Scalar(Token(NUMBER, 4)), Scalar(Token(NUMBER, 5)), Scalar(Token(NUMBER, 6)))))"));
}