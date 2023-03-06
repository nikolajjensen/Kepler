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

#pragma once
#include "core/datatypes.h"
#include "core/array.h"
//#include "core/session.h"

namespace kepler {
    struct Session;

    struct Operation {
    protected:
        Operation* op;
        Session* session;

        virtual bool is_configured() const;

    public:
        Operation();
        Operation(Operation* op);
        Operation(Session* session);

        virtual ~Operation();

        virtual Array operator()(Array omega);

        virtual Array operator()(Array alpha, Array omega);

        virtual Number operator()(Number omega);

        virtual Number operator()(Number alpha, Number omega);

        virtual std::u32string operator()(std::u32string omega);

        virtual std::u32string operator()(std::u32string alpha, std::u32string omega);
    };
};