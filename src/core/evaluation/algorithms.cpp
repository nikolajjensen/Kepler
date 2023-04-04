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

#include "algorithms.h"
#include "core/error.h"
#include <cmath>
#include <numeric>
#include <algorithm>


//https://www.jsoftware.com/papers/eem/complexfloor1.htm#0
kepler::Number kepler::floor(const Number &number) {
    Number raw = {std::floor(number.real()), std::floor(number.imag())};

    double fractional_real = number.real() - std::floor(number.real() / (1 + (double)(0.0 == number.real())));
    double fractional_imag = number.imag() - std::floor(number.imag() / (1 + (double)(0.0 == number.imag())));

    if (1.0 > (fractional_imag + fractional_real)) {
        return raw;
    } else if ((1.0 <= (fractional_imag + fractional_real)) && fractional_real > fractional_imag) {
        return raw + 1.0;
    } else if ((1.0 <= (fractional_imag + fractional_real)) && fractional_real <= fractional_imag) {
        return raw + Number(0, 1);
    } else {
        throw kepler::Error(InternalError, "Unexpected case reached in floor of number.");
    }
}

kepler::Number kepler::binomial(const Number &alpha, const Number &omega) {
    if(alpha.imag() != 0.0 || omega.imag() != 0.0) {
        throw kepler::Error(DomainError, "Complex arguments are not supported.");
    }

    return (tgamma(omega.real() + 1.0) / (tgamma(alpha.real() + 1.0) * tgamma(1.0 + omega.real() - alpha.real())));
}

kepler::Array kepler::partitioned_enclose(const Array &alpha, const Array &omega) {
    std::vector<Array::element_type> lists;

    if(alpha.size() > omega.size()) {
        throw kepler::Error(LengthError, "String must be at least as long as the partitioning.");
    }

    for(int i = 0; i < alpha.data.size(); ++i) {
        auto element = std::get<Array>(alpha.data[i]);
        if(!std::holds_alternative<Number>(element.data[0])) {
            throw kepler::Error(DomainError, "Expected numbers only.");
        }

        auto& ctrl_bool = std::get<Number>(element.data[0]);

        if((ctrl_bool.imag() != 0.0) || (ctrl_bool != 0.0 && ctrl_bool != 1.0)) {
            throw kepler::Error(DomainError, "Expected boolean values only.");
        }

        if(ctrl_bool == 1.0) {
            lists.emplace_back(Array{{0}, {}});
        }

        if(!lists.empty()) {
            std::get<Array>(lists.back()).data.emplace_back(omega.data[i]);
            std::get<Array>(lists.back()).shape[0]++;
        }
    }

    int size = (int)lists.size();
    if(size > 1 || size == 0) {
        return {{size}, std::move(lists)};
    }
    return std::get<Array>(lists[0]);
}

kepler::Array kepler::partitioned_enclose(const Array &alpha, const std::u32string &omega) {
    std::vector<Array::element_type> lists;

    if(alpha.size() > omega.length()) {
        throw kepler::Error(LengthError, "String must be at least the the partitioning.");
    }

    for(int i = 0; i < alpha.data.size(); ++i) {
        auto element = std::get<Array>(alpha.data[i]);
        if(!std::holds_alternative<Number>(element.data[0])) {
            throw kepler::Error(DomainError, "Expected numbers only.");
        }

        auto& ctrl_bool = std::get<Number>(element.data[0]);

        if((ctrl_bool.imag() != 0.0) || (ctrl_bool != 0.0 && ctrl_bool != 1.0)) {
            throw kepler::Error(DomainError, "Expected boolean values only.");
        }

        if(ctrl_bool == 1.0) {
            lists.emplace_back(Array{{}, {U""}});
        }

        if(!lists.empty()) {
            auto& arr = std::get<Array>(lists.back());
            auto& str = std::get<std::u32string>(arr.data[0]);
            str += omega[i];
        }
    }

    int size = (int)lists.size();
    if(size > 1 || size == 0) {
        return {{size}, std::move(lists)};
    }
    return std::get<Array>(lists[0]);
}

kepler::Array kepler::without(const Array &alpha, const Array &omega) {
    Array result{{}, {}};

    for(auto& element : alpha.data) {
        if(std::count(omega.data.begin(), omega.data.end(), element) == 0) {
            result.data.emplace_back(element);
        }
    }

    int size = (int)result.data.size();
    if(size > 1 || size == 0) {
        result.shape = {size};
        return result;
    }

    return result.data[0];
}

kepler::Array kepler::without(const std::u32string &alpha, const std::u32string &omega) {
    std::u32string result;

    for(auto& c : alpha) {
        if(std::count(omega.begin(), omega.end(), c) == 0) {
            result += c;
        }
    }

    return {{}, {result}};
}

kepler::Array kepler::rho(const Array &alpha, const Array &omega) {
    Array result{{}, {}};

    if(alpha.rank() > 1) {
        throw kepler::Error(RankError, "Left argument of reshape cannot have rank " + std::to_string(alpha.rank()));
    }

    if(alpha.is_scalar()) {
        if(!alpha.is_integer_numeric()) {
            throw kepler::Error(DomainError, "Expected only positive integers in left argument.");
        }
        result.shape = {(int)std::get<Number>(alpha.data[0]).real()};
    } else {
        for(auto& element : alpha.data) {
            auto& num = std::get<Number>(std::get<Array>(element).data[0]);

            if(num.real() < 0.0) {
                throw kepler::Error(ValueError, "Expected only positive integers in right argument.");
            }

            result.shape.emplace_back((int)num.real());
        }
    }


    int omega_length = omega.flattened_shape();
    int alpha_length = result.flattened_shape();

    result.data.resize(alpha_length);
    for(int i = 0; i < alpha_length; ++i) {
        auto index = i % omega_length;
        if(omega.is_scalar()) {
            result.data[i] = omega;
        } else if(omega_length == 0) {
            result.data[i] = Array{0};
        } else {
            result.data[i] = omega.data[index];
        }
    }

    return result;
}