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

#include "interpreter.h"
#include "token_pattern_class.h"

kepler::interpreter::PhraseEvaluatorResult::PhraseEvaluatorResult(PhraseMatchType type_, Token result_) : type(type_), result(result_) {}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::remove_parenthesis(kepler::List<kepler::Token>& stack, kepler::Session& session) {
    if(stack[1].is(NilToken) || stack[1].is(BranchToken)) {
        // Signal value-error
        stack[1].tokenClass = ValueErrorToken;
    }

    stack.erase(stack.begin());
    stack.erase(stack.begin() + 2);

    return {Matched, stack[1]};
}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_niladic_function(kepler::List<kepler::Token> &stack, kepler::Session& session) {
    Token& n = stack[0];
    if(n.is(NiladicDefinedFunctionNameToken)) {
        if(session.current_class(n) == NiladicDefinedFunctionToken) {

        } else {
            return {Exception, Token(SyntaxErrorToken)};
        }
    } else if (n.is(NiladicSystemFunctionNameToken)) {

    }
}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_monadic_function(kepler::List<kepler::Token> &stack,
                                                                       kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_monadic_operator(kepler::List<kepler::Token> &stack,
                                                                       kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_dyadic_function(kepler::List<kepler::Token> &stack,
                                                                       kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_dyadic_operator(kepler::List<kepler::Token> &stack,
                                                                       kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_indexed_reference(kepler::List<kepler::Token> &stack, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_indexed_assignment(kepler::List<kepler::Token> &stack, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_assignment(kepler::List<kepler::Token> &stack, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::evaluate_variable(kepler::List<kepler::Token> &stack, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::build_index_list(kepler::List<kepler::Token> &stack,
                                                                      kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session) {

}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::phrase_evaluators::process_end_of_statement(kepler::List<kepler::Token> &stack,
                                                              kepler::List<kepler::interpreter::TokenPatternClass> pattern, kepler::Session& session) {

}

bool kepler::interpreter::match(const kepler::Token& token, TokenPatternClass patternClass) {
    if(patternClass == A || patternClass == B || patternClass == Z) {
        // Anything matches these.
        return true;
    } else if (patternClass == D) {
        return token.is(DyadicOperatorToken);
    } else if (patternClass == F || patternClass == G) {
        return token.is(DefinedFunctionNameToken) || token.is(PrimitiveFunctionToken) || token.is(SystemFunctionNameToken);
    } else if (patternClass == I || patternClass == J) {
        return token.is(PartialIndexListToken);
    } else if (patternClass == C || patternClass == K) {
        return token.is(CompleteIndexListToken);
    } else if (patternClass == L) {
        return token.is(LeftEndOfStatementToken);
    } else if (patternClass == M) {
        return token.is(MonadicOperatorToken);
    } else if (patternClass == N) {
        return token.is(NiladicDefinedFunctionNameToken) || token.is(NiladicSystemFunctionNameToken);
    } else if (patternClass == R) {
        return token.is(RightEndOfStatementToken);
    } else if (patternClass == V) {
        return token.is(VariableNameToken) || token.is(SystemVariableNameToken) || token.is(SharedVariableNameToken);
    } else if (patternClass == X) {
        return token.is(AssignmentArrowToken)
                || token.is(BranchArrowToken)
                || token.is(DefinedFunctionNameToken)
                || token.is(IndexSeparatorToken)
                || token.is(LeftAxisBracketToken)
                || token.is(LeftEndOfStatementToken)
                || token.is(LeftIndexBracketToken)
                || token.is(LeftParenthesisToken)
                || token.is(PrimitiveFunctionToken)
                || token.is(SystemFunctionNameToken)
                || token.is(RightAxisBracketToken);
    } else if (patternClass == LP) {
        return token.is(LeftParenthesisToken);
    } else if (patternClass == RP) {
        return token.is(RightParenthesisToken);
    } else if (patternClass == LB) {
        return token.is(LeftAxisBracketToken) || token.is(LeftIndexBracketToken);
    } else if (patternClass == RB) {
        return token.is(RightAxisBracketToken) || token.is(RightIndexBracketToken);
    } else if (patternClass == SC) {
        return token.is(SmallCircleToken);
    } else if (patternClass == IS) {
        return token.is(IndexSeparatorToken);
    } else if (patternClass == AA) {
        return token.is(AssignmentArrowToken);
    } else if (patternClass == BA) {
        return token.is(BranchArrowToken);
    } else {
        return false;
    }

}

bool kepler::interpreter::match_prefix(const kepler::List<kepler::Token>& stack, const kepler::List<TokenPatternClass>& pattern) {
    if(stack.size() < pattern.size()) {
        return false;
    }

    bool success = true;
    unsigned int i = 0;
    while(success && i < pattern.size()) {
        success = match(stack[i], pattern[i]);
        ++i;
    }
    return success;
}

kepler::interpreter::PhraseEvaluatorResult kepler::interpreter::evaluate_stack_prefix(kepler::List<kepler::Token>& stack, kepler::Session& session) {
    size_t stack_size = stack.size();

    if(stack_size == 0) {
        return PhraseEvaluatorResult(Unmatched);
    }

    else if (match_prefix(stack, phrase_patterns::LP_B_RP_pattern)) {
        return phrase_evaluators::remove_parenthesis(stack, session);
    } else if (match_prefix(stack, phrase_patterns::N_pattern)) {
        return phrase_evaluators::evaluate_niladic_function(stack, session);
    }

    else if (match_prefix(stack, phrase_patterns::X_F_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_function(stack, phrase_patterns::X_F_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::X_F_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_function(stack, phrase_patterns::X_F_LB_C_RB_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::X_F_M_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, phrase_patterns::X_F_M_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::X_F_M_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, phrase_patterns::X_F_M_LB_C_RB_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::A_F_M_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, phrase_patterns::A_F_M_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::A_F_M_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, phrase_patterns::A_F_M_LB_C_RB_B_pattern, session);
    }

    else if (match_prefix(stack, phrase_patterns::A_F_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_function(stack, phrase_patterns::A_F_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::A_F_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_function(stack, phrase_patterns::A_F_LB_C_RB_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::X_F_D_G_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_operator(stack, phrase_patterns::A_F_LB_C_RB_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::A_F_D_G_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_operator(stack, phrase_patterns::A_F_D_G_B_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::A_SC_D_G_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_operator(stack, phrase_patterns::A_SC_D_G_B_pattern, session);
    }

    else if (match_prefix(stack, phrase_patterns::A_LB_K_RB_pattern)) {
        return phrase_evaluators::evaluate_indexed_reference(stack, session);
    } else if (match_prefix(stack, phrase_patterns::V_LB_K_RB_AA_B_pattern)) {
        return phrase_evaluators::evaluate_indexed_assignment(stack, session);
    } else if (match_prefix(stack, phrase_patterns::V_AA_B_pattern)) {
        return phrase_evaluators::evaluate_assignment(stack, session);
    } else if (match_prefix(stack, phrase_patterns::V_pattern)) {
        return phrase_evaluators::evaluate_variable(stack, session);
    }

    else if (match_prefix(stack, phrase_patterns::RB_pattern)) {
        return phrase_evaluators::build_index_list(stack, phrase_patterns::RB_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::IS_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, phrase_patterns::IS_I_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::IS_B_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, phrase_patterns::IS_B_I_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::LB_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, phrase_patterns::LB_I_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::LB_B_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, phrase_patterns::LB_B_I_pattern, session);
    }

    else if (match_prefix(stack, phrase_patterns::L_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, phrase_patterns::L_R_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::L_B_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, phrase_patterns::L_B_R_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::L_AA_B_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, phrase_patterns::L_AA_B_R_pattern, session);
    } else if (match_prefix(stack, phrase_patterns::L_AA_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, phrase_patterns::L_AA_R_pattern, session);
    }

    return PhraseEvaluatorResult(Unmatched);

/*
    if (stack_size == 0) {
        return false;
    } else if(stack_size >= 3 && match(stack[0], LP) && match(stack[1], B) && match(stack[2], RP)) {
        // Remove parenthesis.
    } else if (stack_size >= 1 && match(stack[0], N)) {
        // Evaluate niladic function
    }

    else if (stack_size >= 3 && match(stack[0], X) && match(stack[1], F) && match(stack[2], B)) {
        // Evaluate monadic function
    } else if (stack_size >= 6
                && match(stack[0], X) && match(stack[1], F)
                && match(stack[2], LB) && match(stack[3], C)
                && match(stack[4], RB) && match(stack[5], B)) {
        // Evaluate monadic function
    }

    else if (stack_size >= 4 && match(stack[0], X) && match(stack[1], F) && match(stack[2], M) && match(stack[3], B)) {
        // Evaluate monadic operator
    } else if (stack_size >= 7
               && match(stack[0], X) && match(stack[1], F) && match(stack[2], M)
               && match(stack[3], LB) && match(stack[4], C)
               && match(stack[5], RB) && match(stack[6], B)) {
        // Evaluate monadic operator
    } else if (stack_size >= 4 && match(stack[0], A) && match(stack[1], F) && match(stack[2], M) && match(stack[3], B)) {
        // Evaluate monadic operator
    } else if (stack_size >= 7
               && match(stack[0], A) && match(stack[1], F) && match(stack[2], M)
               && match(stack[3], LB) && match(stack[4], C)
               && match(stack[5], RB) && match(stack[6], B)) {
        // Evaluate monadic operator
    }

    else if (stack_size >= 3 && match(stack[0], A) && match(stack[1], F) && match(stack[2], B)) {
        // Evaluate Dyadic function.
    } else if (stack_size >= 6
               && match(stack[0], A) && match(stack[1], F)
               && match(stack[2], LB) && match(stack[3], C)
               && match(stack[4], RB) && match(stack[5], B)) {
        // Evaluate Dyadic function.
    } else if (stack_size >= 5
               && match(stack[0], X) && match(stack[1], F)
               && match(stack[2], D) && match(stack[3], G)
               && match(stack[4], B)) {
        // Evaluate Dyadic operator.
    } else if (stack_size >= 5
               && match(stack[0], A) && match(stack[1], F)
               && match(stack[2], D) && match(stack[3], G)
               && match(stack[4], B)) {
        // Evaluate Dyadic operator.
    } else if (stack_size >= 5
               && match(stack[0], A) && match(stack[1], SC)
               && match(stack[2], D) && match(stack[3], G)
               && match(stack[4], B)) {
        // Evaluate Dyadic operator.
    }

    else if (stack_size >= 4 && match(stack[0], A) && match(stack[1], LB) && match(stack[2], K) && match(stack[3], RB)) {
        // Evaluate Indexed Reference.
    } else if (stack_size >= 6 && match(stack[0], V) && match(stack[1], LB) && match(stack[2], K) && match(stack[3], RB) &&
            match(stack[4], AA) && match(stack[5], B)) {
        // Evaluate Indexed Assignment.
    } else if (stack_size >= 3 && match(stack[0], V) && match(stack[1], AA) && match(stack[2], B)) {
        // Evaluate Assignment.
    } else if (stack_size >= 1 && match(stack[0], V)) {
        // Evaluate Variable.
    } else if (stack_size >= 1 && match(stack[0], RB)) {
        // Build Index List.
    } else if (stack_size >= 2 && match(stack[0], IS) && match(stack[1], I)) {
        // Build Index List.
    } else if (stack_size >= 3 && match(stack[0], IS) && match(stack[1], B) && match(stack[2], I)) {
        // Build Index List.
    } else if (stack_size >= 2 && match(stack[0], LB) && match(stack[1], I)) {
        // Build Index List.
    } else if (stack_size >= 3 && match(stack[0], LB) && match(stack[1], B) && match(stack[2], I)) {
        // Build Index List.
    }

    else if (stack_size >= 2 && match(stack[0], L) && match(stack[1], R)) {
        // Process End of statement.
    } else if (stack_size >= 3 && match(stack[0], L) && match(stack[1], B) && match(stack[2], R)) {
        // Process End of statement.
    } else if (stack_size >= 4 && match(stack[0], L) && match(stack[1], BA) && match(stack[2], B) && match(stack[3], R)) {
        // Process End of statement.
    } else if (stack_size >= 3 && match(stack[0], L) && match(stack[1], BA) && match(stack[2], R)) {
        // Process End of statement.
    }

*/
}

bool kepler::interpreter::interpret(kepler::Context *context, kepler::Session *session) {
    context->stack = {};

    auto it = context->currentStatement.rbegin();
    auto end_it = context->currentStatement.rend();
    bool done = false;

    PhraseEvaluatorResult evaluatorResult;

    while(!done) {
        evaluatorResult = evaluate_stack_prefix(context->stack, *session);

        if(evaluatorResult.type == Unmatched) {
            if(context->currentStatement.empty()) {
                // Signal syntax-error.
                context->result = Token(SyntaxErrorToken);
                done = true;
            } else {
                context->stack.insert(context->stack.end(),
                                      std::make_move_iterator(context->currentStatement.end() - 1),
                                      std::make_move_iterator(context->currentStatement.end()));
                context->currentStatement.erase(context->currentStatement.end() - 1);
            }
        } else if (evaluatorResult.type == Success || evaluatorResult.type == Exception) {
            context->result = evaluatorResult.result;
            done = true;
        }
    }
}

/*
bool kepler::interpreter::interpret(kepler::List<kepler::Token>& tokens, kepler::Token& result) {
    --
    Array first = boost::get<Array>(tokens.at(0).content.get());
    Char operation = boost::get<Char>(tokens.at(1).content.get());
    Array second = boost::get<Array>(tokens.at(2).content.get());

    if(operation == U'+') {
        Number first_num = boost::get<Number>(first.ravelList[0]);
        Number second_num = boost::get<Number>(second.ravelList[0]);

        result.content = List<Number>{Number(first_num.realScalar + second_num.realScalar)};
    }
--

    kepler::List<kepler::Token> stack;

    while(true) {
        kepler::interpreter::phrase_table_lookup(stack);
    }





    return true;
}
*/