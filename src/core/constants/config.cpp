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
#include "config.h"
#include "core/symbol_table.h"
#include "core/constants/literals.h"
#include "core/array.h"

namespace kepler {
    void constants::set_initial_values(SymbolTable &symbol_table) {
        symbol_table.set(
                {constants::quad, constants::C, constants::T},
                {
                    {VariableToken, Array::vectorOf(List<Number>{initial_comparison_tolerance})}
                });

        symbol_table.set(
                {constants::quad, constants::R, constants::L},
                {
                        {VariableToken, Array::vectorOf(List<Number>{initial_random_link})}
                });

        symbol_table.set(
                {constants::quad, constants::P, constants::P},
                {
                        {VariableToken, Array::vectorOf(List<Number>{initial_print_precision})}
                });


        symbol_table.set(
                {constants::quad, constants::I, constants::O},
                {
                        {VariableToken, Array::vectorOf(List<Number>{initial_index_origin})}
                });

        symbol_table.set(
                {constants::quad, constants::L, constants::X},
                initial_latent_expression);
    }

    std::string constants::function_definition_prompt(int line_number) {
        if(line_number >= 10) {
            return "[" + std::to_string(line_number) + "] > ";
        }
        return "[" + std::to_string(line_number) + "]  > ";
    }
};