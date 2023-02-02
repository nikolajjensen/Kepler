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
#include "form_table.h"
#include "../classifiers.h"

using namespace kepler::interpreter;

EvaluationOutcome kepler::interpreter::optionally_replace(List<Token> &stack, int start, int end, boost::optional<Token>& token, Token& result, TokenClass errorClass) {
    if(start > end) {
        std::cerr << "INTERNAL ERROR: removing from " << start << " to " << end << " in stack is impossible." << std::endl;
        return Error;
    }

    if(!token) {
        result.set(errorClass, boost::none);
        return Error;
    }

    auto start_it = stack.begin() + start;
    auto end_it = stack.begin() + end;

    while(start_it != end_it) {
        stack.erase(start_it);
        ++start_it;
    }

    *(end_it - 1) = *token;

    return Success;
}

bool kepler::interpreter::token_is_primitive_monadic_scalar_function(const Token &token) {
    if(token.contains<Char>()) {
        const Char& character = token.get_content<Char>();
        return character == characters::plus
               || character == characters::bar
               || character == characters::multiply
               || character == characters::divide
               || character == characters::tilde
               || character == characters::circle
               || character == characters::star
               || character == characters::up_stile
               || character == characters::down_stile
               || character == characters::stile
               || character == characters::circle_star
               || character == characters::quote_dot;
    }

    return false;
}

EvaluationOutcome phrase_evaluators::remove_parenthesis(kepler::List<kepler::Token>& stack, kepler::Token& result, kepler::Session& session) {
    if(classifiers::is(stack[1], NilToken) || classifiers::is(stack[1], BranchToken)) {
        // Signal value-error
        result.set(ValueErrorToken, boost::none);
        return Error;
    }

    stack.erase(stack.begin());
    stack.erase(stack.begin() + 2);

    return Success;
}

EvaluationOutcome phrase_evaluators::evaluate_niladic_function(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session) {
    Token& N = stack[0];

    if(classifiers::is(N, NiladicDefinedFunctionNameToken)) {
        if(session.current_class(N) == NiladicDefinedFunctionToken) {
            boost::optional<Token> token = form_table::form_table_evaluation({N}, {form_table::PatternClass::DFN});
            return optionally_replace(stack, 0, 0, token, result, SyntaxErrorToken);
        } else {
            result.set(SyntaxErrorToken, boost::none);
            return Error;
        }
    } else if (classifiers::is(N, NiladicSystemFunctionNameToken)) {
        boost::optional<Token> token = form_table::form_table_evaluation({N}, {form_table::PatternClass::Content});
        return optionally_replace(stack, 0, 0, token, result, SyntaxErrorToken);
    }

    return Error;
}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_monadic_function(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session,
                                                                                                         kepler::List<kepler::interpreter::TokenPatternClass> pattern) {
    bool is_X_F_B_pattern = pattern == phrase_patterns::X_F_B_pattern;
    Token& B = (is_X_F_B_pattern ? stack[2] : stack[3]);
    Token& F = stack[1];

    if(!classifiers::is_value(B)) {
        result.set(ValueErrorToken, boost::none);
        return Error;
    }

    if(is_X_F_B_pattern) {
        // X F B

        if(classifiers::is(F, DefinedFunctionNameToken)) {
            if(session.current_class(F) == DefinedFunctionToken) {
                boost::optional<Token> token = form_table::form_table_evaluation({F, B}, {form_table::PatternClass::DFN, form_table::PatternClass::B});
                return optionally_replace(stack, 1, 2, token, result, SyntaxErrorToken);
            } else {
                result.set(SyntaxErrorToken, boost::none);
                return Error;
            }
        } else if (classifiers::is(F, PrimitiveFunctionToken) || classifiers::is(F, SystemFunctionNameToken)) {
            if(token_is_primitive_monadic_scalar_function(F) && !classifiers::is_scalar(B)) {
                // Do something to the whole array...
                //auto b = 2;
            } else {
                boost::optional<Token> token = form_table::form_table_evaluation({F, B}, {form_table::PatternClass::Content, form_table::PatternClass::B});
                return optionally_replace(stack, 1, 2, token, result, ValenceErrorToken);
            }
        }

    } else {
        // X F [C] B
    }
}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_monadic_operator(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session,
                                                                                                         kepler::List<kepler::interpreter::TokenPatternClass> pattern) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_dyadic_function(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session,
                                                                                                        kepler::List<kepler::interpreter::TokenPatternClass> pattern) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_dyadic_operator(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session,
                                                                                                        kepler::List<kepler::interpreter::TokenPatternClass> pattern) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_indexed_reference(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_indexed_assignment(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_assignment(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::evaluate_variable(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::build_index_list(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session,
                                                                                                kepler::List<kepler::interpreter::TokenPatternClass> pattern) {

}

kepler::interpreter::EvaluationOutcome kepler::interpreter::phrase_evaluators::process_end_of_statement(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session,
                                                                                                        kepler::List<kepler::interpreter::TokenPatternClass> pattern) {
    if(pattern == phrase_patterns::L_R_pattern) {
        result.set(NilToken);
    } else if (pattern == phrase_patterns::L_B_R_pattern) {
        result = stack[1];
    } else if (pattern == phrase_patterns::L_AA_R_pattern) {
        result.set(EscapeToken);
    } else if (pattern == phrase_patterns::L_AA_B_R_pattern) {
        Token& A = stack[1];
        if(A.contains<Array>()) {
            Array& array = A.get_content<Array>();

            if(array.rank() > 1) {
                result.set(RankErrorToken);
            } else if (array.empty()) {
                result.set(NilToken);
            }
        }

        if(Array *arr = boost::get<Array>(&stack[1].content.get())) {
            if(arr->rank() > 1) {
                result.set(RankErrorToken);
            }

            if(arr->ravelList.empty()) {
                result.set(NilToken);
            }
        }
    }

    return Finished;
}

bool kepler::interpreter::match(const kepler::Token& token, TokenPatternClass patternClass) {
    if(patternClass == A || patternClass == B || patternClass == Z) {
        return classifiers::is_result(token);
    } else if (patternClass == D) {
        return classifiers::is(token, DyadicOperatorToken);
    } else if (patternClass == F || patternClass == G) {
        return classifiers::is(token, DefinedFunctionNameToken) || classifiers::is(token, PrimitiveFunctionToken) || classifiers::is(token, SystemFunctionNameToken);
    } else if (patternClass == I || patternClass == J) {
        return classifiers::is(token, PartialIndexListToken);
    } else if (patternClass == C || patternClass == K) {
        return classifiers::is(token, CompleteIndexListToken);
    } else if (patternClass == L) {
        return classifiers::is(token, LeftEndOfStatementToken);
    } else if (patternClass == M) {
        return classifiers::is(token, MonadicOperatorToken);
    } else if (patternClass == N) {
        return classifiers::is(token, NiladicDefinedFunctionNameToken) || classifiers::is(token, NiladicSystemFunctionNameToken);
    } else if (patternClass == R) {
        return classifiers::is(token, RightEndOfStatementToken);
    } else if (patternClass == V) {
        return classifiers::is(token, VariableNameToken) || classifiers::is(token, SystemVariableNameToken) || classifiers::is(token, SharedVariableNameToken);
    } else if (patternClass == X) {
        return classifiers::is(token, AssignmentArrowToken)
                || classifiers::is(token, BranchArrowToken)
                || classifiers::is(token, DefinedFunctionNameToken)
                || classifiers::is(token, IndexSeparatorToken)
                || classifiers::is(token, LeftAxisBracketToken)
                || classifiers::is(token, LeftEndOfStatementToken)
                || classifiers::is(token, LeftIndexBracketToken)
                || classifiers::is(token, LeftParenthesisToken)
                || classifiers::is(token, PrimitiveFunctionToken)
                || classifiers::is(token, SystemFunctionNameToken)
                || classifiers::is(token, RightAxisBracketToken);
    } else if (patternClass == LP) {
        return classifiers::is(token, LeftParenthesisToken);
    } else if (patternClass == RP) {
        return classifiers::is(token, RightParenthesisToken);
    } else if (patternClass == LB) {
        return classifiers::is(token, LeftAxisBracketToken) || classifiers::is(token, LeftIndexBracketToken);
    } else if (patternClass == RB) {
        return classifiers::is(token, RightAxisBracketToken) || classifiers::is(token, RightIndexBracketToken);
    } else if (patternClass == SC) {
        return classifiers::is(token, SmallCircleToken);
    } else if (patternClass == IS) {
        return classifiers::is(token, IndexSeparatorToken);
    } else if (patternClass == AA) {
        return classifiers::is(token, AssignmentArrowToken);
    } else if (patternClass == BA) {
        return classifiers::is(token, BranchArrowToken);
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

kepler::interpreter::EvaluationOutcome kepler::interpreter::evaluate_stack_prefix(kepler::List<kepler::Token>& stack, kepler::Token& result, kepler::Session& session) {
    size_t stack_size = stack.size();

    if(stack_size == 0) {
        return Unmatched;
    }

    else if (match_prefix(stack, phrase_patterns::LP_B_RP_pattern)) {
        return phrase_evaluators::remove_parenthesis(stack, result, session);
    } else if (match_prefix(stack, phrase_patterns::N_pattern)) {
        return phrase_evaluators::evaluate_niladic_function(stack, result, session);
    }

    else if (match_prefix(stack, phrase_patterns::X_F_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_function(stack, result, session, phrase_patterns::X_F_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::X_F_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_function(stack, result, session, phrase_patterns::X_F_LB_C_RB_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::X_F_M_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, result, session, phrase_patterns::X_F_M_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::X_F_M_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, result, session, phrase_patterns::X_F_M_LB_C_RB_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::A_F_M_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, result, session, phrase_patterns::A_F_M_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::A_F_M_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_monadic_operator(stack, result, session, phrase_patterns::A_F_M_LB_C_RB_B_pattern);
    }

    else if (match_prefix(stack, phrase_patterns::A_F_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_function(stack, result, session, phrase_patterns::A_F_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::A_F_LB_C_RB_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_function(stack, result, session, phrase_patterns::A_F_LB_C_RB_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::X_F_D_G_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_operator(stack, result, session, phrase_patterns::A_F_LB_C_RB_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::A_F_D_G_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_operator(stack, result, session, phrase_patterns::A_F_D_G_B_pattern);
    } else if (match_prefix(stack, phrase_patterns::A_SC_D_G_B_pattern)) {
        return phrase_evaluators::evaluate_dyadic_operator(stack, result, session, phrase_patterns::A_SC_D_G_B_pattern);
    }

    else if (match_prefix(stack, phrase_patterns::A_LB_K_RB_pattern)) {
        return phrase_evaluators::evaluate_indexed_reference(stack, result, session);
    } else if (match_prefix(stack, phrase_patterns::V_LB_K_RB_AA_B_pattern)) {
        return phrase_evaluators::evaluate_indexed_assignment(stack, result, session);
    } else if (match_prefix(stack, phrase_patterns::V_AA_B_pattern)) {
        return phrase_evaluators::evaluate_assignment(stack, result, session);
    } else if (match_prefix(stack, phrase_patterns::V_pattern)) {
        return phrase_evaluators::evaluate_variable(stack, result, session);
    }

    else if (match_prefix(stack, phrase_patterns::RB_pattern)) {
        return phrase_evaluators::build_index_list(stack, result, session, phrase_patterns::RB_pattern);
    } else if (match_prefix(stack, phrase_patterns::IS_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, result, session, phrase_patterns::IS_I_pattern);
    } else if (match_prefix(stack, phrase_patterns::IS_B_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, result, session, phrase_patterns::IS_B_I_pattern);
    } else if (match_prefix(stack, phrase_patterns::LB_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, result, session, phrase_patterns::LB_I_pattern);
    } else if (match_prefix(stack, phrase_patterns::LB_B_I_pattern)) {
        return phrase_evaluators::build_index_list(stack, result, session, phrase_patterns::LB_B_I_pattern);
    }

    else if (match_prefix(stack, phrase_patterns::L_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, result, session, phrase_patterns::L_R_pattern);
    } else if (match_prefix(stack, phrase_patterns::L_B_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, result, session, phrase_patterns::L_B_R_pattern);
    } else if (match_prefix(stack, phrase_patterns::L_AA_B_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, result, session, phrase_patterns::L_AA_B_R_pattern);
    } else if (match_prefix(stack, phrase_patterns::L_AA_R_pattern)) {
        return phrase_evaluators::process_end_of_statement(stack, result, session, phrase_patterns::L_AA_R_pattern);
    }

    return Unmatched;
}

bool kepler::interpreter::interpret(kepler::Context *context, kepler::Session *session) {
    context->stack = {};

    auto it = context->currentStatement.rbegin();
    auto end_it = context->currentStatement.rend();
    bool done = false;

    EvaluationOutcome evaluationOutcome;

    while(!done) {
        evaluationOutcome = evaluate_stack_prefix(context->stack, context->result, *session);

        if(evaluationOutcome == Unmatched) {
            if(context->currentStatement.empty()) {
                // Signal syntax-error.
                context->result = Token(SyntaxErrorToken);
                done = true;
            } else {
                context->stack.insert(context->stack.begin(),
                                      std::make_move_iterator(context->currentStatement.end() - 1),
                                      std::make_move_iterator(context->currentStatement.end()));
                context->currentStatement.erase(context->currentStatement.end() - 1);
            }
        } else if (evaluationOutcome == Finished || evaluationOutcome == Error) {
            done = true;
        }
    }

    return evaluationOutcome != Error;
}