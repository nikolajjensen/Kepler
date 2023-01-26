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

using namespace kepler::interpreter;

EvaluationOutcome kepler::interpreter::optionally_replace(List<Token> &stack, int start, int end, boost::optional<Token>& token, Token& result, TokenClass errorClass) {
    if(start > end) {
        std::cerr << "INTERNAL ERROR: removing from " << start << " to " << end << " in stack is impossible." << std::endl;
        return Error;
    }

    if(!token) {
        result.tokenClass = errorClass;
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
    if(token.content && boost::get<Char>(token.content.get())) {
        const Char& token_content = boost::get<Char>(token.content.get());
        return token_content == characters::plus
                || token_content == characters::bar
                || token_content == characters::multiply
                || token_content == characters::divide
                || token_content == characters::tilde
                || token_content == characters::circle
                || token_content == characters::star
                || token_content == characters::up_stile
                || token_content == characters::down_stile
                || token_content == characters::stile
                || token_content == characters::circle_star
                || token_content == characters::quote_dot;
    }

    return false;
}

EvaluationOutcome phrase_evaluators::remove_parenthesis(kepler::List<kepler::Token>& stack, kepler::Token& result, kepler::Session& session) {
    if(stack[1].is(NilToken) || stack[1].is(BranchToken)) {
        // Signal value-error
        result.tokenClass = ValueErrorToken;
        return Error;
    }

    stack.erase(stack.begin());
    stack.erase(stack.begin() + 2);

    return Success;
}

EvaluationOutcome phrase_evaluators::evaluate_niladic_function(kepler::List<kepler::Token> &stack, kepler::Token& result, kepler::Session& session) {
    Token& N = stack[0];

    if(N.is(NiladicDefinedFunctionNameToken)) {
        if(session.current_class(N) == NiladicDefinedFunctionToken) {
            boost::optional<Token> token = form_table::form_table_evaluation({N}, {form_table::PatternClass::DFN});
            return optionally_replace(stack, 0, 0, token, result, SyntaxErrorToken);
        } else {
            result.tokenClass = SyntaxErrorToken;
            return Error;
        }
    } else if (N.is(NiladicSystemFunctionNameToken)) {
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

    if(!B.is_value()) {
        result.tokenClass = ValueErrorToken;
        return Error;
    }

    if(is_X_F_B_pattern) {
        // X F B

        if(F.is(DefinedFunctionNameToken)) {
            if(session.current_class(F) == DefinedFunctionToken) {
                boost::optional<Token> token = form_table::form_table_evaluation({F, B}, {form_table::PatternClass::DFN, form_table::PatternClass::B});
                return optionally_replace(stack, 1, 2, token, result, SyntaxErrorToken);
            } else {
                result.tokenClass = SyntaxErrorToken;
                return Error;
            }
        } else if (F.is(PrimitiveFunctionToken) || F.is(SystemFunctionNameToken)) {
            if(token_is_primitive_monadic_scalar_function(F) && !B.is_scalar()) {
                // Do something to the whole array...
                auto b = 2;
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
        result.tokenClass = NilToken;
    } else if (pattern == phrase_patterns::L_B_R_pattern) {
        result = stack[1];
    } else if (pattern == phrase_patterns::L_AA_R_pattern) {
        result.tokenClass = EscapeToken;
    } else if (pattern == phrase_patterns::L_AA_B_R_pattern) {
        if(Array *arr = boost::get<Array>(&stack[1].content.get())) {
            if(arr->rank() > 1) {
                result.tokenClass = RankErrorToken;
            }

            if(arr->ravelList.empty()) {
                result.tokenClass = NilToken;
            }
        }
    }

    return Finished;
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