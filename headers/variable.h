#ifndef STD_LIB_FACILITIES
    #define STD_LIB_FACILITIES
    #include"std_lib_facilities.h"
#endif
#ifndef TOKEN_TOKENSTREAM
    #define TOKEN_TOKENSTREAM
    #include"token_tokenstream.h"
#endif
extern Token_stream ts;
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


extern Token_stream ts;
struct Variable
{
  string name;
  double value;

  Variable(string, double);
};

struct Function
{
  vector<string> names{{"sin"},{"cos"},{"tg"},{"ctg"},{"sum"},{"pow"}};
  Function(string);



  int number;
  string name;
  double calculate();
  vector<double> get_data();
};

double get_value (string);

void set_value (string, double);

bool is_declared (string);

double define_name (string, double);

double declaration (char);

double statement (char);