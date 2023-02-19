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
#include "numeric.h"
#include "../env/config.h"
#include "../env/session.h"

namespace kepler {
    bool numeric_operations::in_same_half_plane(const Number &lhs, const Number &rhs) {
        if(lhs.real() > 0 && rhs.real() > 0) return true;
        if(lhs.real() < 0 && rhs.real() < 0) return true;
        if(lhs.imag() > 0 && rhs.imag() > 0) return true;
        if(lhs.imag() < 0 && rhs.imag() < 0) return true;

        return false;
    }



    bool numeric_operations::equals(const Number &lhs, const Number &rhs) {
        return lhs == rhs;
    }

    Number numeric_operations::direction(const Number &num) {
        return (num == 0.0) ? num : num / abs(num);
    }

    bool numeric_operations::greater_than(const Number &lhs, const Number &rhs) {
        return lhs.real() > rhs.real();
    }

    bool numeric_operations::less_than(const Number &lhs, const Number &rhs) {
        return greater_than(rhs, lhs);
    }

    Number numeric_operations::negation(const Number &num) {
        return 0.0 - num;
    }

    Number numeric_operations::magnitude(const Number &num) {
        return abs(num);
    }

    bool numeric_operations::in_open_interval_between(const Number &n, const Number &start, const Number &end) {
        return greater_than(n, start) && less_than(n, end);
    }

    bool numeric_operations::in_closed_interval_between(const Number &n, const Number &start, const Number &end) {
        return equals(n, start) || equals(n, end) || in_open_interval_between(n, start, end);
    }

    Number numeric_operations::larger_magnitude(const Number &lhs, const Number &rhs) {
        Number lhs_mag = magnitude(lhs);
        Number rhs_mag = magnitude(rhs);
        return greater_than(lhs_mag, rhs_mag) ? lhs_mag : rhs_mag;
    }

    Number numeric_operations::distance_between(const Number &lhs, const Number &rhs) {
        return magnitude(lhs - rhs);
    }

    bool numeric_operations::tolerantly_equal_within(const Number &n, const Number &to, const Number &tolerance) {
        if(equals(n, to)) return true;
        if(!in_same_half_plane(n, to)) return false;

        Number distance = distance_between(n, to);
        Number larger_mag = larger_magnitude(n, to);
        return (less_than(distance, tolerance * larger_mag) || equals(distance, tolerance * larger_mag));
    }

    Number numeric_operations::floor(const Number &n) {
        return {std::floor(n.real()), std::floor(n.imag())};
    }

    bool numeric_operations::integral_within(const Number &n, const Number &tolerance) {
        return less_than(floor(n) + tolerance, n) || less_than(floor(n + 1.0) - tolerance, n);
    }

    bool numeric_operations::near_integer(const Number &n) {
        return integral_within(n, config::integer_tolerance);
    }

    Number numeric_operations::integer_nearest_to(const Number &n) {
        return floor(n);
    }

    bool numeric_operations::near_boolean(const Number &n) {
        Number nearest_int = integer_nearest_to(n);
        return (nearest_int == 0.0 || nearest_int == 1.0);
    }

    bool numeric_operations::real_within(const Number &n, const Number &tolerance) {
        Number r_mag = magnitude(n.real());
        Number i_mag = magnitude(n.imag());
        return (less_than(i_mag, tolerance) || equals(i_mag, tolerance)) || (less_than(i_mag, tolerance * r_mag) || equals(i_mag, tolerance * r_mag));
    }

    bool numeric_operations::near_real(const Number &n) {
        return real_within(n, config::real_tolerance);
    }
};