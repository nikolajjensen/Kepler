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
#include "core/evaluation/ast.h"
#include "error.h"
#include "symbol.h"

namespace kepler {
    class SymbolTable {
    private:
        std::map<std::u32string, Symbol> table;
        SymbolTable* parent;

        const Symbol& lookup(const std::u32string& id) const;

    public:
        SymbolTable();
        ~SymbolTable();

        void attach_parent(SymbolTable* parent);

        bool contains(const std::u32string& id) const;

        template <typename T>
        const T& get(const std::u32string& id) const {
            const Symbol& symbol = lookup(id);

            if(!symbol.content.has_value()) {
                throw kepler::error(InternalError, "ID '" + uni::utf32to8(id) + "' is defined, but has no value.");
            }

            if(!holds_alternative<T>(symbol.content.value())) {
                throw kepler::error(InternalError, "ID '" + uni::utf32to8(id) + "' has a value, but it is not the one requested.");
            }

            return std::get<T>(symbol.content.value());
        }

        SymbolType get_type(const std::u32string& id) const;

        void set(const std::u32string& id, const Array& value);
        void set(const std::u32string& id, Operation_ptr value);
        void set(const std::u32string& id, const Number& value);
        void bind_function(const std::u32string& id);

        void clear();
        void strip_values();

        void insert_system_parameters();
    };
};