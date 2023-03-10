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