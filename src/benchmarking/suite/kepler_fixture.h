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
#include <iostream>
#include <benchmark/benchmark.h>
#include "../src/core/evaluation/execution.h"
#include "../src/interface/file_reader.h"

/**
 * Benchmark fixture for testing Kepler.
 *
 * It will load the Kepler file from disk before each benchmark.
 */
class KeplerFixture : public benchmark::Fixture {
private:
    kepler::SymbolTable symbol_table;
    std::vector<kepler::Char> input;
    std::ostream& stream;

public:
    KeplerFixture() : stream(std::cout) {}

    void SetUp(const ::benchmark::State& state) {
        symbol_table.insert_system_parameters();
    }

    void TearDown(const ::benchmark::State& state) {
        symbol_table.clear();
    }

    void load_file(const std::string& path) {
        try {
            std::vector<std::vector<kepler::Char>> lines = kepler::read_file(path);
            input = kepler::concat_lines(lines);
        } catch(kepler::Error& err) {
            stream << err.to_string() << std::endl;
        }
    }

    void execute() {
        kepler::safe_execution(input, stream, false, &symbol_table);
    }
};