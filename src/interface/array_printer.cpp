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

#include "core/array.h"
#include "array_printer.h"
#include "core/helpers.h"
#include <string>
#include <vector>
#include <algorithm>

#include "conversion.h"
#include <uni_algo/conv.h>
#include <numeric>

namespace kepler {
    ArrayPrinter::ArrayPrinter(int precision_) : precision(precision_) {}

    bool all_elements_are_scalars(const Array& arr) {
        return std::all_of(arr.data.begin(), arr.data.end(), [&](const Array::element_type& element){
            return holds_alternative<Array>(element) && get<Array>(element).is_simple_scalar();
        });
    }

    std::vector<int> dims(const std::vector<int>& shape) {
        std::vector<int> result;

        for(int i = 0; i < shape.size() - 1; ++i) {
            result.emplace_back(std::accumulate(shape.end() - 1 - i, shape.end(), 1, std::multiplies<>()));
        }

        return result;
    }

    std::vector<int> offsets(const std::vector<int>& shape) {
        std::vector<int> result;

        for(int i = 2; i < shape.size() - 2; ++i) {
            result.emplace_back(std::accumulate(shape.rbegin() + i, shape.rend(), 1, std::multiplies<>()));
        }

        return result;
    }

    // https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
    std::vector<String> split(const String& text, char32_t delim) {
        std::vector<String> vec;

        if(text.empty()) {
            return vec;
        }

        int start = 0;
        int cursor = start;

        while(cursor <= text.size() - 1) {
            if(text[cursor] == delim) {
                vec.emplace_back(text.substr(start, cursor - start));
                start = cursor + 1;
            }
            cursor++;
        }
        if(start < cursor) {
            vec.emplace_back(text.substr(start, cursor - start));
        }

        return vec;
    }

    int max_length_contiguous_segment(const String& str) {
        std::vector<String> segments = split(str, U'\n');
        int max_length = 0;
        for(auto& element : segments) {
            if(element.length() > max_length) {
                max_length = element.length();
            }
        }
        return max_length;
    }




    String block_concat(String left, String right) {
        std::vector<String> l_segments = split(left, U'\n');
        std::vector<String> r_segments = split(right, U'\n');

        String result;

        if(l_segments.empty()) {
            return result;
        }

        for(int i = 0; i < l_segments.size(); ++i) {
            result += l_segments[i] + r_segments[i];
            result += U'\n';
        }
        result.pop_back();

        return result;
    }

    String block_prepend(String str, char32_t val) {
        std::vector<String> delimited = split(str, U'\n');
        String result;
        for(auto& substr : delimited) {
            result += val + substr + U'\n';
        }
        result.pop_back();
        return result;
    }

    String block_append(String str, char32_t val) {
        std::vector<String> delimited = split(str, U'\n');
        String result;
        for(auto& substr : delimited) {
            result += substr + val + U'\n';
        }
        result.pop_back();
        return result;
    }


    String box(const String& str, int width, int height) {
        std::vector<String> lines = split(str, U'\n');
        for(auto& line : lines) {
            line += String(width - line.size(), U' ');
        }
        for(int i = lines.size(); i < height; ++i) {
            lines.emplace_back(String(width, U' '));
        }

        String result;
        for(auto& line : lines) {
            result += line + U'\n';
        }
        result.pop_back();
        return result;
    }


    String block_join(char32_t separator, const std::vector<String>& blocks) {
        if(blocks.empty()) {
            return U"";
        }

        String result = blocks[0];
        for(int i = 1; i < blocks.size(); ++i) {
            result = block_concat(block_append(result, separator), blocks[i]);
        }
        return result;
    }

    String frame_matrix(const std::vector<String>& strings, const std::vector<int>& widths, int height) {
        int num_cols = widths.size();
        int num_rows = strings.size() / num_cols;

        std::vector<String> boxes(strings.size());
        for(int i = 0; i < strings.size(); ++i) {
            boxes.at(i) = box(strings[i], widths[i % num_cols], height);
        }

        std::vector<String> rows;
        for(int i = 0; i < num_rows; ++i) {
            String row = block_join(U'│', {boxes.begin() + i * widths.size(), boxes.begin() + (i + 1) * widths.size()});
            row = block_prepend(row, U'│');
            row = block_append(row, U'│');
            rows.emplace_back(std::move(row));
        }

        String ref_line = split(rows[0], U'\n')[0];
        String top = U"┌";
        for(int i = 1; i < ref_line.size() - 1; ++i) {
            if(ref_line[i] == U'│') {
                top += U'┬';
            } else {
                top += U'─';
            }
        }
        top += U'┐';
        String intermediate = U'├' + top.substr(1, top.size() - 2) + U'┤';
        std::replace(intermediate.begin(), intermediate.end(), U'┬', U'┼');
        String bot = U'└' + top.substr(1, top.size() - 2) + U'┘';
        std::replace(bot.begin(), bot.end(), U'┬', U'┴');

        std::vector<String> lines{top};
        for(auto& row : rows) {
            std::vector<String> delimited = split(row, U'\n');
            std::copy(delimited.begin(), delimited.end(), std::back_inserter(lines));
            lines.emplace_back(intermediate);
        }
        lines.back() = bot;

        String result;
        for(auto& str : lines) {
            result += str + U'\n';
        }
        result.pop_back();

        return result;
    }

    std::string ArrayPrinter::operator()(const String &element) {
        auto result = element;

        // https://stackoverflow.com/questions/4643512/replace-substring-with-another-substring-c
        size_t index = 0;
        while(true) {
            index = result.find(U"\\n", index);
            if(index == std::string::npos) break;
            result.replace(index, 2, U"\n");
            index += 2;
        }

        return uni::utf32to8(result);
    }

    std::string ArrayPrinter::operator()(const Number& element) {
        return kepler::helpers::number_to_string(element, precision);
    }

    std::string ArrayPrinter::operator()(const Array& array) {
        if(array.empty()) {
            return "";
        }

        if(array.is_simple_scalar()) {
            return std::visit(*this, array.data[0]);
        }

        if(all_elements_are_scalars(array)) {
            // No arrays inside each other, so just make strings of everything.
            std::vector<std::string> strings(array.data.size());
            for(int i = 0; i < array.data.size(); ++i) {
                strings.at(i) = std::visit(*this, array.data[i]);
            }

            if(array.rank() > 1) {

                // Compute max widths for each column.
                std::vector<int> widths(array.shape.back(), 0);
                for(int i = 0; i < strings.size(); ++i) {
                    int index = i % array.shape.back();
                    widths[index] = std::max(widths[index], (int)strings[i].size());
                }

                // Pad every element such that every element in a colum
                // has the same size.
                for(int i = 0; i < strings.size(); ++i) {
                    int index = i % array.shape.back();
                    strings[i].insert(0, std::string(widths[index] - strings[i].size(), ' '));
                }
            }

            std::vector<int> cumulative_dims = dims(array.shape);
            std::string result;// = " ";
            for(int i = 0; i < strings.size(); ++i) {
                for(auto& d : cumulative_dims) {
                    if(i != 0 && i % d == 0) {
                        result += "\n";
                    }
                }
                if(i != 0 && result.back() != '\n') {
                    result += " ";
                }
                result += strings[i];
            }
            return result;
        }

        if(array.rank() == 0) {
            return (*this)(Array{{1, 1}, array.data});
        } else if(array.rank() == 1) {
            std::vector<int> shape = {1};
            shape.reserve(array.shape.size() + 1);
            std::copy(array.shape.begin(), array.shape.end(), std::back_inserter(shape));
            return (*this)(Array{shape, array.data});
        } else {
            std::vector<String> strings;
            int last_dim = array.shape.back();
            std::vector<int> widths(last_dim, 0);
            int max_height = 0;

            for(int i = 0; i < array.data.size(); ++i) {
                String str = uni::utf8to32u(std::visit(*this, array.data[i]));
                int s_height = 1 + std::count(str.begin(), str.end(), '\n');
                max_height = std::max(max_height, s_height);

                int s_width = max_length_contiguous_segment(str);
                widths[i%last_dim] = std::max(widths[i%last_dim], s_width);
                strings.emplace_back(str);
            }

            int matrix_size = array.shape[array.shape.size() - 2] * array.shape[array.shape.size() - 1];
            int n_matrices = std::accumulate(array.shape.rbegin(), array.shape.rend(), 1, std::multiplies<int>()) / matrix_size;
            std::vector<String> matrices;
            for(int i = 0; i < n_matrices; ++i) {
                matrices.emplace_back(frame_matrix({strings.begin() + i * matrix_size, strings.begin() + (i + 1) * matrix_size}, widths, max_height));
            }

            std::vector<int> off = offsets(array.shape);
            String result;
            for(int i = 0; i < matrices.size(); ++i) {
                for(auto& o : off) {
                    if(i != 0 && i % o == 0) {
                        result += U'\n';
                    }
                }
                result += matrices[i] + U' ';
            }

            result.pop_back();
            return uni::utf32to8(result);
        }
    }
};