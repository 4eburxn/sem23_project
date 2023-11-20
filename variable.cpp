#include"headers/variable.h"

#include<math.h>
Variable::Variable(string n, double v){
  name = n;
  value = v;
}

#ifndef VAR_TABLE
  #define VAR_TABLE
  vector<Variable> var_table;
  vector<Function> func_table{{"sin"},{"cos"},{"tg"},{"ctg"},{"sum"},{"pow"}};

#endif


double get_value (string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return var_table[i].value;
  for (int i = 0; i < func_table.size(); ++i)
    if (func_table[i].name == s)
      return func_table[i].calculate();

  error("get: undefined name ", s);
}

void set_value (string s, double d)
{
  for (int i = 0; i <= var_table.size(); ++i)
  {
    if (var_table[i].name == s)
    {
      var_table[i].value = d;
      return;
    }
  }

  error("set: undefined name ", s);
}

bool is_declared (string s)
{
  for (int i = 0; i < var_table.size(); ++i)
    if (var_table[i].name == s)
      return true;
  for (int i = 0; i < func_table.size(); ++i)
    if (func_table[i].name == s)
      return true;
  return false;
}

double define_name (string var, double val)
{
  if (is_declared(var))
    error(var, " declared twice(or used as function)");

  var_table.push_back(Variable{var, val});

  return val;
}

double expression (char);
extern Token_stream ts;
double declaration (char end = ';')
{
  Token t = ts.get(end);
  if (t.kind == let)
    error("the name can't be \"let\"!");

  if (t.kind != name)
    error("name expected in declaration");

  string var = t.name;
  if (is_declared(var))
    error(var, " declared twice(or used as function)");

  t = ts.get(end);
  if (t.kind != '=')
    error("'=' missing in declaration of ", var);

  return define_name(var, expression(end));
}

double statement (char end = ';')
{
  Token t = ts.get(end);
  switch (t.kind)
  {
  case let:
    return declaration(end);
  default:
    ts.putback(t);
    return expression(end);
  }
}
Function::Function(string n){
    name = n;
    for(int i = 0;i<names.size();i++){
      if(names[i] == name){
        number = i;
        return;
      }
    }
    error("bad name for function");
}
double term(char);

extern Token_stream ts;

vector<double> Function::get_data()
{
  char ch = 'd';
  double buff;
  vector<double> ret_vec;
  cin.get();
  while(ch != ')'){
    ret_vec.push_back(term('f'));
    if(ts.get('f').kind != ';'){
      break;
    }
    cin.get(ch);
    cin.putback(ch);
  }
  cin.get();
  return ret_vec;
}
double Function::calculate()
{
  auto data = get_data();
  double ret = 0;
  switch (number)
  {
    case 0: // sin
      if (data.size() != 1){
        error("incorrect number of args");
      }
      return sin(data[0]);
    case 1: // cos
      if (data.size() != 1){
        error("incorrect number of args");
      }
      return cos(data[0]);
    case 2: // tg
      if (data.size() != 1){
        error("incorrect number of args");
      }
      return tan(data[0]);
    case 3: // ctg
      if (data.size() != 1){
        error("incorrect number of args");
      }
      return 1/tan(data[0]);
    case 4: // sum
      if (data.size() < 1){
        error("incorrect number of args");
      }
      for(auto i:data)
        ret+=i;
      return ret;
    case 5: // pow
      if (data.size() != 2){
        error("incorrect number of args");
      }
      return pow(data[0],data[1]);
  }
  return 0.0;
}
