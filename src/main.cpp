#include <iostream>
/*
#include <uni_algo/case.h>
#include "uni_algo/conv.h"
#include "core/Lexer.h"
#include "core/CharacterSet.h"
#include <regex>
*/
#include "core/Lexer.h"
#include "core/CharacterSet.h"

int main() {
    CharList test1 = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    CharList test2 = U"+\\-⌿'()'∘.='plus(square(a),plus(square(b),times(2,plus(a,b)))'";
    CharList test3 = U"Mean←{+/⍵÷⍴⍵}  ⍝ Mean program";
    CharList test4 = U" ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";



    Lexer lexer(test4, true);

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<Token> result = lexer.run();
    auto stop = std::chrono::high_resolution_clock::now();

    std::cout << "Result of running Lexer:" << std::endl;
    for(auto& r : result) {
        std::cout << r << std::endl;
    }
    std::cout << "Result contains " << result.size() << " tokens." << std::endl;
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
    std::cout << "Took " << us << " µs (" << (us / 1000.0) << " ms)" << std::endl;
    return 0;

/*
    Character c1({U"⌽", U"2"});
    Character c2({U"⌽"});

    std::cout << c1 << std::endl;
    std::cout << c2 << std::endl;
    */
}

/*
unsigned int t1() {
    return 2;
}

unsigned int t2() {
    return 1;
}

int main() {

    std::string test = "ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    std::cout << "Here we have a normal string with Unicode symbols: " << test << std::endl;
    std::cout << "Here we have the fourth character: " << test[3] << std::endl;

    std::u32string test2 = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    std::cout << "Here we have the fourth character of a UTF string: " << test2[2] << std::endl;


    std::vector<std::string> vec8;
    std::u32string test3 = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";
    for (char32_t c : test3) // Convert the code points to a vector of UTF-8 code units
        vec8.emplace_back(uni::utf32to8(std::u32string(1, c)));
    std::for_each(vec8.begin(), vec8.end(), [](auto s) { std::cout << s; });
    std::cout << '\n';

    char32_t ch = u'←';

    std::cout << (test3[3] == ch) << std::endl;
    std::cout << uni::utf32to8(std::u32string(1, test3[3]))  << std::endl;

    std::cout << (t1() || t2()) << std::endl;

    std::cout << "Hello, World!" << std::endl;


    std::u32string test3 = U"ABC←FN ⎕⌽[1+0] DEF[1;5 6]×3.45E4,⍴'ABC' ⍝COMMENT";

    auto l = uni::utf32to8(Character::s_alpha + U"|" + Character::s_omega);

    std::regex r("←");

    std::smatch m;
    const std::string s = uni::utf32to8(test3);
    if(std::regex_search(s.begin() + 6, s.end(), m, r)) {
        std::cout << "HELLO: " << m.str(0) << "\n";
    }
    return 0;
}
 */