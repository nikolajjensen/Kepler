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

#pragma once
#include "../token.h"
#include "../token_class.h"
#include "../characters.h"
#include "evaluation_outcome.h"

namespace kepler {
    namespace interpreter {
        namespace form_table {
            enum PatternClass {
                DFN, B, Content
            };

            namespace tokens {
                const Token A(ConstantToken);
                const Token B(ConstantToken);
                const Token Z(ConstantToken);
                const Token I(CompleteIndexListToken);
                const Token K(CompleteIndexListToken);
                const Token F(PrimitiveFunctionToken);
                const Token G(DefinedFunctionToken);
                const Token DFN(DefinedFunctionToken);

                const Token plus(PrimitiveFunctionToken, characters::plus);
                const Token bar(PrimitiveFunctionToken, characters::bar);
                const Token multiply(PrimitiveFunctionToken, characters::multiply);
                const Token divide(PrimitiveFunctionToken, characters::divide);
                const Token down_stile(PrimitiveFunctionToken, characters::down_stile);
                const Token up_stile(PrimitiveFunctionToken, characters::up_stile);
                const Token star(PrimitiveFunctionToken, characters::star);
                const Token circle_star(PrimitiveFunctionToken, characters::circle_star);
                const Token stile(PrimitiveFunctionToken, characters::stile);
                const Token quote_dot(PrimitiveFunctionToken, characters::quote_dot);
                const Token circle(PrimitiveFunctionToken, characters::circle);
                const Token tilde(PrimitiveFunctionToken, characters::tilde);

                const Token quad(NilToken, characters::quad);
            };

            namespace patterns {
                const List<Token> conjugate = {tokens::plus, tokens::B};
                const List<Token> negative = {tokens::bar, tokens::B};
                const List<Token> direction = {tokens::multiply, tokens::B};
                const List<Token> reciprocal = {tokens::divide, tokens::B};
                const List<Token> floor = {tokens::down_stile, tokens::B};
                const List<Token> ceiling = {tokens::up_stile, tokens::B};
                const List<Token> exponential = {tokens::star, tokens::B};
                const List<Token> natural_logarithm = {tokens::circle_star, tokens::B};
                const List<Token> magnitude = {tokens::stile, tokens::B};
                const List<Token> factorial = {tokens::quote_dot, tokens::B};
                const List<Token> pi_times = {tokens::circle, tokens::B};
                // NB: Was not called "negation" but "not" in ISO.
                const List<Token> negation = {tokens::tilde, tokens::B};

                const List<Token> quad_input = {tokens::quad};
            };

            namespace evaluators {
                Token conjugate(List<Token>& operands);
                Token negative(List<Token>& operands);
            };

            bool match_form(const List<Token>& tokens, const List<PatternClass>& form, const List<Token>& pattern);

            //boost::optional<Token> form_table_evaluation(List<Token>&& tokens, const List<Token>& pattern);
            boost::optional<Token> form_table_evaluation(List<Token>&& tokens, List<PatternClass> form);
            bool lookup(List<Token>&& tokens, List<PatternClass>&& form);
        };

    };
};