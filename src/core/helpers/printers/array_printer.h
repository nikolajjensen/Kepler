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
#include <iostream>
#include <uni_algo/conv.h>
#include "core/array.h"

namespace kepler::helpers {
    struct ArrayPrinter {
        std::ostream& stream;
        int print_precision;

        explicit ArrayPrinter(std::ostream& stream_, int print_precision_ = -1) : stream(stream_), print_precision(print_precision_) {}

        void operator()(const Array& array) const {
            //stream << std::setprecision(print_precision);

            if(array.shape_list.size() == 0) {
                boost::apply_visitor(*this, array.ravel_list[0]);
            } if(array.shape_list.size() == 1) {
                for(int e = 0; e < array.shape_list[0]; ++e) {
                    boost::apply_visitor(*this, array.ravel_list[e]);
                    if(e < array.shape_list[0] - 1) {
                        stream << " ";
                    }
                }
            } else if(array.shape_list.size() == 2) {
                for(int row = 0; row < array.shape_list[0]; ++row) {
                    for(int col = 0; col < array.shape_list[1]; ++col) {
                        boost::apply_visitor(*this, array.ravel_list[row * array.shape_list[0] + col]);
                        if(col < array.shape_list[1] - 1) {
                            stream << " ";
                        }
                    }
                }
            }
        }

        void operator()(const Char& c) const {
            stream << uni::utf32to8(StringUTF32(1, c));
        }

        void operator()(const Number& n) const {
            stream << number_to_string(n, print_precision);
        }
    };

    struct ArrayDebugPrinter {
        std::ostream& stream;

        explicit ArrayDebugPrinter(std::ostream& stream_) : stream(stream_) {}

        void operator()(const Array& array) const {
            stream << "<Array>[";
            if(array.shape_list.size() == 0) {
                boost::apply_visitor(*this, array.ravel_list[0]);
            } if(array.shape_list.size() == 1) {
                for(int e = 0; e < array.shape_list[0]; ++e) {
                    boost::apply_visitor(*this, array.ravel_list[e]);
                    if(e < array.shape_list[0] - 1) {
                        stream << " ";
                    }
                }
            } else if(array.shape_list.size() == 2) {
                for(int row = 0; row < array.shape_list[0]; ++row) {
                    for(int col = 0; col < array.shape_list[1]; ++col) {
                        boost::apply_visitor(*this, array.ravel_list[row * array.shape_list[0] + col]);
                        if(col < array.shape_list[1] - 1) {
                            stream << " ";
                        }
                    }
                }
            }
            stream << "]";
        }

        void operator()(const Char& c) const {
            stream << uni::utf32to8(StringUTF32(1, c));
        }

        void operator()(const Number& num) const {
            stream << number_to_string(num);
        }
    };
};