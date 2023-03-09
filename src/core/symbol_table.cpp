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
#include "core/error.h"
#include "core/constants/literals.h"
#include "core/constants/config.h"

namespace kepler {
    SymbolTable::SymbolTable() : table(), parent(nullptr) {

    }

    SymbolTable::~SymbolTable() {

    }

    const Symbol & SymbolTable::lookup(const std::u32string &id) const {
        if(table.contains(id)) {
            return table.at(id);
        } else if(parent != nullptr) {
            return parent->lookup(id);
        } else {
            throw kepler::error(DefinitionError, "Undefined variable.");
        }
    }

    void SymbolTable::attach_parent(SymbolTable *parent_) {
        parent = parent_;
    }

    void SymbolTable::set(const std::u32string &id, const Array& value) {
        if(parent != nullptr && parent->contains(id)) {
            parent->set(id, value);
        } else {
            table.insert_or_assign(id, std::move(Symbol(VariableSymbol, value)));
        }
    }

    void SymbolTable::set(const std::u32string &id, Operation_ptr value) {
        if(parent != nullptr && parent->contains(id)) {
            parent->set(id, value);
        } else {
            table.insert_or_assign(id, std::move(Symbol(FunctionSymbol, value)));
        }
    }

    void SymbolTable::set(const std::u32string &id, const Number& value) {
        set(id, Array{{}, {value}});
    }

    bool SymbolTable::contains(const std::u32string &id) const {
        return table.contains(id) || (parent != nullptr && parent->contains(id));
    }

    SymbolType SymbolTable::get_type(const std::u32string &id) const {
        return lookup(id).type;
    }

    void SymbolTable::bind_function(const std::u32string &id) {
        table.insert_or_assign(id, std::move(Symbol(FunctionSymbol)));
    }

    // Removes all keys and destroys all symbols.
    void SymbolTable::clear() {
        table.clear();
    }

    // Removes all values from the symbol table,
    // but keeps all entries and their bindings.
    void SymbolTable::strip_values() {
        for (auto& [key, val] : table) {
            val.content = std::nullopt;
        }
    }

    void SymbolTable::insert_system_parameters() {
        set(constants::index_origin_id, constants::initial_index_origin);
        set(constants::print_precision_id, constants::initial_print_precision);
    }
};