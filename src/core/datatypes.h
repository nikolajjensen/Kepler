//
// Copyright 2022 Nikolaj Banke Jensen.
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

#include <vector>
#include <string>
#include <limits>
#include <ostream>
#include <sstream>
#include <iostream>

#include <uni_algo/conv.h>
#include <boost/optional.hpp>
#include <cmath>

namespace kepler {
    template<typename T>
    using List = std::vector<T>;

    using Char = char32_t;
    using Double = double;
    using Integer = int;
    using UnsignedInteger = unsigned int;

    using StringUTF8 = std::string;
    using StringUTF32 = std::u32string;
    using Boolean = bool;

    class Number {
    public:
        double real_scalar;
        boost::optional<double> imaginary_scalar;

        Number(const List<Char>& list);

        Number(double real_scalar_,
               boost::optional<double> real_exponent_ = boost::none,
               boost::optional<double> imaginary_scalar_ = boost::none,
               boost::optional<double> imaginary_exponent_ = boost::none);

        Number& operator=(const double& num);

        static Number numeric_limit_max() {
            return std::numeric_limits<double>::max();
        }

        static Number numeric_limit_min() {
            return std::numeric_limits<double>::min();
        }

        static double& apply_scientific_notation(double& input, double& exponent) {
            return input *= pow(10.0, exponent);
        }

        void conjugate() {
            if(imaginary_scalar) {
                imaginary_scalar.get() *= -1;
            }
        }

        double magnitude() {
            return 0;
        }

        StringUTF8 to_string() const;

        static StringUTF8 double_to_string(const double& num) ;

        friend std::ostream& operator<<(std::ostream& os, const Number& number) {
            return os << number.to_string();
        }

        friend Number operator-(int lhs, const Number& rhs) {
            Number result = rhs;
            result.real_scalar = lhs - result.real_scalar;
            if(rhs.imaginary_scalar) {
                result.imaginary_scalar = lhs - result.imaginary_scalar.get();
            }
            return result;
        }

        friend bool operator==(double lhs, const Number& rhs) {
            return lhs == rhs.real_scalar;
        }

        friend bool operator==(const Number& lhs, const Number& rhs) {
            bool complex_equal = (lhs.imaginary_scalar && rhs.imaginary_scalar && lhs.imaginary_scalar == rhs.imaginary_scalar) || (!lhs.imaginary_scalar && !rhs.imaginary_scalar);

            return lhs.real_scalar == rhs.real_scalar && complex_equal;
        }
    };
};