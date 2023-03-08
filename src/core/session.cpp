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

kepler::Session::Session(std::string &&name) : session_name(std::move(name)), active_workspace("unnamed"), symbol_table() {
    symbol_table.set(constants::index_origin_id, constants::initial_index_origin);
    symbol_table.set(constants::print_precision_id, constants::initial_print_precision);
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
    List<Char> in = {input.begin(), input.end()};

    try {

        //auto start = std::chrono::high_resolution_clock::now();

        Tokenizer tokenizer;
        List<Token> tokens = tokenizer.tokenize(&in);

        Parser parser(tokens);
        parser.use_table(&symbol_table);
        auto ast = parser.parse();

        Interpreter interpreter(*ast, *ast->symbol_table);
        auto result = interpreter.interpret();

        //auto stop = std::chrono::high_resolution_clock::now();

        //auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        //std::cout << "Took " << us << " µs (" << (us / 1000.0) << " ms)" << std::endl;

        stream << result.to_string() << std::flush;
    } catch(kepler::error& err) {
        err.set_input(&in);
        stream << err.to_string() << std::flush;
    }
}