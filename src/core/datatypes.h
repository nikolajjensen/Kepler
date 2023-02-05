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
#include <ostream>
#include <sstream>
#include <iostream>

#include <uni_algo/conv.h>
#include <boost/optional.hpp>

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
        double realScalar;
        boost::optional<double> exponent;
        boost::optional<double> imaginaryScalar;

        Number(const List<Char>& list);

        Number(const double realScalar_,
               const boost::optional<double> exponent_ = boost::none,
               const boost::optional<double> imaginaryScalar_ = boost::none);

        Number& operator=(const double& num);

        static Number numeric_limit_max() {
            return std::numeric_limits<double>::max();
        }

        static Number numeric_limit_min() {
            return std::numeric_limits<double>::min();
        }

        void conjugate() {
            if(imaginaryScalar) {
                imaginaryScalar.get() *= -1;
            }
        }

        StringUTF8 to_string() const;

        static StringUTF8 double_to_string(const double& num) ;

        friend std::ostream& operator<<(std::ostream& os, const Number& number) {
            return os << number.to_string();
        }

        friend Number operator-(int lhs, const Number& rhs) {
            Number result = rhs;
            result.realScalar *= -1;
            return result;
        }

        friend bool operator==(const Number& lhs, const Number& rhs) {
            bool exponent_equal = (lhs.exponent && rhs.exponent && lhs.exponent == rhs.exponent) || (!lhs.exponent && !rhs.exponent);
            bool complex_equal = (lhs.imaginaryScalar && rhs.imaginaryScalar && lhs.imaginaryScalar == rhs.imaginaryScalar) || (!lhs.imaginaryScalar && !rhs.imaginaryScalar);

            return lhs.realScalar == rhs.realScalar && exponent_equal && complex_equal;
        }
    };
};