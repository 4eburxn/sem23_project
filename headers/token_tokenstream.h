#ifndef STD_LIB_FACILITIES
    #define STD_LIB_FACILITIES
    #include"std_lib_facilities.h"
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


struct Token
{
  char kind;
  double value;
  string name;

  Token(char);

  Token(char, string);

  Token(char, double);
};

class Token_stream
{
  bool full{false};
  Token buffer{'\0'};


public:
  Token_stream();

  Token get (char);
  void putback (Token);

  void ignore (char);
};
