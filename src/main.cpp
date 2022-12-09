
#define BOOST_SPIRIT_X3_UNICODE
#include <iostream>
#include "core/lexer/rules.h"
#include "core/lexer/config.h"

#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3.hpp>
#include <uni_algo/conv.h>

#include "core/datatypes.h"
#include "core/env/printers.h"

int main() {
    std::cout << "An APL Lexer written in Spirit X3.\n";
    namespace x3 = boost::spirit::x3;
    using kepler::lexer::iterator_type;

    std::u32string input_str = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    kepler::List<kepler::Char> input(input_str.begin(), input_str.end());

    std::cout << "Paring input: '" << uni::utf32to8(input_str) << "'" << std::endl;

    kepler::List<kepler::Token> tok_list;
    iterator_type iter = input_str.begin();
    iterator_type const end = input_str.end();

    using x3::with;
    using kepler::lexer::error_handler_type;
    using kepler::lexer::error_handler_tag;
    error_handler_type error_handler(iter, end, std::cerr);

    auto const parser = with<error_handler_tag>(std::ref(error_handler))
            [
                    kepler::lexer::token_list()
            ];


    auto start = std::chrono::high_resolution_clock::now();
    bool r = phrase_parse(iter, end, parser, kepler::lexer::skipper(), tok_list);
    auto stop = std::chrono::high_resolution_clock::now();

    auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    std::cout << "Took " << us << " µs (" << (us / 1000.0) << " ms)" << std::endl;

    if(r && iter == end) {
        std::cout << "-------------------------\n";
        std::cout << "Lexing succeeded\n";
        std::cout << "-------------------------\n";
        kepler::printers::TokenListPrinter printer;
        printer(tok_list);
    } else {
        std::cout << "-------------------------\n";
        std::cout << "Lexing failed\n";
        std::cout << "-------------------------\n";
    }

    return 0;
}