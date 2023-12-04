#ifndef EDITOR_H
#define EDITOR_H

#include "Buffer.h"

#include <ncurses.h>
#include "input.h"

#define CED_TITLE "ceditor"
#define CED_VERSION "v0.1.0 test"

void start_editor(WINDOW* win, Buffer& buf);  


class Editor
{
    private:
        WINDOW* win;
        int x, y;
        int lowerbound;
        char mode;
        bool raiseflag;
        string status;
        string cmd;
        string filename;

        string tos(int);

        bool execCmd();

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void deleteLine();
        void deleteLine(int i);


    public:
        Buffer* buff;
        bool upstatus;

        Editor();
        Editor(Buffer&,WINDOW*);

        char getMode() {return mode;}

        void handleInput(Input);
        void printBuff();
        void printStatusLine();
        void updateStatus();

};


#endif
