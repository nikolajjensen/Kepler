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

class GeneralFixture {
protected:
    kepler::SymbolTable symbol_table;
    std::stringstream output_stream;

public:
    GeneralFixture() {
        symbol_table.insert_system_parameters();
    }

    ~GeneralFixture() {
        symbol_table.clear();
    }

protected:
    std::string run(std::string&& input, bool timing = false) {
        //auto start = std::chrono::high_resolution_clock::now();

        // Clear the output_stream between runs.
        output_stream.str("");

        auto u32str = uni::utf8to32u(input);
        std::vector<kepler::Char> vec = {u32str.begin(), u32str.end()};
        kepler::safe_execution(vec, output_stream, true, &symbol_table);

        //auto stop = std::chrono::high_resolution_clock::now();
        //if(timing) {
        //    auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        //    std::cout << "Took " << us << " µs (" << (us / 1000.0) << " ms)" << std::endl;
        //}

        return output_stream.str();
    }
};
