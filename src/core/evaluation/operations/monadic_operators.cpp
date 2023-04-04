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

#include "monadic_operators.h"

#include <utility>
#include "core/error.h"
#include <memory>

namespace kepler {
    MonadicOp::MonadicOp(Operation_ptr op_) : op(std::move(op_)), Operation(nullptr) {}

    Array Commute::operator()(const Array& alpha, const Array& omega) {
        return (*op)(omega, alpha);
    }

    Array Commute::operator()(const Array& omega) {
        return (*op)(omega, omega);
    }

    Array Slash::operator()(const Array& alpha, const Array& omega) {
        throw kepler::Error(NotImplemented, "Dyadic SLASH is not implemented.");
    }

    Array Slash::operator()(const Array& omega) {
        if(omega.size() < 2) {
            return omega;
        }

        Array acc = get<Array>(omega.data.back());
        for(int i = omega.size() - 2; i >= 0; --i) {
            acc = (*op)(get<Array>(omega.data[i]), acc);
        }
        return acc;
    }

    Array Diaeresis::operator()(const Array &alpha, const Array &omega) {
        Array result{{}, {}};

        if(alpha.is_scalar() && !omega.is_scalar()) {
            auto al = alpha.data[0];

            result.shape = omega.shape;
            auto length = result.flattened_shape();
            for(int i = 0; i < length; ++i) {
                result.data.emplace_back((*op)(al, get<Array>(omega.data[i])));
            }
        } else if(!alpha.is_scalar() && omega.is_scalar()) {
            auto om = omega.data[0];

            result.shape = alpha.shape;
            auto length = result.flattened_shape();
            for(int i = 0; i < length; ++i) {
                result.data.emplace_back((*op)(get<Array>(alpha.data[i]), om));
            }
        } else {
            if(alpha.rank() != omega.rank()) {
                throw kepler::Error(RankError, "Mismatched ranks of left and right arguments.");
            }

            if(alpha.shape != omega.shape) {
                throw kepler::Error(LengthError, "Left and right arguments must have the same dimensions.");
            }

            result.shape = omega.shape;

            auto length = result.flattened_shape();
            for(int i = 0; i < length; ++i) {
                result.data.emplace_back((*op)(get<Array>(alpha.data[i]), get<Array>(omega.data[i])));
            }
        }

        return result;
    }

    Array Diaeresis::operator()(const Array &omega) {
        Array result = omega;

        for(auto& element : result.data) {
            element = (*op)(get<Array>(element));
        }

        return result;
    }

    // 1 2 3∘.×10 20 30 40
    Array OuterProduct::operator()(const Array &alpha, const Array &omega) {
        std::vector<int> result_shape = alpha.shape;
        std::copy(omega.shape.begin(), omega.shape.end(), std::back_inserter(result_shape));

        Array result{result_shape, {}};
        result.data.reserve(result.flattened_shape());

        if(alpha.is_scalar()) {
            for(int i = 0; i < omega.flattened_shape(); ++i) {
                result.data.emplace_back((*op)(alpha, get<Array>(omega.data[i])));
            }
        } else {
            for(int a = 0; a < alpha.flattened_shape(); ++a) {
                if(omega.is_scalar()) {
                    auto res = (*op)(get<Array>(alpha.data[a]), omega);
                    result.data.emplace_back(res);
                } else {
                    for(int i = 0; i < omega.flattened_shape(); ++i) {
                        result.data.emplace_back((*op)(get<Array>(alpha.data[a]), get<Array>(omega.data[i])));
                    }
                }
            }
        }

        return result;
    }
};