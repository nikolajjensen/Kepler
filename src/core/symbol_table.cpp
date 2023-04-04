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
#include "core/literals.h"
#include "core/config.h"

namespace kepler {
    SymbolTable::SymbolTable() : table(), parent(nullptr) {

    }

    SymbolTable::SymbolTable(SymbolTable* parent_) : table(), parent(parent_) {}

    SymbolTable::~SymbolTable() {
        for (auto& [key, val] : table) {
            delete val;
        }
        table.clear();
    }

    const Symbol & SymbolTable::lookup(const std::u32string &id) const {
        if(table.contains(id)) {
            return *table.at(id);
        } else if(parent != nullptr) {
            return parent->lookup(id);
        } else {
            throw kepler::error(DefinitionError, "Undefined variable.");
        }
    }

    void SymbolTable::attach_parent(SymbolTable *parent_) {
        parent = parent_;
    }

    void SymbolTable::set(const std::u32string &id, const Array& value, bool locally_only) {
        if(!locally_only && parent != nullptr && parent->contains(id)) {
            parent->set(id, value);
        } else {
            table.insert_or_assign(id, new Symbol(VariableSymbol, value));
        }
    }

    void SymbolTable::set(const std::u32string &id, const Operation_ptr& value, bool locally_only) {
        if(!locally_only && parent != nullptr && parent->contains(id)) {
            parent->set(id, value);
        } else {
            table.insert_or_assign(id, new Symbol(FunctionSymbol, value));

            // Set the recursive symbol to the same symbol.
            //table.insert_or_assign(constants::recursive_call_id, table.at(id));
        }
    }

    void SymbolTable::set(const std::u32string &id, const Number& value, bool locally_only) {
        set(id, Array{{}, {value}}, locally_only);
    }

    void SymbolTable::remove(const std::u32string &id, bool locally_only) {
        if(table.contains(id)) {
            delete table.at(id);
            table.erase(id);
        } else if (!locally_only && parent != nullptr && parent->contains(id)) {
            parent->remove(id);
        }
    }

    bool SymbolTable::contains(const std::u32string &id) const {
        return table.contains(id) || (parent != nullptr && parent->contains(id));
    }

    SymbolType SymbolTable::get_type(const std::u32string &id) const {
        return lookup(id).type;
    }

    void SymbolTable::bind_function(const std::u32string &id) {
        table.insert_or_assign(id, new Symbol(FunctionSymbol));
    }

    // Removes all keys and destroys all symbols.
    void SymbolTable::clear() {
        table.clear();
    }

    // Removes all values from the symbol table,
    // but keeps all entries and their bindings.
    void SymbolTable::strip_values() {
        for (auto& [key, val] : table) {
            val->content = std::nullopt;
        }
    }

    void SymbolTable::insert_system_parameters() {
        set(constants::index_origin_id, constants::initial_index_origin);
        set(constants::print_precision_id, constants::initial_print_precision);
    }
};