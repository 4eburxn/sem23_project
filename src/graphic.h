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
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_File_Chooser.H>

class WINDOW
{
public:
    Fl_Window *window;
    void MakeWindow(int width, int height);
    Fl_Button *MakeButton(int posX, int posY, int width, int height, const char *name);
    Fl_Menu_Bar *MakeBar(int posX, int posY, int width, int height, Fl_Menu_Item menuitems[]);
};




class FileBrowser : public WINDOW{
public:
    void init();
    FileBrowser();
    Fl_File_Chooser *browser;
};


class Main_Window : public WINDOW{
public:
    void init();


    FileBrowser brow;
    std::vector<Fl_Button *> buttons = std::vector<Fl_Button *>((size_t)10, nullptr);  //более 10 кнопок нам не потребуется
    enum class Buttons{
        mode_change=0,
        open_file_exp=1
    };
    enum class Event{
        file_exp_called=1,
        matrix_chaenged=2,
        menu_called=3,
        error_catched=4
    };


    void matrix_drow(int posX, int posY, int width, int height, const char *title, Matrix matrix);
    void matrix_redrow();
    
    void refreash();
};



/*
namespace Mode_Selector{
    static Window_Maker MAKE;
    void init();
}*/
#endif //__GRAPHIC_H__