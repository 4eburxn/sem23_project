#include <iostream>
#include "src/graphic.h"
#include "src/function_table.h"
#include "src/determinant.h"
int main()
{
    //WINDOW won;
    //won.MakeWindow(800,600);
    //won.window->show();
    //Fl_Int_Input *as = new Fl_Int_Input(50,0,80,30,"vas");
    //won.window->add(as);
    //Fl::run();
    //std::cout<<as->value();
    //int a;
    //std::cin>>a;
    Main_Window win;
    win.init();
    Fl::run();

    return 0;
}
