
#include <iostream>

#include <uni_algo/conv.h>

#include "core/datatypes.h"
#include "core/env/printers.h"
#include <vector>

#include "core/env/environment.h"
#include "core/datatypes.h"
#include "core/lexer/lexer.h"
#include "core/parser/parser.h"
#include "core/interpreter/interpreter.h"
#include "core/parser/token_converter.h"
#include <boost/variant.hpp>
#include "core/error/error.h"


using namespace kepler;

void test() {
    Environment env = Environment();
    Session *session = env.spawn_session();
    //session->insert_line("ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E2,⍴'ABC' ⍝COMMENT");
    session->insert_line("+2");
    //session->insert_line("-1.22E¯1");
    //session->insert_line("+2J1");
    //session->insert_line("-2");
    //session->insert_line("-1.2");

    session->evaluate();
    if(session->currentContext->error) {
        std::cout << session->currentContext->error->type() << ": " << session->currentContext->error->why() << "\n";

        if(session->currentContext->error->where() != -1) {
            std::cout << "    " << uni::utf32to8(session->currentContext->currentLine) << "\n";
            std::cout << "    ";
            for (int i = 0; i < session->currentContext->error->where(); ++i) {
                std::cout << " ";
            }
            std::cout << "^" << "\n";
        }
    }
}

#include <catch2/catch_session.hpp>
#include <lyra/lyra.hpp>
#include "cli.h"
#include "repl/repl.h"

void repl() {
    Environment env = Environment();
    Session *session = env.spawn_session();
    kepler::tui::repl(*session);
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
        // For now, just run the test.
        std::cout << "Directly executing workspaces is not implemented yet." << std::endl;
        return 1;
    } else {
        std::cerr << "Command error: only one file can be specified." << std::endl;
    }
}