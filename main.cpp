#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include "headers/input.h"
#include"headers/matrix_window.h"
#include"headers/Editor.h"
#define WIDTH 30
#define HEIGHT 10 

void print_menu(WINDOW *menu_win, int Hy);

int main(){
	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    start_color();




	clrtoeol();
	refresh();
	endwin();
	return 0;
}
