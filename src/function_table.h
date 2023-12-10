#ifndef __FUNCTION_TABLE_H__
#define __FUNCTION_TABLE_H__ 1

#include <algorithm>

#include "graphic.h"
#include "determinant.h"

/*-----------------------NewFileDialog------------------------*/


void file_chooser_button_CB(Fl_Widget *, void*m);

void cancel_button_CB(Fl_Widget *, void*m);

void ok_button_CB(Fl_Widget *, void*m);

/*-----------------------Main_Window------------------------*/

void new_file_CB(Fl_Widget *, void*m);

void arrow_down_pressed(Fl_Widget *, void*m);
void arrow_left_pressed(Fl_Widget *, void*m);
void arrow_up_pressed(Fl_Widget *, void*m);
void arrow_right_pressed(Fl_Widget *, void*m);

void browser_CB(Fl_Widget *, void*m);   


#endif // __FUNCTION_TABLE_H__