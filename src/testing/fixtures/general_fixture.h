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
#include <sstream>
#include <chrono>
#include "core/datatypes.h"
#include "core/evaluation/execution.h"
#include "core/symbol_table.h"

/**
 * Fixture for testing the execution of Kepler code.
 */
class GeneralFixture {
protected:
    kepler::SymbolTable symbol_table;
    std::stringstream output_stream;

public:
    /**
     * Creates a new GeneralFixture.
     * Initializes the symbol table with the system parameters.
     */
    GeneralFixture() {
        symbol_table.insert_system_parameters();
    }

    /**
     * Destroys the GeneralFixture.
     * Clears the symbol table.
     */
    ~GeneralFixture() {
        symbol_table.clear();
    }

protected:

    /**
     * Runs the execution on the given input.
     * @param input The input to execute.
     * @param timing Whether to time the execution.
     * @return The result of the execution.
     */
    std::string run(std::string&& input) {
        output_stream.str("");
        auto u32str = uni::utf8to32u(input);
        std::vector<kepler::Char> vec = {u32str.begin(), u32str.end()};
        kepler::safe_execution(vec, output_stream, true, &symbol_table);
        return output_stream.str();
    }
};
