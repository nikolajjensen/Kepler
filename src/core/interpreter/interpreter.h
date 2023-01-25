//
// Copyright 2022 Nikolaj Banke Jensen.
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
#include "../datatypes.h"
#include "../token.h"
#include "../env/context.h"
#include "../env/session.h"
#include "token_pattern_class.h"


namespace kepler {
    namespace interpreter {
        enum PhraseMatchType {
            Matched, Unmatched, Exception, Success
        };

        struct PhraseEvaluatorResult {
            PhraseMatchType type;
            Token result;

            PhraseEvaluatorResult(PhraseMatchType type = Unmatched, Token result = Token(NilToken));
        };

        namespace phrase_patterns {
            const kepler::List<TokenPatternClass> LP_B_RP_pattern = {LP, B, RP};
            const kepler::List<TokenPatternClass> N_pattern = {N};

            const kepler::List<TokenPatternClass> X_F_B_pattern = {X, F, B};
            const kepler::List<TokenPatternClass> X_F_LB_C_RB_B_pattern = {X, F, LB, C, RB, B};
            const kepler::List<TokenPatternClass> X_F_M_B_pattern = {X, F, M, B};
            const kepler::List<TokenPatternClass> X_F_M_LB_C_RB_B_pattern = {X, F, M, LB, C, RB, B};
            const kepler::List<TokenPatternClass> A_F_M_B_pattern = {A, F, M, B};
            const kepler::List<TokenPatternClass> A_F_M_LB_C_RB_B_pattern = {A, F, M, LB, C, RB, B};

            const kepler::List<TokenPatternClass> A_F_B_pattern = {A, F, B};
            const kepler::List<TokenPatternClass> A_F_LB_C_RB_B_pattern = {A, F, LB, C, RB, B};
            const kepler::List<TokenPatternClass> X_F_D_G_B_pattern = {X, F, D, G, B};
            const kepler::List<TokenPatternClass> A_F_D_G_B_pattern = {A, F, D, G, B};
            const kepler::List<TokenPatternClass> A_SC_D_G_B_pattern = {A, SC, D, G, B};

            const kepler::List<TokenPatternClass> A_LB_K_RB_pattern = {A, LB, K, RB};
            const kepler::List<TokenPatternClass> V_LB_K_RB_AA_B_pattern = {V, LB, K, RB, AA, B};
            const kepler::List<TokenPatternClass> V_AA_B_pattern = {V, AA, B};
            const kepler::List<TokenPatternClass> V_pattern = {V};

            const kepler::List<TokenPatternClass> RB_pattern = {RB};
            const kepler::List<TokenPatternClass> IS_I_pattern = {IS, I};
            const kepler::List<TokenPatternClass> IS_B_I_pattern = {IS, B, I};
            const kepler::List<TokenPatternClass> LB_I_pattern = {LB, I};
            const kepler::List<TokenPatternClass> LB_B_I_pattern = {LB, B, I};

            const kepler::List<TokenPatternClass> L_R_pattern = {L, R};
            const kepler::List<TokenPatternClass> L_B_R_pattern = {L, B, R};
            const kepler::List<TokenPatternClass> L_AA_B_R_pattern = {L, AA, B, R};
            const kepler::List<TokenPatternClass> L_AA_R_pattern = {L, AA, R};
        }

        namespace phrase_evaluators {
            PhraseEvaluatorResult remove_parenthesis(kepler::List<kepler::Token>& stack, kepler::Session& session);
            PhraseEvaluatorResult evaluate_niladic_function(kepler::List<kepler::Token>& stack, kepler::Session& session);
            PhraseEvaluatorResult evaluate_monadic_function(kepler::List<kepler::Token>& stack, kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session);
            PhraseEvaluatorResult evaluate_monadic_operator(kepler::List<kepler::Token>& stack, kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session);
            PhraseEvaluatorResult evaluate_dyadic_function(kepler::List<kepler::Token>& stack, kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session);
            PhraseEvaluatorResult evaluate_dyadic_operator(kepler::List<kepler::Token>& stack, kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session);
            PhraseEvaluatorResult evaluate_indexed_reference(kepler::List<kepler::Token>& stack, kepler::Session& session);
            PhraseEvaluatorResult evaluate_indexed_assignment(kepler::List<kepler::Token>& stack, kepler::Session& session);
            PhraseEvaluatorResult evaluate_assignment(kepler::List<kepler::Token>& stack, kepler::Session& session);
            PhraseEvaluatorResult evaluate_variable(kepler::List<kepler::Token>& stack, kepler::Session& session);
            PhraseEvaluatorResult build_index_list(kepler::List<kepler::Token>& stack, kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session);
            PhraseEvaluatorResult process_end_of_statement(kepler::List<kepler::Token>& stack, kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session);
        };

        bool match(const kepler::Token& token, TokenPatternClass patternClass);
        bool match_prefix(const kepler::List<kepler::Token>& stack, const kepler::List<TokenPatternClass>& pattern);

        PhraseEvaluatorResult evaluate_stack_prefix(kepler::List<kepler::Token>& stack, kepler::Session& session);

        //bool interpret(kepler::List<kepler::Token>& tokens, kepler::Token& result);
        bool interpret(kepler::Context* context, kepler::Session* session);
    }
};