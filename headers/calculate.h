#ifndef TOKEN_TOKENSTREAM
    #define TOKEN_TOKENSTREAM
    #include"token_tokenstream.h"
#endif
#ifndef CONSTANTS
    #define CONSTANTS
    constexpr char quit = 'q';
    constexpr char print = ';';
    constexpr char number = '8';
    constexpr char name = 'a';
    constexpr char let = 'L';

    const string prompt = "> ";
    const string result = "= ";
    const string declkey = "let";
#endif

void calculate (char);