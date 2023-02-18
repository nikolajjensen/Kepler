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
#include "symbol_table.h"
#include "../characters.h"
#include "../array.h"

namespace kepler {
    void config::set_initial_values(SymbolTable &symbol_table) {
        symbol_table.set(
                {characters::quad, characters::C, characters::T},
                {
                    {VariableToken, Array::vectorOf(List<Number>{initial_comparison_tolerance})}
                });

        symbol_table.set(
                {characters::quad, characters::R, characters::L},
                {
                        {VariableToken, Array::vectorOf(List<Number>{initial_random_link})}
                });

        symbol_table.set(
                {characters::quad, characters::P, characters::P},
                {
                        {VariableToken, Array::vectorOf(List<Number>{initial_print_precision})}
                });


        symbol_table.set(
                {characters::quad, characters::I, characters::O},
                {
                        {VariableToken, Array::vectorOf(List<Number>{initial_index_origin})}
                });

        symbol_table.set(
                {characters::quad, characters::L, characters::X},
                initial_latent_expression);
    }
};