#ifndef __INPUT_H__
#define __INPUT_H__

#include<ncurses.h>
#include<curses.h>


class Input
{
public:
    enum class Type{button, ch, broken};
    Type type;
    int ch;
    Input(){};
    Input(int);
};



Input GetInput(WINDOW*);



#endif // __INPUT_H__
