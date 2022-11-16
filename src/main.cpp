#include <iostream>
#include "core/Lexer.h"
/*
int main() {
    std::string test = "ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    std::string small_test = "ABC←FN";
    Lexer lexer(small_test, true);

    std::vector<Token> result = lexer.run();

    std::cout << "Result of running Lexer: " << TokenType::AssignmentArrow << ":" << std::endl;
    for(auto& r : result) {
        std::cout << r << std::endl;
    }
    return 0;
}
*/


int main() {
    std::string test = "ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    std::cout << "Here we have a normal string with Unicode symbols: " << test << std::endl;
    std::cout << "Here we have the fourth character: " << test[3] << std::endl;

    std::u32string test2 = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    std::cout << "Here we have the fourth character of a UTF string: " << test2[2] << std::endl;




    std::cout << "Hello, World!" << std::endl;
    return 0;
}