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
#include "core/datatypes.h"
#include "core/symbol_table.h"
#include "core/evaluation/tokenizer.h"
#include "core/evaluation/parser.h"
#include <chrono>

class ParserFixture {
protected:
    kepler::SymbolTable symbol_table;

public:
    ParserFixture() {
        symbol_table.insert_system_parameters();
    }

    ~ParserFixture() {
        symbol_table.clear();
    }

protected:
    std::string run(std::string&& raw) {
        try {
            kepler::String converted = uni::utf8to32u(raw);
            std::vector<kepler::Char> input(converted.begin(), converted.end());

            kepler::Tokenizer tokenizer;
            auto tokens = tokenizer.tokenize(&input);

            kepler::Parser parser;
            parser.use_table(&symbol_table);
            return parser.parse(tokens)->to_string();
        } catch(kepler::Error& err) {
            return err.to_string();
        }
    }
};
