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

#include "execution.h"
#include "core/constants/literals.h"
#include "core/constants/config.h"
#include "core/helpers/file_reader.h"
#include "core/evaluation/tokenizer/tokenizer.h"
#include "core/evaluation/parser/parser.h"
#include "core/evaluation/interpreter.h"
#include "symbol_table.h"

int kepler::run_file(const std::string &path) {
    std::vector<Char> contents = read_file(path);

    try {
        Tokenizer tokenizer;
        auto tokens = tokenizer.tokenize(&contents);

        Parser parser(tokens);
        auto ast = parser.parse();

        Interpreter interpreter(*ast, *ast->symbol_table);
        auto output = interpreter.interpret();

        std::cout << output.to_string() << std::endl;

    } catch (kepler::error& err) {
        std::cout << "ERROR: " << err.to_string() << std::endl;
        return 1;
    }

    return 0;
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

int kepler::run_repl() {
    std::stringstream ss;
    SymbolTable symbol_table;

    symbol_table.insert_system_parameters();

    while(true) {
        std::u32string input = read_input();
        ss.str("");
        List<Char> in = {input.begin(), input.end()};
        kepler::immediate_execution(in, ss, &symbol_table);
        if(!ss.str().empty()) {
            std::cout << ss.str() << std::endl;
        }
    }
}

void kepler::immediate_execution(std::vector<Char> &input, std::ostream &stream, SymbolTable* symbol_table) {
    try {
        //auto start = std::chrono::high_resolution_clock::now();

        Tokenizer tokenizer;
        List<Token> tokens = tokenizer.tokenize(&input);

        Parser parser(tokens);
        if(symbol_table != nullptr) {
            parser.use_table(symbol_table);
        }
        auto ast = parser.parse();

        Interpreter interpreter(*ast, *ast->symbol_table);
        auto result = interpreter.interpret();

        //auto stop = std::chrono::high_resolution_clock::now();

        //auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        //std::cout << "Took " << us << " µs (" << (us / 1000.0) << " ms)" << std::endl;

        stream << result.to_string() << std::flush;
    } catch(kepler::error& err) {
        err.set_input(&input);
        stream << err.to_string() << std::flush;
    }
}