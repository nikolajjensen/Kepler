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
#include <optional>
#include "core/array.h"
#include "core/evaluation/ast.h"

namespace kepler {

    /**
     * Defines the different types of symbols.
     */
    enum SymbolType {
        FunctionSymbol,
        VariableSymbol
    };

    /**
     * A Symbol is a variable or function that can be stored in the SymbolTable.
     */
    struct Symbol {
        // A Symbol can contain only Array or Operation_ptr, or nothing at all.
        using content_type = std::optional<std::variant<Array, Operation_ptr>>;

        content_type content;
        SymbolType type;

        /**
         * Creates a new Symbol with the given type and content.
         * @param type_ The type of the symbol.
         * @param content_ The content of the symbol.
         */
        Symbol(SymbolType type_, std::variant<Array, Operation_ptr> content_) : type(type_), content(content_) {}

        /**
         * Creates a new Symbol with the given type and no content.
         * @param type_ The type of the symbol.
         */
        explicit Symbol(SymbolType type_) : type(type_), content(std::nullopt) {}
    };
};