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

#include "session.h"
#include "core/lexer/lexer.h"
#include "core/parser/parser.h"
#include "core/interpreter/interpreter.h"
#include "error.h"
#include "core/constants/prompts.h"
#include "core/helpers/printers.h"

kepler::Session::Session(std::string&& session_name_)
    :   active_workspace(config::clear_workspace_identifier),
        session_name(session_name_) {
    config::set_initial_values(active_workspace.symbol_table);
}

kepler::Token& kepler::Session::get_current_referent(kepler::Token &token) {
    auto& char_list = boost::get<List<Char>>(*token.content);

    kepler::Symbol& symbol_named_by_token = active_workspace.symbol_table.lookup(char_list);
    return symbol_named_by_token.referentList.front();
}

void kepler::Session::set_current_referent(kepler::Token &token, List<Token> &&content) {
    auto& id = token.get_content<List<Char>>();
    active_workspace.symbol_table.set(id, std::move(content));
}

kepler::TokenClass kepler::Session::current_class(kepler::Token &token) {
    return get_current_referent(token).token_class;
}


void display_prompt(std::string& input) {
    std::cout << kepler::prompts::indent_prompt << std::flush;
    getline(std::cin, input);
}

kepler::Token read_input() {
    std::string input;
    display_prompt(input);

    std::u32string result = uni::utf8to32u(input);
    return {kepler::ConstantToken, kepler::List<kepler::Char>(result.begin(), result.end())};
}

void kepler::Session::immediate_execution_mode() {
    while(true) {
        Token input = read_input();

        try {
            Token result = immediately_execute(input);
            if((result.token_class == BranchToken
                || result.token_class == ClearStateIndicatorToken
                || result.token_class == EscapeToken) && !active_workspace.state_indicator.empty()) {
                throw kepler::error(InternalError, "Unclear result.");
            } else if(result.token_class == ConstantToken) {
                kepler::printers::TokenPrinter tokenPrinter(std::cout);
                tokenPrinter(result);
                std::cout << std::endl;
            }
        } catch(kepler::error& err) {
            kepler::printers::ErrorPrinter errorPrinter(std::cout);
            errorPrinter(err);
            std::cout << std::endl;
        }
    }
}

kepler::Token kepler::Session::immediately_execute(List<Char> &&input) {
    return immediately_execute({kepler::ConstantToken, std::move(input)});
}

kepler::Token kepler::Session::immediately_execute(std::string &&input) {
    std::u32string result = uni::utf8to32u(input);
    return immediately_execute({kepler::ConstantToken, kepler::List<kepler::Char>(result.begin(), result.end())});
}


kepler::Token kepler::Session::immediately_execute(Token &&input) {
    return immediately_execute(input);
}

kepler::Token kepler::Session::immediately_execute(Token &input) {
    if(input.token_class == ConstantToken) {
        auto& content = input.get_content<List<Char>>();

        if(content.front() == kepler::characters::right_parenthesis) {
            throw kepler::error(InternalError, "System commands are not supported yet.");
        } else if(content.front() == kepler::characters::del) {
            throw kepler::error(InternalError, "User defined functions are not supported yet.");
        } else {
            Context& new_context = active_workspace.add_context({kepler::ImmediateExecutionMode, content});
            Token result = evaluate_line(new_context);
            active_workspace.pop_context();
            return result;
        }
    } else {
        throw kepler::error(InternalError, "Execution of unexpected token class.");
    }
}

kepler::Token kepler::Session::evaluate_line(kepler::Context& context) {
    kepler::lexer::Lexer::lex(&context);
    kepler::parser::Parser::parse(&context, this);
    return kepler::interpreter::interpret(&context, this);
}