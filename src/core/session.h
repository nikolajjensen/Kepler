//
// Copyright 2022 Nikolaj Banke Jensen.
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
#include "workspace.h"
#include "core/constants/config.h"

namespace kepler {
    class Session {
    public:
        Workspace active_workspace;
        std::string session_name;

        explicit Session(std::string&& name);

        Token& get_current_referent(Token& token);
        void set_current_referent(Token& token, List<Token> &&content);
        TokenClass current_class(Token& token);

        Array& get_system_parameter(const List<Char>& id);

        void immediate_execution_mode();
        void immediate_execution(std::string&& input, std::ostream& stream = std::cout);
        void immediate_execution(Token&& input, std::ostream& stream = std::cout);
    };
};