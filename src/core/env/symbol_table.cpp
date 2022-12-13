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

#include "symbol_table.h"

kepler::SymbolTable::SymbolTable() : symbol_table() {}

bool kepler::SymbolTable::create_symbol(const List<Char> &name) {
    auto it = std::find_if(symbol_table.begin(), symbol_table.end(), [&name](const Symbol& symbol){
        return symbol.name == name;
    });

    if(it == symbol_table.end()) {
        symbol_table.emplace_back(name);
        return true;
    }

    return false;
}

kepler::Symbol& kepler::SymbolTable::get_by_name(const List<Char> &name) {
    auto it = std::find_if(symbol_table.begin(), symbol_table.end(), [&name](const Symbol& symbol){
        return symbol.name == name;
    });

    if(it != symbol_table.end()) {
        return *it;
    }

    create_symbol(name);
    return get_by_name(name);
}