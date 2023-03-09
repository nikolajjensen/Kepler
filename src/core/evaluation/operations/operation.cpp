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

#include "operation.h"

namespace kepler {
    Operation::Operation() : op(nullptr), symbol_table(nullptr) {}
    Operation::Operation(std::shared_ptr<Operation> op_) : op(op_), symbol_table(nullptr) {}
    Operation::Operation(SymbolTable* symbol_table_) : op(nullptr), symbol_table(symbol_table_) {}

    bool Operation::is_configured() const {
        return op != nullptr && op->is_configured();
    }

    Array Operation::operator()(const Array& omega) {
        throw std::runtime_error("This operation does not support monadic array as argument.");
    }

    Array Operation::operator()(const Array& alpha, const Array& omega) {
        throw std::runtime_error("This operation does not support dyadic arrays as arguments.");
    }

    Number Operation::operator()(const Number& omega) {
        throw std::runtime_error("This operation does not support monadic number as argument.");
    }

    Number Operation::operator()(const Number& alpha, const Number& omega) {
        throw std::runtime_error("This operation does not support dyadic numbers as arguments.");
    }

    std::u32string Operation::operator()(const std::u32string& omega) {
        throw std::runtime_error("This operation does not support monadic string as argument.");
    }

    std::u32string Operation::operator()(const std::u32string& alpha, const std::u32string& omega) {
        throw std::runtime_error("This operation does not support dyadic strings as arguments.");
    }
};