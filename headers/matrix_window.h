#ifndef __MATRIX_WINDOW_H__
#define __MATRIX_WINDOW_H__

#include <vector>

#include"input.h"

class Slice{
public:
    size_t Xstart;
    size_t Xend;
    size_t Ystart;
    size_t Yend;
    Slice(size_t Xstart, size_t Xend, size_t Ystart, size_t Yend);
};

void print_matrix3x3(WINDOW *menu_win,int x, int y, Slice slice,int Hx, int Hy,std::vector<std::vector<double>> matrix, bool reverce);

void drow_matrix(WINDOW *menu_win, std::vector<std::vector<double>> matrix,int Hx, int Hy);



#endif // __MATRIX_WINDOW_H__