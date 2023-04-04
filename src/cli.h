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
#include <lyra/lyra.hpp>

/**
 * @brief The CLI namespace contains command-line related code.
 */
namespace kepler::cli {

    /**
     * @brief The Config struct contains all configuration
     * which can be set in the command-line.
     */
    struct Config {
        bool show_help = false;
        bool run_tests = false;
        std::vector<std::string> commands;
    } config;

    /**
     * @brief The command-line parser.
     */
    auto cli
            = lyra::help(config.show_help).description("Here is a list of all command-line arguments.")
                | lyra::opt(config.run_tests)["-t"]["--test"]("Run the test suite.")
                | lyra::arg(config.commands, "workspace|test tags")("Which source file (.kpl) to execute "
                                                                    "if <-t|--test> is not set, else specific "
                                                                    "tags to run tests for.");

}