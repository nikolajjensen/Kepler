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

#include "dyadic_operators.h"

namespace kepler {
    Jot::Jot() : aalpha(nullptr), oomega(nullptr) {}

    Jot::Jot(Operation *aalpha_, Operation *oomega_) : aalpha(aalpha_), oomega(oomega_) {}

    Jot::~Jot() {
        delete aalpha;
        delete oomega;
    }

    bool Jot::is_configured() const {
        return aalpha != nullptr && oomega != nullptr;
    }

    void Jot::configure(Operation *aalpha_, Operation *oomega_) {
        aalpha = aalpha_;
        oomega = oomega_;
    }

    Number Jot::operator()(Number alpha, Number omega) {
        if (!is_configured()) throw std::runtime_error("Not configured.");

        return (*aalpha)(alpha, (*oomega)(omega));
    }

    Number Jot::operator()(Number omega) {
        if (!is_configured()) throw std::runtime_error("Not configured.");

        return (*aalpha)((*oomega)(omega));
    }
};
