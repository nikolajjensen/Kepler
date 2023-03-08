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

#include "classifiers.h"
#include "core/session.h"

bool kepler::helpers::is_function(TokenType type) {
    return type == PLUS || type == MINUS || type == TIMES || type == DIVIDE || type == FLOOR
           || type == CEILING || type == RIGHT_TACK || type == LEFT_TACK || type == IOTA || type == LESS
           || type == LESSEQ || type == EQ || type == GREATEREQ || type == GREATER || type == NEQ
           || type == WITHOUT || type == LSHOE || type == RHO || type == AND || type == OR
           || type == NAND || type == NOR || type == DECODE || type == ENCODE;
}

bool kepler::helpers::is_monadic_operator(TokenType type) {
    return type == COMMUTE || type == DIAERESIS || type == SLASH;
}

bool kepler::helpers::is_dyadic_operator(TokenType type) {
    return type == JOT || type == ATOP || type == OVER;
}

bool kepler::helpers::is_array_token(TokenType type) {
    return type == NUMBER || type == STRING || type == ID || type == ALPHA || type == OMEGA;
}

/*
bool kepler::helpers::is_identifier(const Token &token) {
    return token.token_class == SimpleIdentifierToken || token.token_class == DistinguishedIdentifierToken;
}

bool kepler::helpers::is_literal(const Token &token) {
    return token.token_class == CharacterLiteralToken || token.token_class == NumericLiteralToken;
}

bool kepler::helpers::is_lexical_unit(const Token &token) {
    return token.token_class == PrimitiveToken
            || kepler::helpers::is_literal(token)
            || kepler::helpers::is_literal(token);
}

bool kepler::helpers::is_value(const Token &token) {
    return token.token_class == CommittedValueToken || token.token_class == ConstantToken;
}

bool kepler::helpers::is_delimiter(const Token &token) {
    return token.token_class == PrimitiveFunctionToken
            || token.token_class == BranchArrowToken
            || token.token_class == AssignmentArrowToken
            || token.token_class == LeftEndOfStatementToken
            || token.token_class == RightEndOfStatementToken
            || token.token_class == LeftIndexBracketToken
            || token.token_class == RightIndexBracketToken
            || token.token_class == ElidedIndexMarkerToken
            || token.token_class == LeftAxisBracketToken
            || token.token_class == RightAxisBracketToken
            || token.token_class == LeftParenthesisToken
            || token.token_class == RightParenthesisToken
            || token.token_class == SmallCircleToken
            || token.token_class == SemicolonToken;
}

bool kepler::helpers::is_defined_name(const Token &token) {
    return token.token_class == SharedVariableNameToken
            || token.token_class == VariableNameToken
            || token.token_class == DefinedFunctionNameToken
            || token.token_class == DefinedDyadicOperatorNameToken
            || token.token_class == DefinedMonadicOperatorNameToken
            || token.token_class == NiladicSystemFunctionNameToken
            || token.token_class == ResultNameToken
            || token.token_class == LeftArgumentNameToken
            || token.token_class == RightArgumentNameToken
            || token.token_class == LabelNameToken
            || token.token_class == LocalNameToken;
}

bool kepler::helpers::is_defined_operator(const Token &token) {
    return token.token_class == DefinedDyadicOperatorToken || token.token_class == DefinedMonadicOperatorToken;
}

bool kepler::helpers::is_system_name(const Token &token) {
    return token.token_class == SystemVariableNameToken
            || token.token_class == SystemFunctionNameToken
            || token.token_class == NiladicSystemFunctionNameToken;
}

bool kepler::helpers::is_classified_name(const Token &token) {
    return kepler::helpers::is_system_name(token) || kepler::helpers::is_defined_name(token);
}

bool kepler::helpers::is_syntactic_unit(const Token &token) {
    return kepler::helpers::is_classified_name(token) || kepler::helpers::is_delimiter(token);
}

bool kepler::helpers::is_error(const Token &token) {
    return token.token_class == AxisErrorToken
            || token.token_class == DomainErrorToken
            || token.token_class == ImplicitErrorToken
            || token.token_class == IndexErrorToken
            || token.token_class == LengthErrorToken
            || token.token_class == LimitErrorToken
            || token.token_class == RankErrorToken
            || token.token_class == SyntaxErrorToken
            || token.token_class == ValueErrorToken
            || token.token_class == InterruptToken;
}

bool kepler::helpers::is_report(const Token &token) {
    return token.token_class == IncorrectCommandToken
            || token.token_class == NotCopiedToken
            || token.token_class == NotErasedToken
            || token.token_class == NotFoundToken
            || token.token_class == NotSavedToken;
}

bool kepler::helpers::is_exception(const Token &token) {
    return token.token_class == BranchToken
            || token.token_class == EscapeToken
            || token.token_class == ClearStateIndicatorToken
            || token.token_class == UnwindToken
            || kepler::helpers::is_error(token)
            || kepler::helpers::is_report(token);
}

bool kepler::helpers::is_result(const Token &token) {
    return token.token_class == NilToken
            || kepler::helpers::is_exception(token)
            || kepler::helpers::is_value(token);
}

bool kepler::helpers::is(const Token &token, TokenType tokenClass) {
    return token.token_class == tokenClass;
}

bool kepler::helpers::is_scalar(const Token& token) {
    if(token.contains<Array>()) {
        return token.get_content<Array>().rank() == 0;
    }

    return false;
}
 */