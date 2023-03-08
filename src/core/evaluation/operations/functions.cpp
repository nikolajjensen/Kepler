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
#include "core/session.h"
#include "core/constants/config.h"
#include "core/symbol_table.h"

namespace kepler {
    Number Plus::operator()(Number alpha, Number omega) {
        return alpha + omega;
    }

    Number Plus::operator()(Number omega) {
        return conj(omega);
    }

    Number Minus::operator()(Number alpha, Number omega) {
        return alpha - omega;
    }

    Number Minus::operator()(Number omega) {
        return omega * -1.0;
    }

    Number Times::operator()(Number alpha, Number omega) {
        return alpha * omega;
    }

    Number Times::operator()(Number omega) {
        return (omega == 0.0) ? omega : omega / abs(omega);
    }

    Number Divide::operator()(Number alpha, Number omega) {
        if(omega == 0.0) {
            throw kepler::error(DomainError, "Division by 0 is undefined.");
        }
        return alpha / omega;
    }

    Number Divide::operator()(Number omega) {
        if(omega == 0.0) {
            throw kepler::error(DomainError, "Reciprocal of 0 is undefined.");
        }
        return Number(1) / omega;
    }

    Number Floor::operator()(Number alpha, Number omega) {
        //return ;
        throw kepler::error(InternalError, "'minimum' not implemented yet.");
    }

    Number Floor::operator()(Number omega) {
        //return (omega == 0.0) ? omega : omega / abs(omega);
        throw kepler::error(InternalError, "'floor' not implemented yet.");
    }

    Array Iota::operator()(Array omega) {
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

    Array Rho::operator()(Array omega) {
        Array result{{(int)omega.shape.size()}, {}};
        for(auto& dim : omega.shape) {
            result.data.emplace_back(Array{{}, {dim}});
        }
        return result;
    }
};