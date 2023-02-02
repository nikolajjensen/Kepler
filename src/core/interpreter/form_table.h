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
            /*enum MatchType {
                Type, Content
            };
            */

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

                const Token P_plus(PrimitiveFunctionToken, characters::plus);
                const Token P_bar(PrimitiveFunctionToken, characters::bar);
                const Token P_multiply(PrimitiveFunctionToken, characters::multiply);
                const Token P_divide(PrimitiveFunctionToken, characters::divide);
                const Token P_down_stile(PrimitiveFunctionToken, characters::down_stile);
                const Token P_up_stile(PrimitiveFunctionToken, characters::up_stile);
                const Token P_star(PrimitiveFunctionToken, characters::star);
                const Token P_circle_star(PrimitiveFunctionToken, characters::circle_star);
                const Token P_stile(PrimitiveFunctionToken, characters::stile);
                const Token P_quote_dot(PrimitiveFunctionToken, characters::quote_dot);
                const Token P_circle(PrimitiveFunctionToken, characters::circle);
                const Token P_tilde(PrimitiveFunctionToken, characters::tilde);
            };

            namespace patterns {
                const List<Token> conjugate = {tokens::P_plus, tokens::B};
                const List<Token> negative = {tokens::P_bar, tokens::B};
                const List<Token> direction = {tokens::P_multiply, tokens::B};
                const List<Token> reciprocal = {tokens::P_divide, tokens::B};
                const List<Token> floor = {tokens::P_down_stile, tokens::B};
                const List<Token> ceiling = {tokens::P_up_stile, tokens::B};
                const List<Token> exponential = {tokens::P_star, tokens::B};
                const List<Token> natural_logarithm = {tokens::P_circle_star, tokens::B};
                const List<Token> magnitude = {tokens::P_stile, tokens::B};
                const List<Token> factorial = {tokens::P_quote_dot, tokens::B};
                const List<Token> pi_times = {tokens::P_circle, tokens::B};
                // NB: Was not called "negation" but "not" in ISO.
                const List<Token> negation = {tokens::P_tilde, tokens::B};
            };

            namespace evaluators {
                Token conjugate(List<Token>& operands);
                Token negative(List<Token>& operands);
            };

            bool match_form(const List<Token>& tokens, const List<PatternClass>& form, const List<Token>& pattern);

            //boost::optional<Token> form_table_evaluation(List<Token>&& tokens, const List<Token>& pattern);
            boost::optional<Token> form_table_evaluation(List<Token>&& tokens, List<PatternClass> form);
        };

    };
};