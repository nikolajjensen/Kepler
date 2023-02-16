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
#include "../env/session.h"
#include "../characters.h"

namespace kepler {
    namespace phrase_table {
        enum TokenType {
            Result,
            Dyadic,
            Func,
            PartialList,
            CompleteList,
            LeftEOS,
            RightEOS,
            Monadic,
            Niladic,
            Var,
            Wildcard
        };

        using pattern_atomic = boost::variant<kepler::Token::content_type, TokenType>;
        template <std::size_t Size>
        using pattern = std::array<pattern_atomic, Size>;

        const pattern<3> LP_B_RP = {characters::left_parenthesis, Result, characters::right_parenthesis};
        const pattern<1> N = {Niladic};
        const pattern<3> X_F_B = {Wildcard, Func, Result};
        const pattern<6> X_F_LB_C_RB_B = {Wildcard, Func, characters::left_bracket, CompleteList, characters::right_bracket, Result};
        const pattern<4> X_F_M_B = {Wildcard, Func, Monadic, Result};
        const pattern<7> X_F_M_LB_C_RB_B = {Wildcard, Func, Monadic, characters::left_bracket, CompleteList, characters::right_bracket, Result};
        const pattern<4> A_F_M_B = {Result, Func, Monadic, Result};
        const pattern<7> A_F_M_LB_C_RB_B = {Result, Func, Monadic, characters::left_bracket, CompleteList, characters::right_bracket, Result};
        const pattern<3> A_F_B = {Result, Func, Result};
        const pattern<6> A_F_LB_C_RB_B = {Result, Func, characters::left_bracket, CompleteList, characters::right_bracket, Result};
        const pattern<5> X_F_D_G_B = {Wildcard, Func, Dyadic, Func, Result};
        const pattern<5> A_F_D_G_B = {Result, Func, Dyadic, Func, Result};
        const pattern<5> A_SM_D_G_B = {Result, characters::jot, Dyadic, Func, Result};
        const pattern<4> A_LB_K_RB = {Result, characters::left_bracket, CompleteList, characters::right_bracket};
        const pattern<6> V_LB_K_RB_AA_B = {Var, characters::left_bracket, CompleteList, characters::right_bracket, characters::left_arrow, Result};
        const pattern<3> V_AA_B = {Var, characters::left_arrow, Result};
        const pattern<1> V = {Var};
        const pattern<1> RB = {characters::right_bracket};
        const pattern<2> IS_I = {characters::semicolon, PartialList};
        const pattern<3> IS_B_I = {characters::semicolon, Result, PartialList};
        const pattern<2> LB_I = {characters::left_bracket, PartialList};
        const pattern<3> LB_B_I = {characters::left_bracket, Result, PartialList};
        const pattern<2> L_R = {LeftEOS, RightEOS};
        const pattern<3> L_B_R = {LeftEOS, Result, RightEOS};
        const pattern<4> L_BA_B_R = {LeftEOS, characters::right_arrow, Result, RightEOS};
        const pattern<3> L_BA_R = {LeftEOS, characters::right_arrow, RightEOS};

        using phrase_evaluator = void (*)(kepler::List<kepler::Token>& stack, kepler::Session& session);

        struct lookup_result {
            phrase_evaluator evaluator;
            bool end_of_statement;

            lookup_result(phrase_evaluator evaluator_, bool end_of_statement_ = false) : evaluator(evaluator_), end_of_statement(end_of_statement_) {}
        };

        namespace helpers {
            template <typename... Args>
            void erase(kepler::List<kepler::Token>& stack, Args... args) {
                static_assert(std::conjunction_v<std::is_same<Args, int>...>, "All indexes to delete must be 'int'.");
                int counter = 0;
                for(int i : {args ...}) {
                    stack.erase(stack.begin() + i - counter);
                    counter++;
                }
            }
        };

        namespace evaluators {
            template <std::size_t S, const pattern<S>& Pattern>
            void remove_parenthesis(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_niladic_function(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_monadic_function(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_monadic_operator(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_dyadic_function(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_dyadic_operator(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_indexed_reference(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_indexed_assignment(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_assignment(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void evaluate_variable(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void build_index_list(kepler::List<kepler::Token>& stack, kepler::Session& session);

            template <std::size_t S, const pattern<S>& Pattern>
            void process_end_of_statement(kepler::List<kepler::Token>& stack, kepler::Session& session);
        };

        bool match_type(const kepler::Token& token, TokenType type);

        template <std::size_t S, const pattern<S>& Pattern>
        bool match(const kepler::List<kepler::Token>& tokens);

        lookup_result lookup(kepler::List<kepler::Token>& stack);
    };
};