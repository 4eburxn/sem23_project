#include"graphic.h"
#include"determinant.h"


void WINDOW::MakeWindow(int width, int height){
    window = new Fl_Window(width, height);
}

Fl_Button *WINDOW::MakeButton(int posX, int posY, int width, int height, const char *name)
{
    Fl_Button *button = new Fl_Button(posX, posY, width, height, name);
    window->add(button);
    return button;
}

Fl_Menu_Bar *WINDOW::MakeBar(int posX, int posY, int width, int height, Fl_Menu_Item menuitems[])
{
    Fl_Menu_Bar *m = new Fl_Menu_Bar(posX, posY, width, height);
    m->copy(menuitems);
    window->add(m);
    return m;
}

/*
void NewFile(Fl_Widget *w,void *a){
    Main_Window win = (Main_Window *)a;
    win->broZZ
}*/


void Main_Window::init(){

    brow.init();
    MakeWindow(800,600);
    Fl_Menu_Item menuitems[] = {
  { "&File",              0, 0, 0, FL_SUBMENU },
    //{ "&New File",        0, (Fl_Callback *)(NewFile), (void*)(this) },
    { "&Open File",        0, 0, 0 },
    { "&Safe File",        0, 0, 0 },
    { 0 },
  { "&Edit",              0, 0, 0, FL_SUBMENU },
    { "&Undo",        0, 0, 0 },
    { "&Redo",        0, 0, 0 },
    { 0 },
  { 0 }
};
    MakeBar(0, 0, 800, 35, menuitems);
    //Buttons::mode_change = MAKE.Button(100,100,120,40,"Mode change");
    //Buttons::mode_change->callback(Main_Window::event_handler, (long)(Main_Window::Event::menu_called));
    window->show();
}

/*
void Mode_Selector::init(){
    MAKE.Window(200,300);
    Fl_Text_Editor *edit = new Fl_Text_Editor(0, 0, 100, 100, "adf");
    edit->insert_mode(1);
    MAKE.window->add(edit);
    MAKE.Button(100,100,50,30,"???");
}*/



void callback_handler(Fl_File_Chooser *, void *browser)
{
    std::cout << ((Fl_File_Chooser*)browser)->value(1);
}

void FileBrowser::init()
{
    MakeWindow(400,400);
    Fl_File_Chooser* browser= new Fl_File_Chooser("","*.*", 0, "file_chooser");

    
    browser->callback(callback_handler, (void *)(browser));
}
FileBrowser::FileBrowser()
    {
        init();
    }