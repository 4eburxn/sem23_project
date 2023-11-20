#include"headers/token_tokenstream.h"




Token::Token(char ch) : kind{ch}, value{0} {}

Token::Token(char ch, string s) : kind{ch}, name{s} {}

Token::Token(char ch, double val) : kind{ch}, value{val} {}

Token_stream::Token_stream() {

}

void Token_stream::putback(Token t)
{
  if (full)
    error("putback() into a full buffer");

  buffer = t;
  full = true;
}

Token Token_stream::  get(char end = ';')
{
  if (full)
  {
    full = false;
    return buffer;
  }

  char ch;
  cin >> ch;
  if ('f' == end){ // режим функции
    if(ch == ')'){
      
      cin.putback(ch);
      return Token{';'};
    }
    if(ch == ','){
      return Token{';'};
    }
  }
  switch (ch)
  {
  case '(':
  case ')':
  case '+':
  case '-':
  case '*':
  case '/':
  case '%':
  case ';':
  case '=':
  case quit:
    return Token{ch};

  case '.':
  case '0':
  case '1':
  case '2':
  case '3':
  case '4':
  case '5':
  case '6':
  case '7':
  case '8':
  case '9':
  {
    cin.putback(ch);
    double val;
    cin >> val;
    return Token{number, val};
  }

  default:
    if (isalpha(ch))
    {
      string s;
      s += ch;
      while (cin.get(ch) && (isalpha(ch) || isdigit(ch)))
        s += ch; // было изменено с = на +=
      cin.putback(ch);

      if (s == declkey)
        return Token{let};
      return Token{name, s};
    }
    error("Bad token+");
  }
}


void Token_stream::ignore(char c)
{
  if (full && c == buffer.kind)
  {
    full = false;
    return;
  }
  full = false;

  char ch;
  while (cin >> ch)
    if (ch == c)
      return;
}


Token_stream ts;

void clean_up_mess () { 
  ts.ignore(print);
}