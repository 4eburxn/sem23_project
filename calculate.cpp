#include"headers/calculate.h"

double statement(char);
extern Token_stream ts;
void clean_up_mess();

void calculate (char end = ';')
{
  while (true)
    try
    {
      cout << prompt;
      Token t = ts.get(end);
      while (t.kind == print)
        t = ts.get(end);
      if (t.kind == quit)
        return;

      ts.putback(t);
      cout << result << statement(end) << endl;
    }
    catch (runtime_error& e)
    {
      cerr << e.what() << endl;
      clean_up_mess();
    }
}