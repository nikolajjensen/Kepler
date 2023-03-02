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
#include "core/token.h"
#include "core/context.h"
#include "core/session.h"

namespace kepler::evaluation {
    Token reduce_statement(Context& context, Session& session);
    Token evaluate_statement(Context& context, Session& session);
    Token evaluate_line(Context& context, Session& session);

    Token evaluate_editing_request(Token& identifier, Context& context, Session& session);
    Token evaluate_function_definition_request(List<Char>& input, Session& session);

    void bind_token_class(Token& token, Session& session);
    void literal_conversion(Token& token, Session& session);
};