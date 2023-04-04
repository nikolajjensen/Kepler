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
#include "core/error.h"

namespace kepler {
    Operation::Operation(SymbolTable* symbol_table_) : symbol_table(symbol_table_) {}

    Array Operation::operator()(const Array& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const Number& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const std::u32string& omega) {
        throw kepler::Error(DomainError);
    }



    Array Operation::operator()(const Array& alpha, const Array& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const Array& alpha, const Number& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const Array& alpha, const std::u32string& omega) {
        throw kepler::Error(DomainError);
    }



    Array Operation::operator()(const Number& alpha, const Number& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const Number& alpha, const Array& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const Number& alpha, const std::u32string& omega) {
        throw kepler::Error(DomainError);
    }



    Array Operation::operator()(const std::u32string& alpha, const std::u32string& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const std::u32string& alpha, const Number& omega) {
        throw kepler::Error(DomainError);
    }

    Array Operation::operator()(const std::u32string& alpha, const Array& omega) {
        throw kepler::Error(DomainError);
    }


    Array Operation::operator()(const Char &alpha, const Char &omega) {
        throw kepler::Error(DomainError);
    }
};