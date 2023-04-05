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
#include <string>
#include "core/datatypes.h"

namespace kepler {
    // Forward declaration of Array to avoid circular dependency.
    struct Array;

    /**
     * Converts an Array to a string.
     * Intended to be used with std::visit.
     *
     * @param array The Array to convert.
     * @param precision The number of decimal places to use when printing numbers.
     * @return The string representation of the Array.
     */
    struct ArrayPrinter {

        // The number of decimal places to use when printing numbers.
        int precision;

        /**
         * Creates a new ArrayPrinter.
         * @param precision The number of decimal places to use when printing numbers.
         */
        explicit ArrayPrinter(int precision);

        /**
         * Converts a String (std::u32string) to a std::string.
         */
        std::string operator()(const String& element) const;

        /**
         * Converts a Number (std::complex<double>) to a std::string.
         */
        std::string operator()(const Number& element) const;

        /**
         * Converts an Array to a std::string.
         */
        std::string operator()(const Array& array) const;

    private:

        /**
         * Returns true if all elements in the Array are Arrays themselves which are scalar.
         */
        static bool all_elements_are_scalars(const Array& array);

        /**
         * Returns the a list of sizes of each dimension of the shape, reversed.
         *
         * Start at one before end of the shape input. For each element, multiply all
         * elements to the right of it and insert the result in the result vector.
         *
         * For example, if the shape is [3, 4, 2, 10], the result will be [10, 20, 80].
         * @param shape The shape vector of the Array.
         * @return The accumulated dimensions.
        */
        static std::vector<unsigned int> dims(const std::vector<unsigned int>& shape);

        /**
         * Returns the a list of offsets of each dimension of the shape, reversed.
         *
         * Start at the two before end of the shape input. For each element, multiply all
         * elements to the right of it and insert the result in the result vector.
         *
         * For example, if the shape is [3, 5, 9, 10, 6], the result will be [1, 1, 9].
         * @param shape The shape vector of the Array.
         * @return The accumulated dimensions.
        */
        static std::vector<unsigned int> offsets(const std::vector<unsigned int>& shape);

        /**
         * Splits a String into a vector of Strings by a delimiter.
         * @param text Original string.
         * @param delim Delimiter to split by.
         * @return A vector of delimited strings.
         */
        static std::vector<String> split(const String& text, char32_t delim);

        /**
         * Returns the maximum length of a contiguous segment of a String.
         *
         * A contiguous segment is a sequence of characters that are not a newline.
         * @param str String to find the maximum length of a contiguous segment in.
         * @return The maximum length of a contiguous segment.
         */
        static unsigned int max_length_contiguous_segment(const String& str);

        /**
         * Concatenates two Strings by appending contiguous segments of one String to the other.
         *
         * Specifically, the Strings are split by newlines, and the contiguous segments are
         * zipped between the splits. The result is a String where each contiguous segment
         * is the concatenation of the corresponding contiguous segments of the two input Strings.
         *
         * @param left One of two Strings to concatenate.
         * @param right Second of two Strings to concatenate.
         * @return The concatenated String.
         */
        static String concatenate_block(const String& left, const String& right);

        /**
         * Splits the given string by newlines, prepends the given value to each segment,
         * and concatenates all segments.
         *
         * @param str The String to modify.
         * @param val The value to prepend to each segment.
         * @return The resulting String.
         */
        static String prepend_block(const String& str, char32_t val);

        /**
         * Splits the given string by newlines, appends the given value to each segment,
         * and concatenates all segments.
         *
         * @param str The String to modify.
         * @param val The value to append to each segment.
         * @return The resulting String.
         */
        static String append_block(const String& str, char32_t val);

        /**
         * Splits the given String by newlines, ensures that each segment is at least the
         * width given, and that there is at least height amount of segments.
         *
         * If a line is not width characters long, it is padded with spaces.
         * If there are not enough lines, empty lines are added.
         *
         * @param str The String containing the lines to box.
         * @param width The desired width.
         * @param height The desired height.
         * @return The box-formatted String
         */
        static String box_string(const String& str, unsigned int width, unsigned int height);

        /**
         * Joins several blocks into one String by concatenating them
         * (side-by-side) and inserting a separator between each block.
         *
         * @param separator The separator to insert between each block.
         * @param blocks The blocks to join.
         * @return The String of joined blocks.
         */
        static String join_block(char32_t separator, const std::vector<String>& blocks);

        /**
         * Frames a matrix by adding box-drawing characters around it.
         *
         * @param strings The Strings which make up the matrix.
         * @param widths The widths of each column.
         * @param height The height of the matrix.
         * @return The framed matrix in String format.
         */
        static String frame_matrix(const std::vector<String>& strings, const std::vector<unsigned int>& widths, unsigned int height);
    };
};