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

#include "functions.h"
#include "core/error.h"
#include <numeric>
#include <set>
#include <algorithm>
#include <random>
#include <cmath>
#include "core/constants/config.h"
#include "core/symbol_table.h"
#include "core/evaluation/algorithms.h"
#include "core/array.h"

namespace kepler {
    Array Plus::operator()(const Number& alpha, const Number& omega) {
        return {alpha + omega};
    }

    Array Plus::operator()(const Number& omega) {
        return {conj(omega)};
    }

    Array Minus::operator()(const Number& alpha, const Number& omega) {
        return {alpha - omega};
    }

    Array Minus::operator()(const Number& omega) {
        return {omega * -1.0};
    }

    Array Times::operator()(const Number& alpha, const Number& omega) {
        return {alpha * omega};
    }

    Array Times::operator()(const Number& omega) {
        return {(omega == 0.0) ? omega : omega / abs(omega)};
    }

    Array Divide::operator()(const Number& alpha, const Number& omega) {
        if(omega == 0.0) {
            if(alpha != 0.0) {
                throw kepler::error(DomainError, "Division by 0 is undefined.");
            } else {
                return {1};
            }
        }
        return {alpha / omega};
    }

    Array Divide::operator()(const Number& omega) {
        if(omega == 0.0) {
            throw kepler::error(DomainError, "Reciprocal of 0 is undefined.");
        }
        return {1.0 / omega};
    }

    Array Ceiling::operator()(const Number& alpha, const Number& omega) {
        if(alpha.imag() != 0.0 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Maximum of complex numbers is undefined.");
        }

        return {std::max(alpha.real(), omega.real())};
    }

    Array Ceiling::operator()(const Number& omega) {
        return {-1.0 * kepler::floor(-1.0 * omega)};
    }

    Array Floor::operator()(const Number& alpha, const Number& omega) {
        if(alpha.imag() != 0.0 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Minimum of complex numbers is undefined.");
        }

        return {std::min(alpha.real(), omega.real())};
    }

    Array Floor::operator()(const Number& omega) {
       return {kepler::floor(omega)};
    }

    Array And::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Least common multiple of complex numbers is unsupported.");
        } else if(round(alpha.real()) != alpha.real() || round(omega.real()) != omega.real()) {
            throw kepler::error(DomainError, "Least common multiple of fractional numbers is unsupported.");
        }
        return {std::lcm((int) alpha.real(), (int) omega.real())};
    }

    Array And::operator()(const std::u32string &alpha, const std::u32string &omega) {
        throw kepler::error(DomainError, "The function is undefined on string arguments.");
    }

    Array And::operator()(const Number &omega) {
        throw kepler::error(SyntaxError, "The function requires a left argument.");
    }

    Array Nand::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Logical NAND of complex numbers is unsupported.");
        } else if((alpha.real() != 1.0 && alpha.real() != 0.0) || (omega.real() != 1.0 && omega.real() != 0.0)) {
            throw kepler::error(DomainError, "Logical NAND of non-boolean numbers is unsupported.");
        }
        return {1.0 - std::lcm((int) alpha.real(), (int) omega.real())};
    }

    Array Nand::operator()(const Number &omega) {
        throw kepler::error(SyntaxError, "The function requires a left argument.");
    }

    Array Nand::operator()(const std::u32string &alpha, const std::u32string &omega) {
        throw kepler::error(DomainError, "The function is undefined on string arguments.");
    }

    Array Or::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Greatest common divisor of complex numbers is unsupported.");
        } else if(round(alpha.real()) != alpha.real() || round(omega.real()) != omega.real()) {
            throw kepler::error(DomainError, "Greatest common divisor of fractional numbers is unsupported.");
        }
        return {std::gcd((int) alpha.real(), (int) omega.real())};
    }

    Array Or::operator()(const Number &omega) {
        throw kepler::error(SyntaxError, "The function requires a left argument.");
    }

    Array Or::operator()(const std::u32string &alpha, const std::u32string &omega) {
        throw kepler::error(DomainError, "The function is undefined on string arguments.");
    }

    Array Nor::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Logical NOR of complex numbers is unsupported.");
        } else if((alpha.real() != 1.0 && alpha.real() != 0.0) || (omega.real() != 1.0 && omega.real() != 0.0)) {
            throw kepler::error(DomainError, "Logical NOR of non-boolean numbers is unsupported.");
        }
        return {1.0 - std::gcd((int) alpha.real(), (int) omega.real())};
    }

    Array Nor::operator()(const std::u32string &alpha, const std::u32string &omega) {
        throw kepler::error(DomainError, "The function is undefined on string arguments.");
    }

    Array Nor::operator()(const Number &omega) {
        throw kepler::error(SyntaxError, "The function requires a left argument.");
    }

    Array RightTack::operator()(const Array &alpha, const Array &omega) {
        return omega;
    }

    Array RightTack::operator()(const Array &omega) {
        return omega;
    }

    Array LeftTack::operator()(const Array &alpha, const Array &omega) {
        return alpha;
    }

    Array LeftTack::operator()(const Array &omega) {
        return omega;
    }

    Array Less::operator()(const Number& alpha, const Number& omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Less-than of complex numbers is unsupported.");
        }

        return {alpha.real() < omega.real()};
    }

    Array LessEq::operator()(const Number& alpha, const Number& omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Less-than-or-equal of complex numbers is unsupported.");
        }

        return {alpha.real() <= omega.real()};
    }

    Array Eq::operator()(const Number& alpha, const Number& omega) {
        return {alpha == omega};
    }

    Array Eq::operator()(const Char &alpha, const Char &omega) {
        return {alpha == omega};
    }

    Array GreaterEq::operator()(const Number& alpha, const Number& omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Greater-than of complex numbers is unsupported.");
        }

        return {alpha.real() >= omega.real()};
    }

    Array Greater::operator()(const Number& alpha, const Number& omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Greater-than of complex numbers is unsupported.");
        }

        return {alpha.real() > omega.real()};
    }

    Array Neq::operator()(const Number &alpha, const Number &omega) {
        return {alpha != omega};
    }

    Array Neq::operator()(const Char &alpha, const Char &omega) {
        return {alpha != omega};
    }

    Array Neq::operator()(const Array &omega) {
        Array result = omega;
        std::vector<Array::element_type> seen;

        for(int i = 0; i < omega.size(); ++i) {
            if(std::count(seen.begin(), seen.end(), omega.data[i]) == 0) {
                seen.push_back(omega.data[i]);
                result.data[i] = Array{{}, {1}};
            } else {
                result.data[i] = Array{{}, {0}};
            }
        }

        return result;
    }

    Array LeftShoe::operator()(const Array &omega) {
        if(omega.is_simple_scalar()) {
            return omega;
        } else {
            return {{}, {omega}};
        }
    }

    Array LeftShoe::operator()(const Array &alpha, const Array &omega) {
        if(alpha.size() > omega.size()) {
            if(holds_alternative<std::u32string>(omega.data[0])) {
                return partitioned_enclose(alpha, get<std::u32string>(omega.data[0]));
            }
        }
        return partitioned_enclose(alpha, omega);
    }

    Array Not::operator()(const Number &omega) {
        if(omega != 0.0 && omega != 1.0) {
            throw kepler::error(DomainError, "Expected an array of boolean values.");
        }

        return {!(bool)omega.real()};
    }

    Array Not::operator()(const Array &alpha, const Array &omega) {
        if((alpha.rank() != omega.rank() && omega.rank() != 0) || alpha.rank() >= 2) {
            throw kepler::error(RankError, "Incompatible ranks.");
        }

        if((alpha.rank() == 0 && !alpha.is_numeric()) || (omega.rank() == 0 && !omega.is_numeric())) {
            // Individual element.
            return std::visit(*this, alpha.data[0], omega.data[0]);
        } else {
            // Rank 1.
            return without(alpha, omega);
        }
    }

    Array Not::operator()(const std::u32string &alpha, const std::u32string &omega) {
        return without(alpha, omega);
    }

    Array Iota::operator()(const Array& omega) {
        if(omega.size() != 1 || !holds_alternative<Number>(omega.data[0])) {
            throw kepler::error(RankError, "Expected numeric scalar for index generation.");
        }

        Number om = get<Number>(omega.data[0]);
        if(om.imag() != 0.0) {
            throw kepler::error(DomainError, "Complex number not usable for index generation.");
        } else if(om.real() != round(om.real())) {
            throw kepler::error(DomainError, "Floating point number not usable for index generation.");
        }

        int final_om = (int)round(om.real());

        if(final_om < 0) {
            throw kepler::error(DomainError, "Negative numbers cannot be used for index generation.");
        }

        Array io = symbol_table->get<Array>(constants::index_origin_id);
        int origin = (int)(get<Number>(io.data[0]).real());

        Array result({final_om}, {});
        for(int i = 0; i < final_om; ++i) {
            result.data.emplace_back(Array{{}, {i + origin}});
        }
        return result;
    }

    Array Rho::operator()(const Array& omega) {
        Array result{{(int)omega.shape.size()}, {}};
        for(auto& dim : omega.shape) {
            result.data.emplace_back(Array{{}, {dim}});
        }
        return result;
    }

    Array Rho::operator()(const Array &alpha, const Array &omega) {
        return rho(alpha, omega);
    }

    int vec_size(const std::vector<int>& shape, int dim) {
        if(dim == shape.size() - 1) {
            return shape.back();
        } else {
            return std::accumulate(shape.begin() + dim, shape.end() - 1, 1, std::multiplies<>());
        }
    }

    int get_step_size(const std::vector<int>& shape, int dim) {
        return std::accumulate(shape.begin() + dim + 1, shape.end(), 1, std::multiplies<>());
    }

    int get_block_size(const std::vector<int>& shape, int axis) {
        int length = vec_size(shape, axis);
        if(axis == shape.size() - 1) {
            return length;
        }

        return length * shape.back();
    }

    int get_shift(int element, int axis, int step_size, const Array& alpha, const Array& omega) {
        if(alpha.is_simple_scalar()) {
            return (int)get<Number>(alpha.data[0]).real();
        }

        int scalar_dim_size = omega.shape.back();

        int index;
        if(axis == omega.shape.size() - 1) {
            index = std::floor((double)element / scalar_dim_size);
        } else {
            index = (int)((element % scalar_dim_size) + (std::floor((double)element / step_size) * scalar_dim_size));
        }

        return (int)get<Number>(get<Array>(alpha.data[index]).data[0]).real();
    }

    Array rotate(int axis, const Array& alpha, const Array& omega) {
        int step_size = get_step_size(omega.shape, axis);
        int block_size = get_block_size(omega.shape, axis);

        Array result = omega;
        for(int i = 0; i < omega.size(); ++i) {
            int shift = get_shift(i, axis, step_size, alpha, omega);

            int index = (int)(std::floor((double)i / block_size) * block_size) + (((step_size * shift + i) % block_size + block_size) % block_size);//((step_size * shift + i) % (block_size));
            result.data[i] = omega.data[index];
        }
        return result;
    }

    //⌽(2 2 3 4⍴⍳100)
    Array reverse(int axis, const Array& omega) {
        int step_size = get_step_size(omega.shape, axis);
        int block_size = get_block_size(omega.shape, axis);

        Array result = omega;
        for(int i = 0; i < omega.size(); ++i) {
            int width = omega.shape[axis];
            double shift = (width - 1) - 2 * ((int)std::floor((double)i / step_size) % width);
            int index = (int)(std::floor((double)i / block_size) * block_size) + ((step_size * (int)shift + i) % (block_size));
            result.data[i] = omega.data[index];
        }
        return result;
    }

    Array CircleBar::operator()(const Number &omega) {
        return {omega};
    }

    Array CircleBar::operator()(const std::u32string &omega) {
        return {std::u32string{omega.rbegin(), omega.rend()}};
    }

    Array CircleBar::operator()(const Number &shift, const std::u32string &omega) {
        std::u32string result = omega;
        std::rotate(result.begin(), result.begin() + (int)shift.real(), result.end());
        return {result};
    }

    Array CircleBar::operator()(const Number &shift, const Number &omega) {
        return {omega};
    }

    // Rotate along first axis by alpha.
    Array CircleBar::operator()(const Array &alpha, const Array &omega) {
        if(!alpha.is_integer_numeric()) {
            throw kepler::error(DomainError, "Expected only integer-numeric left argument.");
        } else if(alpha.is_simple_scalar() && alpha.is_numeric() && omega.is_simple_scalar()) {
            return std::visit(*this, alpha.data[0], omega.data[0]);
        } else if(omega.is_scalar()) {
            return (*this)(alpha, get<Array>(omega.data[0]));
        }

        int required_size = omega.size() / omega.shape[0];
        if(!alpha.is_simple_scalar() && alpha.size() != required_size) {
            throw kepler::error(LengthError, "Left argument must have same shape as right argument, excluding the first axis.");
        }

        return rotate(0, alpha, omega);
    }

    // Reverse
    Array CircleBar::operator()(const Array &omega) {
        if(omega.is_simple_scalar()) {
            return std::visit(*this, omega.data[0]);
        }

        return reverse(0, omega);
    }

    // x←3 3⍴⍳100
    // 1⌽x
    Array CircleStile::operator()(const Array &alpha, const Array &omega) {
        if(!alpha.is_integer_numeric()) {
            throw kepler::error(DomainError, "Expected only integer-numeric left argument.");
        } else if(alpha.is_simple_scalar() && alpha.is_numeric() && omega.is_simple_scalar()) {
            return std::visit(*this, alpha.data[0], omega.data[0]);
        } else if(omega.is_scalar()) {
            return (*this)(alpha, get<Array>(omega.data[0]));
        }

        int required_size = omega.size() / omega.shape.back();
        if(!alpha.is_simple_scalar() && alpha.size() != required_size) {
            throw kepler::error(LengthError, "Left argument must have same shape as right argument, excluding the last axis.");
        }

        return rotate(omega.shape.size() - 1, alpha, omega);
    }

    Array CircleStile::operator()(const Array &omega) {
        if(omega.is_simple_scalar()) {
            return std::visit(*this, omega.data[0]);
        }

        return reverse(omega.shape.size() - 1, omega);
    }

    Array CircleStile::operator()(const Number &omega) {
        return {omega};
    }

    Array CircleStile::operator()(const std::u32string &omega) {
        return {std::u32string{omega.rbegin(), omega.rend()}};
    }

    Array CircleStile::operator()(const Number &shift, const std::u32string &omega) {
        std::u32string result = omega;
        std::rotate(result.begin(), result.begin() + (int)shift.real(), result.end());
        return {result};
    }

    Array CircleStile::operator()(const Number &shift, const Number &omega) {
        return {omega};
    }

    void pad(Array& arr, int dim, const std::vector<int>& new_shape, const Array::element_type& padding, const std::vector<int>& ordering) {
        int orig_size = std::accumulate(arr.shape.begin() + dim, arr.shape.end(), 1, std::multiplies<>());
        int new_size = std::accumulate(new_shape.begin() + dim, new_shape.end(), 1, std::multiplies<>());

        int padding_per_step = new_size - orig_size;
        int steps = std::accumulate(arr.shape.begin(), arr.shape.begin() + dim, 1, std::multiplies<>());

        int base_padding = ordering[dim] >= 0 ? orig_size : 0;

        for(int step = 0; step < steps; ++step) {
            int index = step * (orig_size + padding_per_step) + base_padding;

            if(padding_per_step < 0) {
                arr.data.erase(arr.data.begin() + index + padding_per_step, arr.data.begin() + index);
            } else {
                arr.data.insert(arr.data.begin() + index, padding_per_step, padding);
            }
        }
    }

    // x←(2 2 2⍴⍳100) (2 2 3⍴⍳100) ◊ ↑x
    // x←(2⍴⍳100) (3⍴⍳100) ◊ ↑x
    Array reshape(const Array& original, const Array::element_type& padding, const std::vector<int>& new_shape, const std::vector<int>& ordering) {
        Array result = original;

        int additional_dims = new_shape.size() - original.shape.size();
        if(additional_dims < 0) {
            int deleted_data = result.data.size() - std::accumulate(result.shape.begin() + abs(additional_dims), result.shape.end(), 1, std::multiplies<>());
            result.data.erase(result.data.end() - deleted_data, result.data.end());
            result.shape.erase(result.shape.begin(), result.shape.begin() + abs(additional_dims));
        } else {
            result.shape.insert(result.shape.begin(), additional_dims, 1);
        }

        for(int i = new_shape.size() - 1; i >= 0; --i) {
            pad(result, i, new_shape, padding, ordering);
            result.shape[i] = new_shape[i];
        }

        return result;
    }

    // ¯10 10↑(2 2 2⍴⍳100)
    // ¯10↑(2 2 2⍴⍳100)
    Array ArrowUp::operator()(const Array &alpha, const Array &omega) {
        if(!alpha.is_integer_numeric()) {
            throw kepler::error(DomainError, "Expected an integer-based left argument.");
        } else if(alpha.rank() > 1) {
            throw kepler::error(DomainError, "Left argument must be a scalar or vector.");
        } else if(alpha.size() > omega.rank()) {
            throw kepler::error(LengthError, "Length of left argument must be equal to or less than the rank of the right argument.");
        }

        auto shape = omega.shape;
        std::vector<int> ordering = shape;

        if(alpha.is_scalar()) {
            auto& num = get<Number>(alpha.data[0]);
            int num_int = static_cast<int>(num.real());

            if(num_int < 0) {
                ordering[0] = num_int;
            }

            shape[0] = abs(num_int);
        } else {
            for(int i = 0; i < alpha.data.size(); ++i) {
                auto& num = get<Number>(get<Array>(alpha.data[i]).data[0]);
                int num_int = static_cast<int>(num.real());

                if(num_int < 0) {
                    ordering[i] = num_int;
                }

                shape[i] = abs(num_int);
            }
        }

        return reshape(omega, Array{0}, shape, ordering);
    }

    Array ArrowUp::operator()(const Array &omega) {
        // Find the largest shape of elements in omega.

        std::vector<int> largest_shape = {};

        for(auto& element : omega.data) {
            auto& shape = get<Array>(element).shape;

            for(int d = 0; d < shape.size(); ++d) {
                if(largest_shape.size() <= d) {
                    largest_shape.emplace_back(shape[d]);
                } else if(largest_shape[d] < shape[d]) {
                    largest_shape[d] = shape[d];
                }
            }
        }


        Array result{largest_shape, {}};
        result.shape.insert(result.shape.begin(), omega.size());

        for(auto& element : omega.data) {
            const auto& arr = get<Array>(element);
            auto tmp = reshape(arr, Array{0}, largest_shape, largest_shape);
            result.data.reserve(result.size() + tmp.data.size());
            std::copy(tmp.data.begin(), tmp.data.end(), std::back_inserter(result.data));
        }

        return result;
    }

    Array Comma::operator()(const Array &omega) {
        return {{omega.size()}, omega.data};
    }

    //https://stackoverflow.com/questions/7560114/random-number-c-in-some-range
    Array Roll::operator()(const Number &omega) {
        if(omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Random complex numbers are not supported.");
        }

        std::random_device random_device;
        std::mt19937 generator(random_device());

        if(omega.real() == 0.0) {
            // Generate number between 0 and 1.
            std::uniform_real_distribution<> distribution(0.0, 1.0);
            return {distribution(generator)};
        } else if(omega.real() == round(omega.real())) {
            // Generate number between ⎕IO and omega.
            Array io = symbol_table->get<Array>(constants::index_origin_id);
            int origin = (int)(get<Number>(io.data[0]).real());

            std::uniform_int_distribution<> distribution(origin, static_cast<int>(omega.real()));
            return {distribution(generator)};
        } else {
            throw kepler::error(DomainError, "Expected integer numbers only.");
        }
    }

    Array Star::operator()(const Number &omega) {
        return {exp(omega)};
    }

    Array Star::operator()(const Number &alpha, const Number &omega) {
        if(alpha == 0.0 && omega == 0.0) {
            return {1};
        } else if(alpha == 0.0) {
            if(omega.real() > 0.0) {
                return {0};
            } else {
                throw kepler::error(DomainError, "0 to the power of a negative number is undefined.");
            }
        }

        return {std::pow(alpha, omega)};
    }

    Array Log::operator()(const Number &omega) {
        if(omega == 0.0) {
            throw kepler::error(DomainError, "Natural logarithm of 0 is undefined.");
        }

        return {log(omega)};
    }

    Array Log::operator()(const Number &alpha, const Number &omega) {
        if(alpha == omega) {
            return {1};
        } else if(alpha == 1.0) {
            throw kepler::error(DomainError, "Logarithm of base 1 is undefined.");
        }

        return { log(omega) / log(alpha) };
    }

    Array Bar::operator()(const Number &omega) {
        return {abs(omega)};
    }

    Array Bar::operator()(const Number &alpha, const Number &omega) {
        if(alpha == 0.0) {
            throw kepler::error(DomainError, "Expected a non-zero left argument.");
        }

        return {omega - alpha * kepler::floor(omega / (alpha + (double)(0.0 == omega)))};
    }

    Array ExclamationMark::operator()(const Number &omega) {
        if(omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Factorial of complex numbers is undefined.");
        } if(omega.real() < 0.0 && omega.real() == round(omega.real())) {
            throw kepler::error(DomainError, "Factorial of negative integers is undefined.");
        }

        return {tgamma(omega.real() + 1)};
    }

    Array ExclamationMark::operator()(const Number &alpha, const Number &omega) {
        return {kepler::binomial(alpha, omega)};
    }

    Array Circle::operator()(const Number &omega) {
        return {M_PI * omega};
    }

    Array Circle::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.0) {
            throw kepler::error(DomainError, "Left argument cannot be complex.");
        } else if(alpha.real() != round(alpha.real())) {
            throw kepler::error(DomainError, "Expected an integer left argument.");
        }

        int designator = static_cast<int>(alpha.real());
        if(designator < -12 || designator > 12) {
            throw kepler::error(DomainError, "Expected left argument to be between -12 and 12.");
        }

        switch (designator) {
            case -12:
                return {std::exp(omega * Number(0, 1))};
            case -11:
                return {Number(0, 1) * omega};
            case -10:
                return {std::conj(omega)};
            case -9:
                return {omega};
            case -8:
                return {pow((-1.0 + std::pow(omega, 2)), 0.5)};
            case -7:
                if(omega == -1.0 || omega == 1.0) {
                    throw kepler::error(DomainError, "Inverse hyperbolic tangent undefined for " +
                            number_to_string(omega, 2));
                }

                return {atanh(omega)};
            case -6:
                return {acosh(omega)};
            case -5:
                return {asinh(omega)};
            case -4:
                if(omega == -1.0) {
                    return {0};
                } else {
                    return {pow(((omega + 1.0) / (omega - 1.0)), 0.5) * (omega + 1.0)};
                }
            case -3:
                return {atan(omega)};
            case -2:
                return {acos(omega)};
            case -1:
                return {asin(omega)};
            case 0:
                if(omega.imag() != 0.0) {
                    throw kepler::error(DomainError, "Expected non-complex argument.");
                } else if(omega.real() < -1.0 || omega.real() > 1.0) {
                    throw kepler::error(DomainError, "Expected argument between -1 and 1.");
                } else {
                    return {pow((1.0 - pow(omega, 2)), 0.5)};
                }
            case 1:
                return {sin(omega)};
            case 2:
                return {cos(omega)};
            case 3:
                if(omega.imag() == 0.0
                   && static_cast<int>(std::round(omega.real() / M_PI_2)) % 2 != 0) {
                    throw kepler::error(DomainError, "Tangent is undefined for odd multiples of π/2.");
                }
                return {tan(omega)};
            case 4:
                return {pow((1.0 + pow(omega, 2)), 0.5)};
            case 5:
                return {sinh(omega)};
            case 6:
                return {cosh(omega)};
            case 7:
                return {tanh(omega)};
            case 8:
                return {pow(-1.0 - pow(omega, 2), 0.5)};
            case 9:
                return {omega.real()};
            case 10:
                return {abs(omega)};
            case 11:
                return {omega.imag()};
            case 12:
                return {std::arg(omega)};
            default:
                throw kepler::error(InternalError, "Could not match designator.");
        }
    }
};
