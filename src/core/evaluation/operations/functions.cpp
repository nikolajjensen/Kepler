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
        if(omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Ceiling of complex numbers is undefined.");
        }
        return {-kepler::floor(-omega)};
    }

    Array Floor::operator()(const Number& alpha, const Number& omega) {
        if(alpha.imag() != 0.0 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Minimum of complex numbers is undefined.");
        }

        return {std::min(alpha.real(), omega.real())};
    }

    Array Floor::operator()(const Number& omega) {
        if(omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Floor of complex numbers is undefined.");
        }

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

            int index = (int)(std::floor((double)i / block_size) * block_size) + ((step_size * shift + i) % (block_size));
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
            double shift = (width - 1) - 2 * ((int)std::floor((double)i / step_size) % width);//std::floor((double)i / step_size) + (int)(std::floor((double)i / block_size) * step_size);// + (int)(std::floor((double)i / block_size) * block_size);
            int index = (int)(std::floor((double)i / block_size) * block_size) + ((step_size * (int)shift + i) % (block_size));
            result.data[i] = omega.data[index];
        }
        return result;

        /*
        Array result{omega.shape, {}};

        int length = omega.flattened_shape();
        length /= omega.shape[axis];
        for(int i = omega.data.size() - length; i >= 0; i -= length) {
            for(int j = i; j < i + length; ++j) {
                result.data.emplace_back(omega.data[j]);
            }
        }

        return result;
         */
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
        } else if(alpha.rank() != omega.rank() - 1) {
            throw kepler::error(RankError, "Left argument must be one less than rank of right argument.");
        }

        int required_size = omega.size() / omega.shape[0];
        if(alpha.size() != required_size) {
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

        /*
        // Get flattened_shape - size of left dimension. This is size of each chunk.
        // Reverse iterate omega by chunk size, and insert chunk into result, which is then returned.

        if(omega.is_simple_scalar()) {
            return std::visit(*this, omega.data[0]);
        }

        Array result{omega.shape, {}};

        int length = omega.flattened_shape();
        length /= omega.shape[0];
        for(int i = omega.data.size() - length; i >= 0; i -= length) {
            for(int j = i; j < i + length; ++j) {
                result.data.emplace_back(omega.data[j]);
            }
        }

        return result;
         */
    }

    Array CircleStile::operator()(const Array &alpha, const Array &omega) {
        if(!alpha.is_integer_numeric()) {
            throw kepler::error(DomainError, "Expected only integer-numeric left argument.");
        } else if(alpha.is_simple_scalar() && alpha.is_numeric() && omega.is_simple_scalar()) {
            return std::visit(*this, alpha.data[0], omega.data[0]);
        } else if(alpha.rank() != omega.rank() - 1) {
            throw kepler::error(RankError, "Left argument must be one less than rank of right argument.");
        }

        int required_size = omega.size() / omega.shape.back();
        if(alpha.size() != required_size) {
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

    Array Roll::operator()(const Array &alpha, const Array &omega) {
        throw kepler::error(DomainError);
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
};
