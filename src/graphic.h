#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__ 1

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Enumerations.H>
#include "determinant.h"

class Window_Maker
{
private:
    Fl_Window *window;
public:
    void Window(int width, int height);
    Fl_Button *Button(int posX, int posY, int width, int height, const char *name);
};


namespace Main_Window{
    static Window_Maker MAKE;
    void init();

    enum class Event{
        file_exp_called,
        matrix_chaenged,
        menu_called,
        error_catched
    };


    void event_handler(Event type);

    void matrix_drow(int posX, int posY, int width, int height, const char *title, Matrix matrix);
    void matrix_redrow();
    
    void refreash();
}
namespace Main_Window{
    static Window_Maker MAKE;
}
#endif //__GRAPHIC_H__