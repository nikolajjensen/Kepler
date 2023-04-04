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
#include "core/evaluation/tokenizer.h"
#include <chrono>

/**
 * Fixture for testing the tokenizer.
 */
class TokenizerFixture {
protected:

    /**
     * Runs the tokenizer on the given input.
     * @param raw The input to tokenize.
     * @return The result of the tokenization.
     */
    kepler::List<kepler::Token> run(std::string&& raw) {
        kepler::String converted = uni::utf8to32u(raw);
        std::vector<kepler::Char> input(converted.begin(), converted.end());
        kepler::Tokenizer tokenizer;
        std::vector<kepler::Token> output = tokenizer.tokenize(&input);
        return output;
    }
};
