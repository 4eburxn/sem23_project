#include"graphic.h"
#include"determinant.h"


void Window_Maker::Window(int width, int height){
    window = new Fl_Window(width, height);
    window->show();

}

Fl_Button *Window_Maker::Button(int posX, int posY, int width, int height, const char *name)
{

    Fl_Button *button = new Fl_Button(posX, posY, width, height, name);
    window->add(button);
    return button;
}




void Main_Window::init(){
    MAKE.Window(800,600);
    MAKE.Button(100,100,70,50,"sadf");
}