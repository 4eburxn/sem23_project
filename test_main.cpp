#include <iostream>
#include "src/graphic.h"


int main()
{
    
    Main_Window win;
    FileBrowser brow;
    brow.init();
    win.init();
    Fl::run();

    return 0;
}
