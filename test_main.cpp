#include <iostream>
#include "src/graphic.h"
#include "src/function_table.h"
#include "src/determinant.h"
int main()
{
    Main_Window win;
    win.init();
    Fl::run();

    return 0;
}
