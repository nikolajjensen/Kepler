
#define BOOST_SPIRIT_X3_UNICODE
#include <iostream>
#include "core/lexer/models.h"
#include "core/lexer/models_adapted.h"
#include "core/lexer/rules.h"
#include "core/lexer/model_processing.h"
#include <uni_algo/conv.h>

int main() {
    std::cout << "An APL Lexer written in Spirit X3.\n";
    //std::cout << "Give me an employee of the form:"
    //          << "employee{age, \"forename\", \"surname\", salary}\n";
    //std::cout << "Type [q or Q] to quit.\n";

    namespace x3 = boost::spirit::x3;
    using boost::spirit::x3::unicode::space;
    using boost::spirit::x3::unicode::lit;
    using iterator_type = std::u32string::const_iterator;
    using kepler::lexer::token_list;
    using kepler::lexer::skipper;

    std::u32string str32 = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⋄ F←(⍺+⍵) ⍝COMMENT";

    std::cout << "Paring input: '" << uni::utf32to8(str32) << "'" << std::endl;

    kepler::lexer::models::TokenList tok_list;
    iterator_type iter = str32.begin();
    iterator_type const end = str32.end();

    bool r = phrase_parse(iter, end, token_list(), skipper(), tok_list);

    if(r && iter == end) {
        std::cout << "-------------------------\n";
        std::cout << "Parsing succeeded\n";
        std::cout << "-------------------------\n";
        kepler::lexer::model_processing::TokenListPrinter printer;
        printer(tok_list);
    } else {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }

    /*
    std::string str;
    while(std::getline(std::cin, str)) {
        if(str.empty() || str[0] == 'q' || str[0] == 'Q') {
            break;
        }



        std::u32string str32 = uni::utf8to32u(str);

        std::cout << "Paring input: '" << uni::utf32to8(str32) << "'" << std::endl;

        kepler::lexer::models::TokenList tok_list;
        iterator_type iter = str32.begin();
        iterator_type const end = str32.end();

        bool r = phrase_parse(iter, end, token_list(), skipper(), tok_list);

        if(r && iter == end) {
            std::cout << "-------------------------\n";
            std::cout << "Parsing succeeded\n";
            std::cout << "-------------------------\n";
            kepler::lexer::model_processing::TokenListPrinter printer;
            printer(tok_list);
        } else {
            std::cout << "-------------------------\n";
            std::cout << "Parsing failed\n";
            std::cout << "-------------------------\n";
        }
    }
    */

    std::cout << "Bye...\n";
    return 0;
}