
#include <iostream>
#include <catch2/catch_session.hpp>
#include <lyra/lyra.hpp>
#include "cli.h"
#include "core/execution.h"

using namespace kepler;
/*
void test() {
    try {
        //std::u32string one = U"FN←{⍺+⍵} ⋄ FN/⍳10";
        std::u32string one = U"fn←{ q←{⍺÷⍵} ⋄ ⍵ q ⍺}";
        //std::u32string one = U"2+5";
        //std::u32string one = U"FN←{⍺+⍵}◊1 FN 2";
        //std::u32string one = U"Val←123◊1 Val 2";

        std::cout << "Input: " << uni::utf32to8(one) << "\n" << std::endl;
        std::vector<Char> input{one.begin(), one.end()};

        Tokenizer tokenizer;
        auto tokens = tokenizer.tokenize(&input);

        Parser parser(tokens);
        auto ast = parser.parse();

        Interpreter interpreter(*ast, *ast->symbol_table);
        auto output = interpreter.interpret();

        std::cout << output.to_string() << std::endl;

    } catch (kepler::error& err) {
        std::cout << "ERROR: " << err.to_string() << std::endl;
    }
}
 */

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
        run_repl();
        //test();
    } else if(kepler::cli::config.commands.size() == 1) {
        // Try to run the file.
        return run_file(kepler::cli::config.commands[0]);
        //std::cout << "Directly executing workspaces is not implemented yet." << std::endl;
        //return 1;
    } else {
        std::cerr << "Command error: only one file can be specified." << std::endl;
    }
}