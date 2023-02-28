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

#include "evaluators.h"
#include "grammar/lexer.h"
#include "grammar/parser.h"
#include "grammar/function_parser.h"
#include "reduce_statement/form_table.h"
#include "reduce_statement/phrase_table.h"

using namespace kepler;

Token evaluation::reduce_statement(Context &context, Session &session) {
    context.stack = {};

    auto it = context.current_statement.rbegin();
    auto end_it = context.current_statement.rend();
    bool done = false;

    while(!done) {
        phrase_table::lookup_result result = kepler::phrase_table::lookup(context.stack);

        if(result.evaluator == nullptr) {
            // No evaluator was found with lookup, so we push to stack.
            if(context.current_statement.empty()) {
                throw kepler::error(SyntaxError, "Ran out of tokens to evaluate, but is still not done...");
            } else {
                context.stack.insert(context.stack.begin(),
                                      std::make_move_iterator(context.current_statement.end() - 1),
                                      std::make_move_iterator(context.current_statement.end()));
                context.current_statement.erase(context.current_statement.end() - 1);
            }
        } else {
            result.evaluator(context.stack, session);

            if(result.end_of_statement) {
                done = true;
            }
        }
    }

    return context.stack[0];
}

Token evaluation::evaluate_statement(Context &context, Session& session) {
    for(auto& token : context.current_statement) {
        if(helpers::is_identifier(token)) {
            bind_token_class(token, session);
        } else if (helpers::is_literal(token)) {
            literal_conversion(token, session);
        }
    }

    Parser parser(context.current_statement);
    context.current_statement = parser.parse();

    context.current_statement.emplace(context.current_statement.begin(), LeftEndOfStatementToken);
    context.current_statement.emplace_back(RightEndOfStatementToken);

    return reduce_statement(context, session);
}

Token evaluation::evaluate_line(Context &context, Session &session) {
    Lexer lexer(context.current_line);
    context.current_statement = lexer.lex();
    return evaluate_statement(context, session);
}

void evaluation::evaluate_function_definition_request(List<Char> &input, Session &session) {
    FunctionParser parser(input);
    parser.parse();

    TokenClass current_class = session.current_class(parser.get_identifier());
    DefinedFunction defined_function;

    if(current_class == NilToken) {
        // Do nothing here, as defined_function has default initializer.
    } else {
        // If N is not editable, throw DefinitionError.
        // Set M to the current-referent of N.
    }

    session.active_workspace.add_context({
        FunctionDefinitionMode,
        parser.get_request(),
        defined_function,
        static_cast<int>(defined_function.canonical_representation.size())
    });


}

void evaluation::bind_token_class(Token &token, Session &session) {
    if(kepler::helpers::is(token, SimpleIdentifierToken)){
        TokenClass current_class = session.current_class(token);
        if(current_class == TokenClass::DefinedMonadicOperatorToken) {
            token.token_class = TokenClass::DefinedMonadicOperatorNameToken;
        } else if (current_class == TokenClass::DefinedDyadicOperatorToken) {
            token.token_class = TokenClass::DefinedDyadicOperatorNameToken;
        } else if (current_class == TokenClass::DefinedFunctionToken) {
            token.token_class = TokenClass::DefinedFunctionNameToken;
        } else if (current_class == TokenClass::NiladicDefinedFunctionToken) {
            token.token_class = TokenClass::NiladicDefinedFunctionNameToken;
        } else if (current_class == TokenClass::NilToken || current_class == TokenClass::VariableToken) {
            token.token_class = TokenClass::VariableNameToken;
        } else if (current_class == TokenClass::SharedVariableToken) {
            token.token_class = TokenClass::SharedVariableNameToken;
        } else if (current_class == TokenClass::LabelToken) {
            token.token_class = TokenClass::ConstantToken;
            token.content = session.get_current_referent(token).content;
        } else {
            // Should throw something here, this should never be reached.
            throw kepler::error(InternalError, "bind_token_class error: Unexpected case reached.");
        }
    } else if (token.token_class == TokenClass::DistinguishedIdentifierToken) {
        auto form_one = kepler::form_table::lookup({&token}, &session);
        auto form_two = kepler::form_table::lookup({&token, constants::left_arrow, form_table::Constant}, &session);
        auto form_three = kepler::form_table::lookup({&token, form_table::Constant}, &session);
        auto form_four = kepler::form_table::lookup({form_table::Constant, &token, form_table::Constant}, &session);

        if(form_one != nullptr && form_two != nullptr) {
            token.token_class = SystemVariableNameToken;
        } else if(form_one != nullptr && form_two == nullptr) {
            token.token_class = NiladicSystemFunctionNameToken;
        } else if(form_three != nullptr || form_four != nullptr) {
            token.token_class = SystemFunctionNameToken;
        } else {
            throw kepler::error(SyntaxError, "Distinguished identifier is unrecognised.");
        }
    }
}

void evaluation::literal_conversion(kepler::Token& token, kepler::Session& session) {
    List<Char> content;

    if(token.contains<List<Char>>()) {
        content = token.get_content<List<Char>>();
    } else if(token.contains<Char>()) {
        content = {token.get_content<Char>()};
    } else {
        throw kepler::error(InternalError, "Cannot convert unrecognized token to literal.");
    }

    Array vector;

    if(token.token_class == TokenClass::CharacterLiteralToken) {
        List<Char> char_vector(content.begin(), content.end());
        char_vector.erase(char_vector.begin());
        char_vector.pop_back();
        token.content = Array::vectorOf(std::move(char_vector));
    } else if(token.token_class == TokenClass::NumericLiteralToken) {
        List<Number> numeric_vector;

        auto start = content.begin();
        auto end = content.end();

        while(start != end) {
            while(start != end && *start == constants::blank) { ++start; }
            auto cursor = start;

            do {
                ++cursor;
            } while(cursor != end && *cursor != kepler::constants::blank);

            numeric_vector.emplace_back(number_from_characters({start, cursor}));
            start = cursor;
        }

        token.content = Array::vectorOf(std::move(numeric_vector));
    }

    token.token_class = ConstantToken;
}

void evaluation::scalar_conversion(kepler::Token &token) {
    if(token.contains<List<Char>>()) {
        auto& list = token.get_content<List<Char>>();
        token.content = list[0];
    }
}