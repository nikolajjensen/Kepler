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
#include "core/constants/config.h"
#include "core/constants/literals.h"

kepler::Session::Session(std::string &&name) : session_name(std::move(name)), active_workspace("unnamed"), interpreter(*this) {
    active_workspace.symbol_table.set(constants::index_origin_id, constants::initial_index_origin);
    active_workspace.symbol_table.set(constants::print_precision_id, constants::initial_print_precision);
}
void display_prompt(std::string& input) {
    std::cout << kepler::constants::indent_prompt << std::flush;
    getline(std::cin, input);
}


std::u32string read_input() {
    std::string input;
    display_prompt(input);
    return uni::utf8to32u(input);
}

void kepler::Session::immediate_execution_mode() {
    std::stringstream ss;

    while(true) {
        std::u32string input = read_input();
        ss.str("");
        immediate_execution(std::move(input), ss);
        if(!ss.str().empty()) {
            std::cout << ss.str() << std::endl;
        }
    }
}

void kepler::Session::immediate_execution(std::u32string &&input, std::ostream &stream) {
    try {
        Context& new_context = active_workspace.add_context({std::move(input)});

        List<Token> tokens = tokenizer.tokenize(&new_context.current_line);

        //for(auto& tok : tokens) {
        //    std::cout << tok.to_string() << std::endl;
        //}

        ASTNode<Array>* ast = parser.parse(&tokens);

        //std::cout << "AST: " << ast->to_string() << std::endl;

        Array result = interpreter.interpret(ast);

        active_workspace.pop_context();

        stream << result.to_string() << std::flush;
    } catch(kepler::error& err) {
        stream << err.to_string() << std::flush;
    }
}