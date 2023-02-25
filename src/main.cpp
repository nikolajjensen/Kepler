
#include <iostream>
#include "core/system.h"
#include <catch2/catch_session.hpp>
#include <lyra/lyra.hpp>
#include "cli.h"
#include "core/helpers/printers.h"

using namespace kepler;

void repl() {
    System env = System();
    Session* session = env.spawn_session();
    session->immediate_execution_mode();
}

int main(int argc, char* argv[]) {
    auto result = kepler::cli::cli.parse({argc, argv});

    if (!result) {
        std::cerr << "Error in command line: " << result.message() << std::endl;
        return 1;
    }

    if(kepler::cli::config.show_help) {
        std::cout << kepler::cli::cli << "\n";
        return 0;
    } else if(kepler::cli::config.run_tests) {
        Catch::Session session;
        if(!kepler::cli::config.commands.empty()) {
            session.configData().testsOrTags = kepler::cli::config.commands;
        }
        return session.run();
    } else if(kepler::cli::config.commands.empty()) {
        // Run REPL.
        //repl();
        repl();
    } else if(kepler::cli::config.commands.size() == 1) {
        // Try to run the file.
        std::cout << "Directly executing workspaces is not implemented yet." << std::endl;
        return 1;
    } else {
        std::cerr << "Command error: only one file can be specified." << std::endl;
    }
}