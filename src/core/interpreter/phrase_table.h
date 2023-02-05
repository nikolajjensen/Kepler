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

        constexpr std::size_t LP_B_RP_size = 3;
        const pattern<LP_B_RP_size> LP_B_RP = {characters::left_parenthesis, Result, characters::right_parenthesis};

        constexpr std::size_t N_size = 1;
        const pattern<N_size> N = {Niladic};

        constexpr std::size_t X_F_B_size = 3;
        const pattern<X_F_B_size> X_F_B = {Wildcard, Func, Result};

        constexpr std::size_t X_F_LB_C_RB_B_size = 6;
        const pattern<X_F_LB_C_RB_B_size> X_F_LB_C_RB_B = {Wildcard, Func, characters::left_bracket, CompleteList, characters::right_bracket, Result};

        constexpr std::size_t X_F_M_B_size = 4;
        const pattern<X_F_M_B_size> X_F_M_B = {Wildcard, Func, Monadic, Result};

        constexpr std::size_t X_F_M_LB_C_RB_B_size = 7;
        const pattern<X_F_M_LB_C_RB_B_size> X_F_M_LB_C_RB_B = {Wildcard, Func, Monadic, characters::left_bracket, CompleteList, characters::right_bracket, Result};

        constexpr std::size_t A_F_M_B_size = 4;
        const pattern<A_F_M_B_size> A_F_M_B = {Result, Func, Monadic, Result};

        constexpr std::size_t A_F_M_LB_C_RB_B_size = 7;
        const pattern<A_F_M_LB_C_RB_B_size> A_F_M_LB_C_RB_B = {Result, Func, Monadic, characters::left_bracket, CompleteList, characters::right_bracket, Result};

        constexpr std::size_t A_F_B_size = 3;
        const pattern<A_F_B_size> A_F_B = {Result, Func, Result};

        constexpr std::size_t A_F_LB_C_RB_B_size = 6;
        const pattern<A_F_LB_C_RB_B_size> A_F_LB_C_RB_B = {Result, Func, characters::left_bracket, CompleteList, characters::right_bracket, Result};

        constexpr std::size_t X_F_D_G_B_size = 5;
        const pattern<X_F_D_G_B_size> X_F_D_G_B = {Wildcard, Func, Dyadic, Func, Result};

        constexpr std::size_t A_F_D_G_B_size = 5;
        const pattern<A_F_D_G_B_size> A_F_D_G_B = {Result, Func, Dyadic, Func, Result};

        constexpr std::size_t A_SM_D_G_B_size = 5;
        const pattern<A_SM_D_G_B_size> A_SM_D_G_B = {Result, characters::jot, Dyadic, Func, Result};

        constexpr std::size_t A_LB_K_RB_size = 4;
        const pattern<A_LB_K_RB_size> A_LB_K_RB = {Result, characters::left_bracket, CompleteList, characters::right_bracket};

        constexpr std::size_t V_LB_K_RB_AA_B_size = 6;
        const pattern<V_LB_K_RB_AA_B_size> V_LB_K_RB_AA_B = {Var, characters::left_bracket, CompleteList, characters::right_bracket, characters::left_arrow, Result};

        constexpr std::size_t V_AA_B_size = 3;
        const pattern<V_AA_B_size> V_AA_B = {Var, characters::left_arrow, Result};

        constexpr std::size_t V_size = 1;
        const pattern<V_size> V = {Var};

        constexpr std::size_t RB_size = 1;
        const pattern<RB_size> RB = {characters::right_bracket};

        constexpr std::size_t IS_I_size = 2;
        const pattern<IS_I_size> IS_I = {characters::semicolon, PartialList};

        constexpr std::size_t IS_B_I_size = 3;
        const pattern<IS_B_I_size> IS_B_I = {characters::semicolon, Result, PartialList};

        constexpr std::size_t LB_I_size = 2;
        const pattern<LB_I_size> LB_I = {characters::left_bracket, PartialList};

        constexpr std::size_t LB_B_I_size = 3;
        const pattern<LB_B_I_size> LB_B_I = {characters::left_bracket, Result, PartialList};

        constexpr std::size_t L_R_size = 2;
        const pattern<L_R_size> L_R = {LeftEOS, RightEOS};

        constexpr std::size_t L_B_R_size = 3;
        const pattern<L_B_R_size> L_B_R = {LeftEOS, Result, RightEOS};

        constexpr std::size_t L_BA_B_R_size = 4;
        const pattern<L_BA_B_R_size> L_BA_B_R = {LeftEOS, characters::right_arrow, Result, RightEOS};

        constexpr std::size_t L_BA_R_size = 3;
        const pattern<L_BA_R_size> L_BA_R = {LeftEOS, characters::right_arrow, RightEOS};

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