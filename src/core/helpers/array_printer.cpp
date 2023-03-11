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
#include <string>
#include <vector>

#include "conversion.h"
#include <uni_algo/conv.h>
#include <numeric>

namespace kepler {
    bool all_elements_are_scalars(const Array& arr) {
        return std::all_of(arr.data.begin(), arr.data.end(), [&](const Array::element_type& element){
            return holds_alternative<Array>(element) && get<Array>(element).is_simple_scalar();
        });
    }

    std::vector<int> dims(const std::vector<int>& shape) {
        std::vector<int> result;

        for(int i = 0; i < shape.size() - 1; ++i) {
            result.emplace_back(std::accumulate(shape.rbegin() + i + 1, shape.rend(), 1, std::multiplies<int>()));
        }

        return result;
    }

    std::vector<int> offsets(const std::vector<int>& shape) {
        std::vector<int> result;

        for(int i = 2; i < shape.size() - 2; ++i) {
            result.emplace_back(std::accumulate(shape.rbegin() + i, shape.rend(), 1, std::multiplies<int>()));
        }

        return result;
    }

    // https://stackoverflow.com/questions/5607589/right-way-to-split-an-stdstring-into-a-vectorstring
    std::vector<std::string> split(const std::string& text, char delim) {
        std::string line;
        std::vector<std::string> vec;
        std::stringstream ss(text);
        while(std::getline(ss, line, delim)) {
            vec.push_back(line);
        }
        return vec;
    }

    std::vector<std::u32string> split(const std::u32string& text, char32_t delim) {
        std::vector<std::u32string> vec;

        if(text.empty()) {
            return vec;
        }

        int start = 0;
        int cursor = start;

        while(cursor <= text.size() - 1) {
            auto s = text.size() - 1;
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

    int max_length_contiguous_segment(const std::u32string& str) {
        std::vector<std::u32string> segments = split(str, U'\n');
        int max_length = 0;
        for(auto& element : segments) {
            if(element.length() > max_length) {
                max_length = element.length();
            }
        }
        return max_length;
    }




    std::u32string block_concat(std::u32string left, std::u32string right) {
        std::vector<std::u32string> l_segments = split(left, U'\n');
        std::vector<std::u32string> r_segments = split(right, U'\n');

        std::u32string result;

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

    std::u32string block_prepend(std::u32string str, char32_t val) {
        std::vector<std::u32string> delimited = split(str, U'\n');
        std::u32string result;
        for(auto& substr : delimited) {
            result += val + substr + U'\n';
        }
        result.pop_back();
        return result;
    }

    std::u32string block_append(std::u32string str, char32_t val) {
        std::vector<std::u32string> delimited = split(str, U'\n');
        std::u32string result;
        for(auto& substr : delimited) {
            result += substr + val + U'\n';
        }
        result.pop_back();
        return result;
    }


    std::u32string box(const std::u32string& str, int width, int height) {
        std::vector<std::u32string> lines = split(str, U'\n');
        for(auto& line : lines) {
            line.insert(0, std::u32string(width - line.size(), U' '));
        }
        for(int i = lines.size(); i < height; ++i) {
            lines.emplace_back(std::u32string(width, U' '));
        }

        std::u32string result;
        for(auto& line : lines) {
            result += line + U'\n';
        }
        result.pop_back();
        return result;
    }


    std::u32string block_join(char32_t separator, const std::vector<std::u32string>& blocks) {
        if(blocks.empty()) {
            return U"";
        }

        std::u32string result = blocks[0];
        for(int i = 1; i < blocks.size(); ++i) {
            result = block_concat(block_append(result, separator), blocks[i]);
        }
        return result;
    }

    std::u32string frame_matrix(const std::vector<std::u32string>& strings, const std::vector<int>& widths, int height) {
        int num_cols = widths.size();
        int num_rows = strings.size() / num_cols;

        std::vector<std::u32string> boxes(strings.size());
        for(int i = 0; i < strings.size(); ++i) {
            boxes.at(i) = box(strings[i], widths[i % num_cols], height);
        }

        std::vector<std::u32string> rows;
        for(int i = 0; i < num_rows; ++i) {
            std::u32string row = block_join(U'│', {boxes.begin() + i * widths.size(), boxes.begin() + (i + 1) * widths.size()});
            row = block_prepend(row, U'│');
            row = block_append(row, U'│');
            rows.emplace_back(std::move(row));
        }

        std::u32string ref_line = split(rows[0], U'\n')[0];
        std::u32string top = U"┌";
        for(int i = 1; i < ref_line.size() - 1; ++i) {
            if(ref_line[i] == U'│') {
                top += U'┬';
            } else {
                top += U'─';
            }
        }
        top += U'┐';
        std::u32string intermediate = U'├' + top.substr(1, top.size() - 2) + U'┤';
        std::replace(intermediate.begin(), intermediate.end(), U'┬', U'┼');
        std::u32string bot = U'└' + top.substr(1, top.size() - 2) + U'┘';
        std::replace(bot.begin(), bot.end(), U'┬', U'┴');

        std::vector<std::u32string> lines{top};
        for(auto& row : rows) {
            std::vector<std::u32string> delimited = split(row, U'\n');
            std::copy(delimited.begin(), delimited.end(), std::back_inserter(lines));
            lines.emplace_back(intermediate);
        }
        lines.back() = bot;

        std::u32string result;
        for(auto& str : lines) {
            result += str + U'\n';
        }
        result.pop_back();

        return result;
    }

    std::string ArrayPrinter::operator()(const std::u32string &element) {
        return uni::utf32to8(element);
    }

    std::string ArrayPrinter::operator()(const Number& element) {
        return number_to_string(element);
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
            std::string result;
            for(int i = 0; i < strings.size(); ++i) {
                for(auto& d : cumulative_dims) {
                    if(i != 0 && i % d == 0) {
                        result += "\n";
                    }
                }
                result += strings[i];

                if(i < strings.size() - 1) {
                    result += " ";
                }
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
            std::vector<std::u32string> strings;
            int last_dim = array.shape.back();
            std::vector<int> widths(last_dim, 0);
            int max_height = 0;

            for(int i = 0; i < array.data.size(); ++i) {
                std::u32string str = uni::utf8to32u(std::visit(*this, array.data[i]));
                int s_height = 1 + std::count(str.begin(), str.end(), '\n');
                max_height = std::max(max_height, s_height);

                // HERE!
                int s_width = max_length_contiguous_segment(str);
                widths[i%last_dim] = std::max(widths[i%last_dim], s_width);
                strings.emplace_back(str);
            }

            int matrix_size = array.shape[array.shape.size() - 2] * array.shape[array.shape.size() - 1];
            int n_matrices = std::accumulate(array.shape.rbegin(), array.shape.rend(), 1, std::multiplies<int>()) / matrix_size;
            std::vector<std::u32string> matrices;
            for(int i = 0; i < n_matrices; ++i) {
                matrices.emplace_back(frame_matrix({strings.begin() + i * matrix_size, strings.begin() + (i + 1) * matrix_size}, widths, max_height));
            }

            std::vector<int> off = offsets(array.shape);
            std::u32string result;
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