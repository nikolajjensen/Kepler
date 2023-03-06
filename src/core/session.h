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
#include <string>
#include "workspace.h"
#include "core/evaluation/parser/parser.h"
#include "core/evaluation/tokenizer/tokenizer.h"
#include "core/evaluation/interpreter.h"

namespace kepler {
    class Session {
    private:
        Tokenizer tokenizer;
        Parser parser;
        Interpreter interpreter;

    public:
        Workspace active_workspace;
        std::string session_name;

        explicit Session(std::string&& name);

        void immediate_execution_mode();
        void immediate_execution(std::u32string&& input, std::ostream& stream = std::cout);
    };
};