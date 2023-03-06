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

#include "symbol_table.h"

namespace kepler {
    SymbolTable::SymbolTable() : table() {}

    void SymbolTable::set(const std::u32string &id, const Array& value) {
        table.insert_or_assign(id, value);
    }

    void SymbolTable::set(const std::u32string &id, const Number& value) {
        set(id, Array{{}, {value}});
    }

    bool SymbolTable::contains(const std::u32string &id) const {
        return table.contains(id);
    }

    const Array& SymbolTable::get(const std::u32string &id) const {
        return table.at(id);
    }
};