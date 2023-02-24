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
#include "error.h"
#include "core/helpers/printers.h"
#include "core/constants/config.h"
#include "core/constants/literals.h"
#include "core/evaluation/evaluators.h"

kepler::Session::Session(std::string&& session_name_)
    :   active_workspace(constants::clear_workspace_identifier),
        session_name(session_name_) {
    constants::set_initial_values(active_workspace.symbol_table);
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
    std::cout << kepler::constants::indent_prompt << std::flush;
    getline(std::cin, input);
}

kepler::Token read_input() {
    std::string input;
    display_prompt(input);

    std::u32string result = uni::utf8to32u(input);
    return {kepler::ConstantToken, kepler::List<kepler::Char>(result.begin(), result.end())};
}

void kepler::Session::immediate_execution_mode() {
    std::stringstream ss;

    while(true) {
        Token input = read_input();
        ss.str("");
        immediate_execution(std::move(input), ss);
        if(!ss.str().empty()) {
            std::cout << ss.str() << std::endl;
        }
    }
}

void kepler::Session::immediate_execution(std::string &&input, std::ostream &stream) {
    std::u32string result = uni::utf8to32u(input);
    immediate_execution({kepler::ConstantToken, kepler::List<kepler::Char>(result.begin(), result.end())}, stream);
}

void kepler::Session::immediate_execution(Token &&input, std::ostream &stream) {
    try {
        if(input.token_class == ConstantToken) {
            auto& content = input.get_content<List<Char>>();

            if(content.front() == kepler::constants::right_parenthesis) {
                throw kepler::error(InternalError, "System commands are not supported yet.");
            } else if(content.front() == kepler::constants::del) {
                throw kepler::error(InternalError, "User defined functions are not supported yet.");
            } else {
                Context& new_context = active_workspace.add_context({kepler::ImmediateExecutionMode, content});

                Token result = evaluation::evaluate_line(new_context, *this);
                active_workspace.pop_context();

                if((result.token_class == BranchToken
                    || result.token_class == ClearStateIndicatorToken
                    || result.token_class == EscapeToken) && !active_workspace.state_indicator.empty()) {
                    throw kepler::error(InternalError, "Unclear result.");
                } else if(result.token_class == ConstantToken) {
                    Array& pp = get_system_parameter(constants::PP);
                    kepler::helpers::TokenPrinter tokenPrinter(stream, pp.get_content<Number>(0).real());
                    tokenPrinter(result);
                    stream << std::flush;
                }
            }
        } else {
            throw kepler::error(InternalError, "Execution of unexpected token class.");
        }
    } catch(kepler::error& err) {
        kepler::helpers::ErrorPrinter errorPrinter(stream);
        errorPrinter(err);
        stream << std::flush;
    }
}

/*
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

        if(content.front() == kepler::constants::right_parenthesis) {
            throw kepler::error(InternalError, "System commands are not supported yet.");
        } else if(content.front() == kepler::constants::del) {
            throw kepler::error(InternalError, "User defined functions are not supported yet.");
        } else {
            Context& new_context = active_workspace.add_context({kepler::ImmediateExecutionMode, content});

            Token result = evaluation::evaluate_line(new_context, *this);
            active_workspace.pop_context();
            return result;
        }
    } else {
        throw kepler::error(InternalError, "Execution of unexpected token class.");
    }
}
*/
kepler::Array& kepler::Session::get_system_parameter(const List<Char> &id) {
    Symbol& symbol = active_workspace.symbol_table.lookup(id);
    return symbol.referentList[0].get_content<Array>();
}