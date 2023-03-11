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

//https://www.jsoftware.com/papers/eem/complexfloor1.htm#0
kepler::Number kepler::floor(const Number &number) {
    Number raw = {std::floor(number.real()), std::floor(number.imag())};

    double integral;
    double fractional_real = std::modf(number.real(), &integral);
    double fractional_imag = std::modf(number.imag(), &integral);

    if (1.0 > (fractional_imag + fractional_real)) {
        return raw;
    } else if ((1.0 <= (fractional_imag + fractional_real)) && fractional_real >= fractional_imag) {
        return raw + 1.0;
    } else if ((1.0 <= (fractional_imag + fractional_real)) && fractional_real < fractional_imag) {
        return raw + Number(0, 1);
    } else {
        throw kepler::error(InternalError, "Unexpected case reached in floor of number.");
    }
}

kepler::Array kepler::partitioned_enclose(const Array &alpha, const Array &omega) {
    std::vector<Array::element_type> lists;

    for(int i = 0; i < alpha.data.size(); ++i) {
        auto element = get<Array>(alpha.data[i]);
        if(!holds_alternative<Number>(element.data[0])) {
            throw kepler::error(DomainError, "Expected numbers only.");
        }

        auto& ctrl_bool = get<Number>(element.data[0]);

        if((ctrl_bool.imag() != 0.0) || (ctrl_bool != 0.0 && ctrl_bool != 1.0)) {
            throw kepler::error(DomainError, "Expected boolean values only.");
        }

        if(ctrl_bool == 1.0) {
            lists.emplace_back(Array{{0}, {}});
        }

        if(!lists.empty()) {
            get<Array>(lists.back()).data.emplace_back(omega.data[i]);
            get<Array>(lists.back()).shape[0]++;
        }
    }

    int size = (int)lists.size();
    if(size > 1) {
        return {{size}, std::move(lists)};
    }
    return get<Array>(lists[0]);
}

kepler::Array kepler::partitioned_enclose(const Array &alpha, const std::u32string &omega) {
    std::vector<Array::element_type> lists;

    for(int i = 0; i < alpha.data.size(); ++i) {
        auto element = get<Array>(alpha.data[i]);
        if(!holds_alternative<Number>(element.data[0])) {
            throw kepler::error(DomainError, "Expected numbers only.");
        }

        auto& ctrl_bool = get<Number>(element.data[0]);

        if((ctrl_bool.imag() != 0.0) || (ctrl_bool != 0.0 && ctrl_bool != 1.0)) {
            throw kepler::error(DomainError, "Expected boolean values only.");
        }

        if(ctrl_bool == 1.0) {
            lists.emplace_back(Array{{}, {U""}});
        }

        if(!lists.empty()) {
            auto& arr = get<Array>(lists.back());
            auto& str = get<std::u32string>(arr.data[0]);
            str += omega[i];
        }
    }

    int size = (int)lists.size();
    if(size > 1) {
        return {{size}, std::move(lists)};
    }
    return get<Array>(lists[0]);
}

kepler::Array kepler::without(const Array &alpha, const Array &omega) {
    Array result{{}, {}};

    for(auto& element : alpha.data) {
        if(std::count(omega.data.begin(), omega.data.end(), element) == 0) {
            result.data.emplace_back(element);
        }
    }

    int size = (int)result.data.size();
    if(size > 0) {
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
        throw kepler::error(ValueError, "Left argument of reshape cannot have rank " + std::to_string(alpha.rank()));
    }

    if(alpha.is_scalar()) {
        result.shape = {(int)get<Number>(alpha.data[0]).real()};
    } else {
        for(auto& element : alpha.data) {
            auto& num = get<Number>(get<Array>(element).data[0]);

            if(num.real() < 0.0) {
                throw kepler::error(ValueError, "Expected only positive integers in argument.");
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
        } else {
            result.data[i] = omega.data[index];
        }
    }

    return result;
}

std::vector<int> kepler::encode(const std::vector<int> &radices, const int &scalar) {
    auto n = (std::count(radices.begin(), radices.end(), 0) == 0)
             ? std::accumulate(radices.begin(), radices.end(), 1, std::multiplies<>())
             : scalar + 1;
    auto b = 0;

    auto rit = radices.rbegin();
    std::vector<int> result;
    while(rit != radices.rend()) {
        if(*rit != 0) {
            n = n / *rit;
            b = n % *rit;
        } else {
            b = n;
            n = 0;
        }
        result.emplace_back(b);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

kepler::Array kepler::decode(const Array &alpha, const Array &omega) {
    int acc = 0;
    int acc_prod = 1;

    for(int i = alpha.size(); i >= 0; --i) {
        acc += acc_prod * (int)get<Number>(get<Array>(omega.data[i]).data[0]).real();
        acc_prod *= (int)get<Number>(get<Array>(alpha.data[i]).data[0]).real();
    }

    return {acc};
}

kepler::Array kepler::index_generator(const Array &omega) {
    Array result = omega;

    if(omega.rank() > 1) {
        throw kepler::error(RankError, "Index generator did not expect array of rank " + std::to_string(omega.rank()));
    }

    if(!omega.is_integer_numeric()) {
        throw kepler::error(ValueError, "Index generator expected only integer array argument.");
    }

    if(omega.is_scalar()) {
        result.shape = {(int)get<Number>(omega.data[0]).real()};
    } else {
        result.shape = {};
        for(auto& element : omega.data) {
            auto& num = get<Number>(get<Array>(element).data[0]);

            if(num.real() < 0.0) {
                throw kepler::error(ValueError, "Expected only positive integers in argument.");
            }

            result.shape.emplace_back((int)num.real());
        }
    }



    return result;
}