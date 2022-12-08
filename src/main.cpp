
#define BOOST_SPIRIT_X3_UNICODE
#include <iostream>
#include "core/lexer/models.h"
#include "core/lexer/models_adapted.h"
#include "core/lexer/rules.h"
#include "core/lexer/config.h"
#include "core/lexer/models.h"
#include "core/lexer/model_processing.h"

#include <boost/spirit/home/x3/support/utility/error_reporting.hpp>
#include <boost/spirit/home/x3.hpp>
#include <uni_algo/conv.h>

int main() {
    std::cout << "An APL Lexer written in Spirit X3.\n";

    namespace x3 = boost::spirit::x3;

    using kepler::lexer::iterator_type;

    std::u32string str32 = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E23,⍴'ABC' ⋄ F←(⍺+⍵) ⍝COMMENT";

    std::cout << "Paring input: '" << uni::utf32to8(str32) << "'" << std::endl;

    kepler::lexer::models::TokenList tok_list;
    iterator_type iter = str32.begin();
    iterator_type const end = str32.end();

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
        kepler::lexer::model_processing::TokenListPrinter printer;
        printer(tok_list);
    } else {
        std::cout << "-------------------------\n";
        std::cout << "Lexing failed\n";
        std::cout << "-------------------------\n";
    }

    return 0;
}