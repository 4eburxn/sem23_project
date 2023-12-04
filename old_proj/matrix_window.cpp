#include"headers/matrix_window.h"

#include <vector>
#include <iostream>



Slice::Slice(size_t Xstart_, size_t Xend_, size_t Ystart_, size_t Yend_){
    Xstart=Xstart_;
    Xend=Xend_;
    Ystart=Ystart_;
    Yend=Yend_;
}


void print_matrix3x3(WINDOW *menu_win,int x, int y, Slice slice,int Hx, int Hy,std::vector<std::vector<double>> matrix, bool reverce ){	
	init_pair(3, COLOR_BLACK, COLOR_GREEN);
    init_pair(4, COLOR_YELLOW, COLOR_BLUE);
	int highlight = 0;
	int startx,starty;
    for(int i = slice.Xstart;i<slice.Xend;i++){
        for(size_t j = slice.Ystart;j<slice.Yend;j++){
            wattron(menu_win, COLOR_PAIR(4));
            if((((i-slice.Xstart)*3+(j-slice.Ystart))%2 == 1) ^ reverce){wattron(menu_win, A_REVERSE);}
            if(Hx == i && Hy == j){
                wattroff(menu_win, A_REVERSE);
                wattron(menu_win, COLOR_PAIR(3));
            }
            if(matrix[i][j]>=0.0){mvwprintw(menu_win,x+i-slice.Xstart, y+(j-slice.Ystart)*8," ");y++;}
            mvwprintw(menu_win,x+(i-slice.Xstart), y+(j-slice.Ystart)*8,"%.1e", matrix[i][j]);
            if(matrix[i][j]>0.0){y--;}
            if(Hx == i && Hy == j){wattroff(menu_win, COLOR_PAIR(3));}
            wattroff(menu_win, A_REVERSE);
        }
    }
}

enum class Place_In_matrix{
    corner_left_upper,
    corner_right_upper,
    corner_right_down,
    corner_left_down,
    wall_right,
    wall_upper,
    wall_down,
    wall_left,
    centre
};

void slice_to_normal(Slice& S, std::vector<std::vector<double>>& mmx){
    if(S.Xstart == -1){
        S.Xstart = 0;
        S.Xend = 3;
    }
    else if(S.Xend > size(mmx)){
        S.Xstart = size(mmx)-3;
        S.Xend = size(mmx);
    }

    if(S.Ystart == -1){
        S.Ystart = 0;
        S.Yend = 3;
    }
    else if(S.Yend >= size(mmx[0])){
        S.Ystart = size(mmx[0])-3;
        S.Yend = size(mmx[0]);
    }
}




void drow_gray(){return;} /// важно реализовать

void drow_part(WINDOW *menu_win, std::vector<std::vector<double>>& matrix, int Hx, int Hy, int x, int y,Place_In_matrix type){
    auto S = Slice(Hx-1,Hx+2,Hy-1,Hy+2);
    switch (type)
    {
    case Place_In_matrix::corner_left_upper:
        if(Hx<2 || Hy<2){drow_gray();}
        else{print_matrix3x3(menu_win, x, y, Slice(0,1,0,1), Hx, Hy, matrix,false);}
        break;
    case Place_In_matrix::corner_left_down:
        if(size(matrix)-Hx<3 || Hy<2){drow_gray();}
        else{print_matrix3x3(menu_win, x, y, Slice(size(matrix)-1,size(matrix),0,1), Hx, Hy, matrix,false);}
        break;
    case Place_In_matrix::corner_right_down:
        if(size(matrix)-Hx<3 || size(matrix[0])-Hy<3){drow_gray();}
        else{print_matrix3x3(menu_win, x, y, Slice(size(matrix)-1,size(matrix),size(matrix[0])-1,size(matrix[0])), Hx, Hy, matrix,false);}
        break;
    case Place_In_matrix::corner_right_upper:
        if(Hx<2 || size(matrix[0])-Hy<3){drow_gray();}
        else{print_matrix3x3(menu_win, x, y, Slice(0,1,size(matrix[0])-1,size(matrix[0])), Hx, Hy, matrix,false);}
        break;
    case Place_In_matrix::wall_left:
        if(Hy<2 ){drow_gray();}
        else if(size(matrix)-Hx<3){print_matrix3x3(menu_win, x, y, Slice(size(matrix)-3,size(matrix[0]),0,1), Hx, Hy, matrix,true);}
        else if(Hx<2){print_matrix3x3(menu_win, x, y, Slice(0,3,0,1), Hx, Hy, matrix,true);}
        else{print_matrix3x3(menu_win, x, y, Slice(Hx-1,Hx+2,0,1), Hx, Hy, matrix,true);}
        break;
    case Place_In_matrix::wall_down:
        if(size(matrix)-Hx<3){drow_gray();}
        else if(size(matrix[0])-Hy<3){print_matrix3x3(menu_win, x, y, Slice(size(matrix[0])-1,size(matrix[0]),size(matrix)-3,size(matrix)), Hx, Hy, matrix,true);}
        else if(Hy<2){print_matrix3x3(menu_win, x, y, Slice(size(matrix[0])-1,size(matrix[0]),0,3), Hx, Hy, matrix,true);}
        else{print_matrix3x3(menu_win, x, y, Slice(size(matrix[0])-1,size(matrix[0]),Hy-1,Hy+2), Hx, Hy, matrix,true);}
        break;
    case Place_In_matrix::wall_right:
        if(size(matrix[0])-Hy<3){drow_gray();}
        else if(size(matrix)-Hx<3){print_matrix3x3(menu_win, x, y, Slice(size(matrix)-3,size(matrix[0]),size(matrix)-1,size(matrix)), Hx, Hy, matrix,true);}
        else if(Hx<2){print_matrix3x3(menu_win, x, y, Slice(0,3,size(matrix)-1,size(matrix)), Hx, Hy, matrix,true);}
        else{print_matrix3x3(menu_win, x, y, Slice(Hx-1,Hx+2,size(matrix)-1,size(matrix)), Hx, Hy, matrix,true);}
        break;
    case Place_In_matrix::wall_upper: // не доделана
        if(Hx<2){drow_gray();}
        else if(size(matrix[0])-Hy<3){print_matrix3x3(menu_win, x, y, Slice(0,1,size(matrix)-3,size(matrix)), Hx, Hy, matrix,true);}
        else if(Hy<2){print_matrix3x3(menu_win, x, y, Slice(0,1,0,3), Hx, Hy, matrix,true);}
        else{print_matrix3x3(menu_win, x, y, Slice(0,1,Hy-1,Hy+2), Hx, Hy, matrix,true);}
        break;
    case Place_In_matrix::centre:
        slice_to_normal(S,matrix);
        print_matrix3x3(menu_win, x, y, S, Hx, Hy, matrix,false);
        break;
    default:
        break;
    }
}




void drow_matrix(WINDOW *menu_win, std::vector<std::vector<double>> matrix,int Hx, int Hy){
    


	box(menu_win,0,0);
    
    if(size(matrix)<6){
        if(size(matrix[0])<6){
            print_matrix3x3(menu_win,0, 0,Slice(0,size(matrix),0,size(matrix[0])), Hx, Hy, matrix,false);
            return;
        }
        if(Hy<5 && Hy<=size(matrix)/2){
            print_matrix3x3(menu_win,0, 0,Slice(0,size(matrix),0,3), Hx, Hy, matrix,true);
            print_matrix3x3(menu_win,0, 26,Slice(0,size(matrix),size(matrix[0])-1,size(matrix[0])), Hx, Hy, matrix,false);
            return;
        }
        if(size(matrix[0])-Hy<6 && Hy>size(matrix[0])/2+1){
            print_matrix3x3(menu_win,0, 0,Slice(0,size(matrix),0,1), Hx, Hy, matrix,false);
            print_matrix3x3(menu_win,0, 10,Slice(0,size(matrix),size(matrix[0])-3,size(matrix[0])), Hx, Hy, matrix,true);
            return;
        }
        print_matrix3x3(menu_win,0, 0,Slice(0,size(matrix),size(matrix[0])-1,size(matrix[0])), Hx, Hy, matrix,false);
        print_matrix3x3(menu_win,0, 36,Slice(0,size(matrix),0,1), Hx, Hy, matrix,false);
        print_matrix3x3(menu_win,0, 10,Slice(0,size(matrix),Hy-1,Hy+2), Hx, Hy, matrix,true);
        return;
    }
    if(size(matrix[0])<6){
        if(Hx<5 && Hx<size(matrix)/2){
            print_matrix3x3(menu_win,0, 0,Slice(0,3,0,size(matrix[0])), Hx, Hy, matrix,false);
            print_matrix3x3(menu_win,4, 0,Slice(size(matrix)-1,size(matrix),0,size(matrix[0])), Hx, Hy, matrix,true);
            return;
        }
        if(size(matrix)-Hx<6 && Hx>size(matrix)/2){
            print_matrix3x3(menu_win,0, 0,Slice(0,1,0,size(matrix[0])), Hx, Hy, matrix,false);
            print_matrix3x3(menu_win,2, 0,Slice(size(matrix)-3,size(matrix),0,size(matrix[0])), Hx, Hy, matrix,true);
            return;
        }
        print_matrix3x3(menu_win,7, 1,Slice(size(matrix)-1,size(matrix),0,size(matrix[0])), Hx, Hy, matrix,false);
        print_matrix3x3(menu_win,1, 1,Slice(0,1,0,size(matrix[0])), Hx, Hy, matrix,false);
        print_matrix3x3(menu_win,3, 1,Slice(Hx-1,Hx+2,0,size(matrix[0])), Hx, Hy, matrix,true);
        return;
    }
    werase(menu_win);
	box(menu_win,0,0);
    drow_part(menu_win,matrix,Hx,Hy,2,2,Place_In_matrix::corner_left_upper);
    drow_part(menu_win,matrix,Hx,Hy,2,12,Place_In_matrix::wall_upper);
    drow_part(menu_win,matrix,Hx,Hy,2,38,Place_In_matrix::corner_right_upper);
    drow_part(menu_win,matrix,Hx,Hy,4,2,Place_In_matrix::wall_left);
    drow_part(menu_win,matrix,Hx,Hy,4,12,Place_In_matrix::centre);
    drow_part(menu_win,matrix,Hx,Hy,4,38,Place_In_matrix::wall_right);
    drow_part(menu_win,matrix,Hx,Hy,8,2,Place_In_matrix::corner_left_down);
    drow_part(menu_win,matrix,Hx,Hy,8,12,Place_In_matrix::wall_down);
    drow_part(menu_win,matrix,Hx,Hy,8,38,Place_In_matrix::corner_right_down);
}