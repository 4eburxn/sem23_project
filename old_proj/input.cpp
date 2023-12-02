#include "headers/input.h"
#include <ctype.h>

Input::Input(int chin)
{
    ch = chin;
    switch (chin)
    {
    case KEY_UP:
    case KEY_RIGHT:
    case KEY_LEFT:
    case KEY_DOWN:
    case 27:
        type = Type::button;
        break;
    default:
        if(isalnum(chin) || chin == '.' || chin == ',' || chin == '(' || chin == ')' || chin == '\n' || chin == ' '){
            type = Type::ch;
            break;
        }
        type = Type::broken;
        break;
    }
}
Input GetInput(WINDOW* menu_win)
{
    return Input(wgetch(menu_win));
}