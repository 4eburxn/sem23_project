#include <stdio.h>
#include <ncurses.h>
#include <iostream>
#include "headers/input.h"
#include"headers/matrix_window.h"
#include"headers/Editor.h"
#define WIDTH 30
#define HEIGHT 10 

int startx = 0;
int starty = 0;

int n_choices = 5;
void print_menu(WINDOW *menu_win, int Hy);

int main()
{	WINDOW *menu_win;
	int Hy = 1,Hx = 1;
	int choice = 0;
	int c;
    //std::cerr<<"adfsadfa";
	int i=0;
	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    start_color();

/**/



    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    attron(COLOR_PAIR(1));
    printw("This should be printed in black with a red background!\n");

    attron(COLOR_PAIR(2));
    printw("And this in a green background!\n");
    refresh();
	
    //std::cout<<"adfsadfa";
	
    //std::vector<std::vector<double>> mmx{{22.0,2.0,3.0,-1.0,-2.0},
    //                                             {4.0,5.0,6.0,-1.0,-2.0},
    //                                             {7.0,8.0,9.0,-1.0,-2.0},{7.0,8.0,9.0,-11298374912834700.0,-2.0},{7.0,8.0,9.0,-1.0,-2.0}};
	//std::vector<std::vector<double>> mmx{{22.0,2.0,3.0,-1.0,-2.0,-2.0,-2.0},
    //                                     {4.0,5.0,6.0,-1.0,-2.0,-567.0,-2.0},
    //                                     {7.0,8.0,9.0,-1.0,-2.0,-123.0,-2.0},
	//									 {7.0,8.0,9.0,-11298374912834700.0,-2.0,-2.0,-2.0},
	//									 {7.0,8.0,9.0,-1.0,-2.0,-3.0,-2.0}};
	std::vector<std::vector<double>> mmx{{1.,2.,3.,1.,100.,3.},
										 {4.,5.,6.,4.,5.,6.},
										 {7.,8.,9.,7.,8.,9.},
										 {-1.,-2.,-3.,-1.,-2.,-3.},
										 {-4.,-5.,-6.,-4.,-5.,-6.},
										 {-7.,-8.,-9.,-10.,-11.,-12.}};
	
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
		WINDOW *matrix = newwin(11, 48, 3,3);
		std::vector<std::string> l{"ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss","ssss"};
		Buffer a;
		a.lines = std::vector<std::string>(l);
		a.lines.reserve(1000);
		start_editor(matrix,a);

		keypad(matrix, true);
		Input b;
	while(1)
	{	
		mvprintw(23, 0,"Hx:%3d Hy:%3d", Hx, Hy,mmx);
		drow_matrix(matrix,mmx,Hy-1,Hx-1);
		mvprintw(14, 12,"%f",mmx[Hy-1][Hx-1]);
		refresh();
		b = GetInput(matrix);
		if(b.type == Input::Type::button)
			{	
				switch (b.ch){
				case KEY_UP:
					if(Hy == 1)
						Hy = size(mmx);
					else
						--Hy;
					break;
				case KEY_DOWN:
					if(Hy == size(mmx))
						Hy = 1;
					else 
						++Hy;
					break;
				case KEY_LEFT:
					if(Hx == 1)
						Hx = size(mmx[0]);
					else
						--Hx;
					break;
				case KEY_RIGHT:
					if(Hx == size(mmx[0]))
						Hx = 1;
					else 
						++Hx;
					break;
				case 27:
					refresh();
					endwin();
					std::cout<<"\nYou exit\n";
					return 0;
				default:
					mvprintw(24, 0,"other char pressed (%3d) Hopefully it can be printed as '%c'", b.ch, b.ch);
					break;
			}}
		else if(b.type == Input::Type::ch){
			switch (b.ch){
				case 10:
					choice = Hy;
					break;
				default:
					mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", b.ch, b.ch);
					refresh();
					break;
			}
		}
		else{
			mvprintw(24, 0,"bad char pressed (%3d) Hopefully it can be printed as '%c'", b.ch, b.ch);
			refresh();
		}
	}
	clrtoeol();
	refresh();
	endwin();
	return 0;
}
