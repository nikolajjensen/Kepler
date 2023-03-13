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

    enum SymbolType {
        FunctionSymbol,
        VariableSymbol
    };

    struct Symbol {
        using content_type = std::optional<std::variant<Array, Operation_ptr>>;

        content_type content;
        SymbolType type;

        Symbol(SymbolType type_, std::variant<Array, Operation_ptr> content_) : type(type_), content(content_) {}
        explicit Symbol(SymbolType type_) : type(type_), content(std::nullopt) {}
    };
};