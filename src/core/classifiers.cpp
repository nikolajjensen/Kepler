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
#include "core/env/session.h"

bool kepler::classifiers::is_identifier(const Token &token) {
    return token.tokenClass == SimpleIdentifierToken || token.tokenClass == DistinguishedIdentifierToken;
}

bool kepler::classifiers::is_literal(const Token &token) {
    return token.tokenClass == CharacterLiteralToken || token.tokenClass == NumericLiteralToken;
}

bool kepler::classifiers::is_lexical_unit(const Token &token) {
    return token.tokenClass == PrimitiveToken
            || kepler::classifiers::is_literal(token)
            || kepler::classifiers::is_literal(token);
}

bool kepler::classifiers::is_value(const Token &token) {
    return token.tokenClass == CommittedValueToken || token.tokenClass == ConstantToken;
}

bool kepler::classifiers::is_delimiter(const Token &token) {
    return token.tokenClass == PrimitiveFunctionToken
            || token.tokenClass == BranchArrowToken
            || token.tokenClass == AssignmentArrowToken
            || token.tokenClass == LeftEndOfStatementToken
            || token.tokenClass == RightEndOfStatementToken
            || token.tokenClass == LeftIndexBracketToken
            || token.tokenClass == RightIndexBracketToken
            || token.tokenClass == ElidedIndexMarkerToken
            || token.tokenClass == LeftAxisBracketToken
            || token.tokenClass == RightAxisBracketToken
            || token.tokenClass == LeftParenthesisToken
            || token.tokenClass == RightParenthesisToken
            || token.tokenClass == SmallCircleToken
            || token.tokenClass == SemicolonToken;
}

bool kepler::classifiers::is_defined_name(const Token &token) {
    return token.tokenClass == SharedVariableNameToken
            || token.tokenClass == VariableNameToken
            || token.tokenClass == DefinedFunctionNameToken
            || token.tokenClass == DefinedDyadicOperatorNameToken
            || token.tokenClass == DefinedMonadicOperatorNameToken
            || token.tokenClass == NiladicSystemFunctionNameToken
            || token.tokenClass == ResultNameToken
            || token.tokenClass == LeftArgumentNameToken
            || token.tokenClass == RightArgumentNameToken
            || token.tokenClass == LabelNameToken
            || token.tokenClass == LocalNameToken;
}

bool kepler::classifiers::is_defined_operator(const Token &token) {
    return token.tokenClass == DefinedDyadicOperatorToken || token.tokenClass == DefinedMonadicOperatorToken;
}

bool kepler::classifiers::is_system_name(const Token &token) {
    return token.tokenClass == SystemVariableNameToken
            || token.tokenClass == SystemFunctionNameToken
            || token.tokenClass == NiladicSystemFunctionNameToken;
}

bool kepler::classifiers::is_classified_name(const Token &token) {
    return kepler::classifiers::is_system_name(token) || kepler::classifiers::is_defined_name(token);
}

bool kepler::classifiers::is_syntactic_unit(const Token &token) {
    return kepler::classifiers::is_classified_name(token) || kepler::classifiers::is_delimiter(token);
}

bool kepler::classifiers::is_error(const Token &token) {
    return token.tokenClass == AxisErrorToken
            || token.tokenClass == DomainErrorToken
            || token.tokenClass == ImplicitErrorToken
            || token.tokenClass == IndexErrorToken
            || token.tokenClass == LengthErrorToken
            || token.tokenClass == LimitErrorToken
            || token.tokenClass == RankErrorToken
            || token.tokenClass == SyntaxErrorToken
            || token.tokenClass == ValueErrorToken
            || token.tokenClass == InterruptToken;
}

bool kepler::classifiers::is_report(const Token &token) {
    return token.tokenClass == IncorrectCommandToken
            || token.tokenClass == NotCopiedToken
            || token.tokenClass == NotErasedToken
            || token.tokenClass == NotFoundToken
            || token.tokenClass == NotSavedToken;
}

bool kepler::classifiers::is_exception(const Token &token) {
    return token.tokenClass == BranchToken
            || token.tokenClass == EscapeToken
            || token.tokenClass == ClearStateIndicatorToken
            || token.tokenClass == UnwindToken
            || kepler::classifiers::is_error(token)
            || kepler::classifiers::is_report(token);
}

bool kepler::classifiers::is_result(const Token &token) {
    return token.tokenClass == NilToken
            || kepler::classifiers::is_exception(token)
            || kepler::classifiers::is_value(token);
}

bool kepler::classifiers::is(const Token &token, TokenClass tokenClass) {
    return token.tokenClass == tokenClass;
}

bool kepler::classifiers::is_scalar(const Token& token) {
    if(token.contains<Array>()) {
        return token.get_content<Array>().rank() == 0;
    }

    return false;
}

bool kepler::classifiers::is_integral_within(const Number &lhs, const Number &rhs) {
    double rounded = round(lhs.real());
    return ((rounded + rhs.real()) >= lhs.real())
            && ((rounded - rhs.real()) <= lhs.real());
}

bool kepler::classifiers::is_near_integer(const Number &number, const Session &session) {
    return kepler::classifiers::is_integral_within(number, session.config.integer_tolerance);
}