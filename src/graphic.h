#ifndef __GRAPHIC_H__
#define __GRAPHIC_H__ 1


#include <iostream>
#include <format>
#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Widget.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/Fl_Value_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_File_Input.H>
#include <stdlib.h>

#include "determinant.h"
#include "function_table.h"
#include "file_work.h"

//FIXME! деструкторы

class WINDOW
{
public:
    Fl_Window *window;
    void MakeWindow(int width, int height);
    Fl_Button *MakeButton(int posX, int posY, int width, int height, const char *name = "");
    Fl_Menu_Bar *MakeBar(int posX, int posY, int width, int height, Fl_Menu_Item menuitems[]);
    ~WINDOW(){
        window->clear();
        delete window;
    }
};


class Main_Window;
class NewFileDialog : public WINDOW{
public:
    Main_Window *Main; // fixme
    Fl_Native_File_Chooser FileChooser;
    std::string choosed = "nothing selected";
    bool ischoosed = false;
    std::vector<Fl_Button *> buttons = std::vector<Fl_Button *>((size_t)10, nullptr);  //более 10 кнопок нам не потребуется
    enum Button_names{
        cancel=0,
        open_file_exp=1,
        ok_button=2
    };
    Fl_Int_Input *width_of_matrix;
    Fl_Int_Input *height_of_matrix;
    Fl_Text_Display *Path_display;
    Fl_Text_Buffer * buffer;

    NewFileDialog();
    void show();
    int call_file_chooser();
};


class ActionMenu : public WINDOW{
public:
    Main_Window *Main; // fixme
    Fl_Native_File_Chooser FileChooser;
    std::vector<Fl_Button *> buttons = std::vector<Fl_Button *>((size_t)10, nullptr);  //более 10 кнопок нам не потребуется
    enum Button_names{
        cancel=0,
        ok_button=1
    };
    Fl_File_Input *Path1_display;
    Fl_File_Input *Path2_display;

    ActionMenu();
    void show(){window->show();}
    int call_file_chooser();
};


class MatrixDrower{
private:
    const int dispheight=30,dispwidth=70;
    size_t HORISONTAL = 0,
           VERTICAL = 1;
    class Text_Display_Pbuff{
    public:
        Fl_Text_Display* display;
        Fl_Text_Buffer * buffer;
        Text_Display_Pbuff() = default;
        Text_Display_Pbuff(int Startx, int Starty, int height, int width,Fl_Window *win){
            display = new Fl_Text_Display(Startx, Starty, height, width);
            buffer = new Fl_Text_Buffer();
            display->buffer(buffer);
            win->add(display);
        }
        void highlight(bool reverce = false){
            if(!reverce){display->color(Fl_Color(2));}
            else{display->color(Fl_Color(7));}

        }
    };
    Text_Display_Pbuff displays[3][3];
    Text_Display_Pbuff numbers[2][3];
public:
    MatrixDrower(int Startx,int Starty, Fl_Window *win){
        Fl_Text_Buffer *buff;
        for(size_t i = 0;i<3;i++)
        {
            for(size_t j = 0;j<3;j++){
                displays[j][i]=Text_Display_Pbuff(Startx+dispwidth*(i+1),Starty+dispheight*(j+1),dispwidth,dispheight,win);
            }
            numbers[HORISONTAL][i]=Text_Display_Pbuff(Startx+dispwidth*(i+1),Starty,dispwidth,dispheight,win);
            numbers[VERTICAL][i]=Text_Display_Pbuff(Startx,Starty+dispheight*(i+1),dispwidth,dispheight,win);
        }
    }
    void draw(Matrix mtrx,size_t Hx, size_t Hy, bool clear = false);
};


class Main_Window : public WINDOW{
public:
    void init();

    std::vector<Matrix> OpenedMatrix;
    size_t OpenedNow=-1;

    std::vector<Fl_Button *> buttons = std::vector<Fl_Button *>((size_t)10, nullptr);  //более 10 кнопок нам не потребуется
    enum Button_names{
        mode_change=0,
        open_file_exp=1,
        arrow_down=2,
        arrow_left=3,
        arrow_up=4,
        arrow_right=5,
        confirm_float_input=6,
        open_act_menu = 7,
        matrix_transpose = 8
    };
    int mtrx_posX = 0,
        mtrx_posY = 0;
    Fl_Hold_Browser *brow;
    Fl_Float_Input *input;
    Fl_Text_Buffer * buffer;
    Fl_Text_Display *det_output;
    Fl_Check_Button *determinant_recalc;

    MatrixDrower *mtrxdrow;
    NewFileDialog newfiledialog;
    ActionMenu actmenu;
    //WINDOW popupwin; //TODO
    
    void matrix_redrow(bool clear = false);
    void add_matrix(std::string filepath);

    ~Main_Window(){
        for(auto i:buttons){
            delete i;
            i = nullptr;
        }
        delete brow,input,mtrxdrow;
    }
};





#endif //__GRAPHIC_H__