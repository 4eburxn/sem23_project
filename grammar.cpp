#include"headers/grammar.h"

extern Token_stream ts;
double expression (char);
double get_value (string s);

double primary (char end = ';')
{
  Token t = ts.get(end);
  switch (t.kind)
  {
  case '(':
  {
    double d = expression(end);
    t = ts.get(end);
    if (t.kind != ')')
      error("'(' expected");
    return d;
  }

  case '-':
    return -primary(end);
  case '+':
    return +primary(end);

  case number:
    return t.value;

  case name:
    return get_value(t.name);
  default:
    error("primary expected");
  }
}

double term (char end = ';')
{
  double left = primary(end);

  while (true)
  {
    Token t = ts.get(end);

    switch (t.kind)
    {
    case '*':
      left *= primary(end);
      break;

    case '/':
    {
      double d = primary(end);
      if (d == 0)
        error("divide by zero");
      left /= d;
      break;
    }

    default:
      ts.putback(t);
      return left;
    }
  }
}

double expression (char end)
{
  double left = term(end);

  while (true)
  {
    Token t = ts.get(end);

    switch (t.kind)
    {
    case '+':
      left += term(end);
      break;

    case '-':
      left -= term(end);
      break;
    case number:
      error("incorrect input(use \";\" to see result)");
    default:
      ts.putback(t);
      return left;
    }
  }
}