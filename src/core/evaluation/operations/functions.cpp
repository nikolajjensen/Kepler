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
            throw kepler::error(DomainError, "Division by 0 is undefined.");
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
        return {-kepler::floor(-omega)};
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

    Array Nand::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Logical NAND of complex numbers is unsupported.");
        } else if((alpha.real() != 1.0 && alpha.real() != 0.0) || (omega.real() != 1.0 && omega.real() != 0.0)) {
            throw kepler::error(DomainError, "Logical NAND of non-boolean numbers is unsupported.");
        }
        return {1.0 - std::lcm((int) alpha.real(), (int) omega.real())};
    }

    Array Or::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Greatest common divisor of complex numbers is unsupported.");
        } else if(round(alpha.real()) != alpha.real() || round(omega.real()) != omega.real()) {
            throw kepler::error(DomainError, "Greatest common divisor of fractional numbers is unsupported.");
        }
        return {std::gcd((int) alpha.real(), (int) omega.real())};
    }

    Array Nor::operator()(const Number &alpha, const Number &omega) {
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Logical NOR of complex numbers is unsupported.");
        } else if((alpha.real() != 1.0 && alpha.real() != 0.0) || (omega.real() != 1.0 && omega.real() != 0.0)) {
            throw kepler::error(DomainError, "Logical NOR of non-boolean numbers is unsupported.");
        }
        return {1.0 - std::gcd((int) alpha.real(), (int) omega.real())};
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
        if(alpha.imag() != 0.00 || omega.imag() != 0.0) {
            throw kepler::error(DomainError, "Equality of complex numbers is unsupported.");
        }

        return {alpha.real() == omega.real()};
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
        if(alpha.size() != omega.size()) {
            if(omega.size() != 1) {
                throw kepler::error(LengthError, "Mismatched left and right shapes.");
            }

            if(!holds_alternative<std::u32string>(omega.data[0])) {
                throw kepler::error(DomainError, "Expected a string here.");
            }

            return partitioned_enclose(alpha, get<std::u32string>(omega.data[0]));
        } else {
            return partitioned_enclose(alpha, omega);
        }
    }

    Array Not::operator()(const Number &omega) {
        if(omega != 0.0 && omega != 1.0) {
            throw kepler::error(DomainError, "Expected an array of boolean values.");
        }

        return {!(bool)omega.real()};
    }

    Array Not::operator()(const Array &alpha, const Array &omega) {
        if(alpha.rank() != omega.rank() || alpha.rank() >= 2) {
            throw kepler::error(RankError, "Incompatible ranks.");
        }

        if(alpha.rank() == 0) {
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
            throw kepler::error(SyntaxError, "Expected numeric scalar for index generation.");
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
};
