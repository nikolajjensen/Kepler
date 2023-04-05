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

#pragma once
#include <string>
#include "core/datatypes.h"
#include "core/symbol_table.h"

namespace kepler {
    /**
     * Executes the '.kpl' file which is located at the given path, and outputs any results/errors to the given stream.
     * @param path The path of the file to execute.
     * @param stream The output stream to write to.
     * @return 1 if an error occurred, 0 otherwise.
     */
    int run_file(const std::string& path, std::ostream & stream = std::cout);

    /**
     * Starts a REPL (Read-Eval-Print-Loop) which reads input from the user, evaluates it, and prints the result.
     * @return 1 if an error occurred, 0 otherwise.
     */
    int run_repl();

    /**
     * Executes the given input, and outputs any results/errors to the given stream.
     *
     * This function is safe, meaning that it will not throw any exceptions.
     *
     * @param input The input to execute.
     * @param stream The output stream to write to.
     * @param print_last Whether or not to print the last result. In the REPL, this should be true, but in a file, it should be false.
     * @param symbol_table The symbol table to use during evaluation. Can be nullptr.
     */
    void safe_execution(const std::vector<Char>& input, std::ostream & stream, bool print_last = true, SymbolTable* symbol_table = nullptr);

    /**
     * Executes the given input, and outputs any results/errors to the given stream.
     *
     * This function is unsafe, meaning that it will throw exceptions if errors occur.
     *
     * @param input The input to execute.
     * @param stream The output stream to write to.
     * @param print_last Whether or not to print the last result. In the REPL, this should be true, but in a file, it should be false.
     * @param symbol_table The symbol table to use during evaluation. Can be nullptr.
     */
    void immediate_execution(const std::vector<Char>& input, std::ostream & stream, bool print_last = true, SymbolTable* symbol_table = nullptr);
};