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
#include "core/datatypes.h"
#include "core/array.h"
#include <memory>

namespace kepler {
    struct SymbolTable;

    struct Operation {
    protected:
        std::shared_ptr<Operation> op;
        SymbolTable* symbol_table;

        virtual bool is_configured() const;

    public:
        Operation();
        Operation(std::shared_ptr<Operation> op);
        Operation(SymbolTable* symbol_table);

        virtual Array operator()(const Array& omega);

        virtual Array operator()(const Array& alpha, const Array& omega);

        virtual Number operator()(const Number& omega);

        virtual Number operator()(const Number& alpha, const Number& omega);

        virtual std::u32string operator()(const std::u32string& omega);

        virtual std::u32string operator()(const std::u32string& alpha, const std::u32string& omega);
    };
};