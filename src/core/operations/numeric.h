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
#include "../env/session.h"

namespace kepler::numeric_operations {
    bool in_same_half_plane(const Number& lhs, const Number& rhs);

    bool equals(const Number&, const Number&);
    Number direction(const Number&);
    bool greater_than(const Number&, const Number&);
    bool less_than(const Number&, const Number&);
    Number negation(const Number&);
    Number magnitude(const Number&);
    bool in_open_interval_between(const Number& n, const Number& start, const Number& end);
    bool in_closed_interval_between(const Number& n, const Number& start, const Number& end);
    Number larger_magnitude(const Number&, const Number&);
    Number distance_between(const Number&, const Number&);
    bool tolerantly_equal_within(const Number& n, const Number& to, const Number& tolerance);
    Number floor(const Number& n);
    bool integral_within(const Number& n, const Number& tolerance);
    bool near_integer(const Number& n);
    Number integer_nearest_to(const Number& n);
    bool near_boolean(const Number& n);
    bool real_within(const Number&, const Number&);
    bool near_real(const Number& n);
};