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
#include <map>
#include <string>
#include "core/array.h"

namespace kepler {
    class SymbolTable {
    private:
        std::map<std::u32string, Array> table;

    public:
        SymbolTable();

        void set(const std::u32string& id, const Array& value);
        void set(const std::u32string& id, const Number& value);
        bool contains(const std::u32string& id) const;
        const Array& get(const std::u32string& id) const;
    };
};