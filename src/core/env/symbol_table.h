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

#pragma once
#include "symbol.h"
#include "../datatypes.h"

namespace kepler {
    class SymbolTable {
    private:
        List<Symbol> symbol_table;

        kepler::Symbol& create(const List<Char>& id);

    public:
        SymbolTable();

        Symbol& set(const List<Char>& id, List<Token> &&content);
        Symbol& set(const List<Char>& id, const List<Token> &content);
        Symbol& lookup(const List<Char>& id);
    };
};