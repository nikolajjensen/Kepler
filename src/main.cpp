
#include <iostream>
#include <catch2/catch_session.hpp>
#include <lyra/lyra.hpp>
#include "cli.h"
#include "core/evaluation/execution.h"
#include "core/literals.h"

using namespace kepler;

/**
 * Main method - entry point of the program.
 */
int main(int argc, char* argv[]) {
    auto result = kepler::cli::cli.parse({argc, argv});

    if (!result) {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        return 1;
    }

    if(kepler::cli::config.show_help) {
        // Show help.
        std::cout << kepler::cli::cli << "\n";
        return 0;
    } else if(kepler::cli::config.run_tests) {
        // Run tests.
        Catch::Session session;
        if(!kepler::cli::config.commands.empty()) {
            session.configData().testsOrTags = kepler::cli::config.commands;
        }
        return session.run();
    } else if(kepler::cli::config.commands.empty()) {
        // Run REPL.
        run_repl();
    } else if(kepler::cli::config.commands.size() == 1) {
        // Run file.
        return run_file(kepler::cli::config.commands[0]);
    } else {
        std::cerr << "Command error: only one file can be specified." << std::endl;
    }
}