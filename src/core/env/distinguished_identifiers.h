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
#include "../datatypes.h"
#include "../characters.h"

namespace kepler {
    namespace distinguished_identifiers {
        const List<Char> CT = {characters::quad, characters::C, characters::T};
        const List<Char> RL = {characters::quad, characters::R, characters::L};
        const List<Char> PP = {characters::quad, characters::P, characters::P};
        const List<Char> IO = {characters::quad, characters::I, characters::O};
        const List<Char> LX = {characters::quad, characters::L, characters::X};
    };
};