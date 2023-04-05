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

    /**
     * The SymbolTable is used to map identifiers to their values.
     *
     * A SymbolTable can have a parent SymbolTable, which is used to
     * look up identifiers which are not defined in the current SymbolTable.
     */
    class SymbolTable {
    private:
        std::map<String, Symbol*> table;
        SymbolTable* parent;

        /**
         * Looks up the given identifier in the SymbolTable.
         *
         * If the id is not found in the current SymbolTable,
         * then it will be looked up in the parent, if it exists.
         *
         * If the id does not exist in the current SymbolTable or its parent,
         * an kepler::Error will be thrown.
         *
         * @param id The identifier to look up.
         * @return The Symbol associated with the identifier.
         * @throws kepler::Error if the id is not defined.
         */
        [[nodiscard]] const Symbol& lookup(const String& id) const;

    public:
        /**
         * Creates a new SymbolTable.
         */
        SymbolTable();

        /**
         * Creates a new SymbolTable with parent reference.
         *
         * @param parent The parent SymbolTable.
         */
        explicit SymbolTable(SymbolTable* parent);

        /**
         * Destroys the SymbolTable.
         *
         * Will also delete every symbol within the table.
         */
        ~SymbolTable();

        /**
         * "Attaches" a parent SymbolTable to the current SymbolTable.
         *
         * This will set the parent reference to the new 'parent'. The previous parent is not deleted.
         *
         * @param parent The parent SymbolTable.
         */
        void attach_parent(SymbolTable* parent);

        /**
         * Returns true if the id is defined in the SymbolTable.
         *
         * If the id is not defined in the SymbolTable, its parent (if it exists) will be checked.
         */
        [[nodiscard]] bool contains(const String& id) const;

        /**
         * Returns the value associated with the given id.
         *
         * Note that if the id is not defined, then a kepler::Error will be thrown.
         *
         * @tparam T The type expected to be stored i the table for the given id.
         * @param id The id to look up.
         * @return The value associated with the id.
         * @throws kepler::Error if the id is not defined.
         */
        template <typename T>
        const T& get(const String& id) const {
            const Symbol& symbol = lookup(id);

            if(!symbol.content.has_value()) {
                throw kepler::Error(DefinitionError, "ID '" + uni::utf32to8(id) + "' is defined, but has no value.");
            }

            if(!std::holds_alternative<T>(symbol.content.value())) {
                throw kepler::Error(DefinitionError, "ID '" + uni::utf32to8(id) + "' has a value, but it is not the one requested.");
            }

            return std::get<T>(symbol.content.value());
        }

        /**
         * Returns the type of the value associated with the given id.
         *
         * Note that if the id is not defined, then a kepler::Error will be thrown.
         *
         * @param id The id to look up.
         * @return The type of the value associated with the id.
         * @throws kepler::Error if the id is not defined.
         */
        [[nodiscard]] SymbolType get_type(const String& id) const;

        /**
         * Sets the value associated with the given id.
         *
         * If locally_only is set, then the value will be set in the current SymbolTable,
         * regardless of whether the id is defined in the parent SymbolTable.
         *
         * @param id The id to set the value for.
         * @param value The Array to set as value.
         * @param locally_only Whether to set the value locally or not.
         */
        void set(const String& id, const Array& value, bool locally_only = false);

        /**
         * Sets the value associated with the given id.
         *
         * If locally_only is set, then the value will be set in the current SymbolTable,
         * regardless of whether the id is defined in the parent SymbolTable.
         *
         * @param id The id to set the value for.
         * @param value The Operation_ptr to set as value.
         * @param locally_only Whether to set the value locally or not.
         */
        void set(const String& id, const Operation_ptr& value, bool locally_only = false);

        /**
         * Sets the value associated with the given id.
         *
         * If locally_only is set, then the value will be set in the current SymbolTable,
         * regardless of whether the id is defined in the parent SymbolTable.
         *
         * @param id The id to set the value for.
         * @param value The Number to set as value.
         * @param locally_only Whether to set the value locally or not.
         */
        void set(const String& id, const Number& value, bool locally_only = false);

        /**
         * If the current SymbolTable contains the id, then the value is
         * deleted and freed from memory. If 'locally_only' is set to false
         * and the id was not found in the current SymbolTable, the parent
         * will be checked and the value will be removed from there.
         *
         * No exceptions are thrown if the id is not found.
         *
         * @param id The id to remove.
         * @param locally_only Whether to remove the value locally or not.
         */
        void remove(const String& id, bool locally_only = false);

        /**
         * Binds the given id to a function type.
         *
         * This does not set any value to the id, thus performing
         * a lookup will fail.
         *
         * @param id The id to bind to a function type.
         */
        void bind_function(const String& id);

        /**
         * Clears the SymbolTable such that no ids are defined.
         *
         * Will also delete every symbol within the table.
         */
        void clear();

        /**
         * Inserts the default system parameters into the SymbolTable.
         *
         * These include '⎕IO' and '⎕PP'.
         */
        void insert_system_parameters();
    };
};