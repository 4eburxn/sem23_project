#include "headers/Editor.h"

#include <fstream>
#include <iostream>
#include <sstream>


#include <ncurses.h>
#include "headers/Editor.h"
#include "headers/input.h"

// Initializes the curses.h

void start_editor(WINDOW* win, Buffer& buf)
{
    Editor ed;
	keypad(win, true);
    // Initialize filename
    ed = Editor(buf,win);
    while(ed.getMode() != 'n')
    {
        if(ed.upstatus)
            ed.updateStatus();
        ed.printStatusLine();

        ed.printBuff();
        ed.handleInput(GetInput(win));
        
    }
		keypad(win, false);

    refresh();
}


Editor::Editor(Buffer& bf, WINDOW* win_)
{

    win=win_;
    x = 0; y = 0; mode = 'i';
    cmd = "";
    lowerbound = 0;
    raiseflag = false;                  // for debugging
    upstatus = true;
    status = "Normal Mode";
    buff = new Buffer(bf);


}

Editor::Editor()
{
    /* For a new file */
    x = 0; y = 0; mode = 'n';
    cmd = "";
    upstatus = true;
    raiseflag = false;
    status = "Normal Mode";
    lowerbound = 0;
    filename = "";
    buff = new Buffer();
    buff->appendLine("");
}

void Editor::updateStatus()
{
    switch(mode)
    {
        case 'n':
            if(cmd.empty())
                status = string(CED_TITLE) + " " + string(CED_VERSION);
            else
                status = cmd;
            break;
        case 'i':
            status = "Insert Mode";
            break;
        case 'x':
            status = "Exiting";
            break;
    }
    status += "\tCOL: " + tos(x) + "\tROW: " + tos(lowerbound);
}

void Editor::handleInput(Input input)
{
    werase(win);
    int c = input.ch;
    upstatus = true;
    switch(mode)
    {
        case 'n':
            switch(c)
            {
                case KEY_LEFT:
                    moveLeft();
                    break;
                case KEY_RIGHT:
                    moveRight();
                    break;
                case KEY_UP:
                    moveUp();
                    break;
                case KEY_DOWN:
                    moveDown();
                    break;
                case KEY_ENTER:
                case 10:
                    // Execute the command
                    execCmd();
                    break;
                case 27:
                    // Escape/Alt key
                    // clears command
                    cmd.clear();
                    break;
                case 127:
                case KEY_BACKSPACE:
                case KEY_DC:
                    // Removes last character
                    if(!cmd.empty())
                        cmd.erase(cmd.length()-1, 1);
                    break;
                default:
                    // Add character to command
                    cmd += string(1, char(c));
                    break;
            }
            break;
        case 'i':
            switch(c)
            {
                case 27:
                    // Escape/Alt key
                    mode = 'n';
                    break;
                case 127:
                case KEY_BACKSPACE:
                    // The Backspace
                    if(x == 0 && lowerbound +y > 0)
                    {
                        x = buff->lines[y-1].length();
                        // Bring line down
                        buff->lines[lowerbound +y-1] += buff->lines[y];
                        // Delete the line
                        deleteLine();
                        moveUp();
                    }
                    else if(x > 0)
                    {
                        buff->lines[lowerbound +y].erase(--x, 1);
                    }
                    break;
                case KEY_DC:
                    // The Delete key
                    if(x == buff->lines[lowerbound +y].length() && lowerbound +y != buff->lines.size()-1)
                    {
                        // Bring line down
                        buff->lines[lowerbound +y] += buff->lines[lowerbound +y+1];
                        // Delete the line
                        deleteLine(lowerbound +y+1);
                    }
                    else
                    {
                        buff->lines[lowerbound +y].erase(x, 1);
                    }
                    break;
                case KEY_LEFT:
                    moveLeft();
                    break;
                case KEY_RIGHT:
                    moveRight();
                    break;
                case KEY_UP:
                    moveUp();
                    break;
                case KEY_DOWN:
                    moveDown();
                    break;
                case KEY_ENTER:
                case 10:
                    // Bring rest of line down
                    //std::cout <<(y+lowerbound+1 - (int)buff->lines.size())<<std::endl;
                    if(x <= buff->lines[y+lowerbound].length()-1)
                    {
                        // Put rest of line on new line
                        buff->insertLine(buff->lines[y+lowerbound].substr(x, buff->lines[y+lowerbound].length()-x), y+lowerbound+1);
                        // Remove that part of the line
                        buff->lines[y+lowerbound].erase(x, buff->lines[y+lowerbound].length()-x);
                    }
                    else
                        buff->insertLine("",y+lowerbound+1);
                    
                    x = 0;
                    moveDown();
                    break;
                case KEY_BTAB:
                case KEY_CTAB:
                case KEY_STAB:
                case KEY_CATAB:
                case 9:
                    // The tab
                    buff->lines[y+lowerbound].insert(x, 4, ' ');
                    x+=4;
                    break;
                default:
                    buff->lines[y+lowerbound].insert(x, 1, char(c));
                    x++;
                    break;
            }
            break;
        default:;
    }
    if(y>buff->lines.size()){
        y = buff->lines.size()-1;
    }
    if(x>buff->lines[y+lowerbound].size()-1){
        x = buff->lines[y+lowerbound].size();
    }
}

void Editor::deleteLine()
{
    buff->removeLine(y);
}

void Editor::deleteLine(int i)
{
    buff->removeLine(i);
}

void Editor::moveLeft()
{
    if(x-1 >= 0)
    {
        x--;
        move(y, x);
    }
}

void Editor::moveRight()
{
    if(x+1 < win->_maxx && x+1 <= buff->lines[y+lowerbound].length())
    {
        x++;
        move(y, x);
    }
}

void Editor::moveUp()
{
    if(y-1 >= 0)
    {
        y--;
    }
    else if(y-1 < 0 && lowerbound > 0)
    {
        lowerbound--;
    }
    if(x >= buff->lines[lowerbound +y].length())
        x = buff->lines[lowerbound +y].length();
    move(y, x);
}

void Editor::moveDown()
{
    if(y+1 < win->_maxy-1 && lowerbound + y+1 < buff->lines.size()-1)
    {
        y++;
    }
    else if(lowerbound+y+1 < buff->lines.size())
    {
        raiseflag = true;
        lowerbound++;
    }
    if(x >= buff->lines[lowerbound +y].length())
        x = buff->lines[lowerbound +y].length();
    move(y, x);
}

void Editor::printBuff()
{
    int lc = 0;                     // Line count
    for(int i=lowerbound; lc<win->_maxy-1 && i<buff->lines.size(); i++)
    {
        if(i >= buff->lines.size())
        {
        }
        else
        {
            mvwprintw(win,lc, 0, buff->lines[i].c_str());
        }
        wclrtoeol(win);
        lc++;
    }

    mvprintw(2,2,"x:%d  y:%d",x,y);
    refresh();
    wmove(win,y, x);
}

void Editor::printStatusLine()
{
    if(raiseflag)
        wattron(win,A_BOLD);
    wattron(win,A_REVERSE);
    mvwprintw(win,win->_maxy-1, 0, status.c_str());
    clrtoeol();
    if(raiseflag)
        wattroff(win,A_BOLD);
    wattroff(win,A_REVERSE);
}


string Editor::tos(int n)
{
    stringstream ss;
    ss << n;
    return ss.str();
}

bool Editor::execCmd()
{
    if(cmd == "i")
        mode = 'i';
    else if(cmd == "x")
        mode = 'x';
    else if(cmd == "s")
    {
        upstatus = false;
    }
    return true;
}
