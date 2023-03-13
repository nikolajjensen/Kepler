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
#include "datatypes.h"
#include "symbol_table.h"

namespace kepler {
    int run_file(const std::string& path, std::ostream & stream = std::cout);

    int run_repl();

    void safe_execution(std::vector<Char>& input, std::ostream & stream, SymbolTable* symbol_table = nullptr);
    void immediate_execution(std::vector<Char>& input, std::ostream & stream, SymbolTable* symbol_table = nullptr);
};