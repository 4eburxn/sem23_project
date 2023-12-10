#include"function_table.h"
/*-----------------------NewFileDialog------------------------*/


void file_chooser_button_CB(Fl_Widget *, void*m){
    NewFileDialog *nfd = (NewFileDialog*)m;
    if(nfd->call_file_chooser() == 0){
        nfd->choosed = nfd->FileChooser.filename();
        std::cout<<"\n\n"<<nfd->choosed<<"\n\n"<<std::endl;
        nfd->ischoosed = true;
        nfd->buffer->text(nfd->FileChooser.filename());
    }
    //else -- cancel pressed
}

void cancel_button_CB(Fl_Widget *, void*m){
    NewFileDialog *nfd = (NewFileDialog*)m;
    nfd->window->hide();
}

void ok_button_CB(Fl_Widget *, void*m){//FIXME!!!!!
    NewFileDialog& nfd = *(NewFileDialog*)m;
    if(atoi(nfd.width_of_matrix->value())>0 && atoi(nfd.height_of_matrix->value()) > 0 && nfd.ischoosed){
        std::vector<std::vector<long double>> a = std::vector<std::vector<long double>>(atoi(nfd.height_of_matrix->value()),std::vector<long double>(atoi(nfd.width_of_matrix->value()),0.));
        Matrix mtrx;
        mtrx.n = atoi(nfd.height_of_matrix->value());
        mtrx.m = atoi(nfd.width_of_matrix->value());
        mtrx.matrix = std::vector<std::vector<long double>>(a);
        mtrx.path_to = nfd.choosed;
        write_matrix_to_file(mtrx);
        nfd.Main->add_matrix(nfd.choosed);
        nfd.window->hide();
    }
}

/*-----------------------Main_Window------------------------*/

void new_file_CB(Fl_Widget *, void*m){
    Main_Window *Win = (Main_Window*)m;
    Win->newfiledialog.show();
}

void arrow_down_pressed(Fl_Widget *, void*m){//FIXME! Макароны
    Main_Window *Win = (Main_Window*)m;
    if(Win->OpenedNow == -1)
    return;
    Win->mtrx_posY = std::max(std::min(Win->mtrx_posY+1,Win->OpenedMatrix[Win->OpenedNow].n-1),0);
    Win->matrix_redrow();
}
void arrow_left_pressed(Fl_Widget *, void*m){
    Main_Window *Win = (Main_Window*)m;
    if(Win->OpenedNow == -1)
    return;
    Win->mtrx_posX = std::max(std::min(Win->mtrx_posX-1,Win->OpenedMatrix[Win->OpenedNow].m-1),0);
    Win->matrix_redrow();
}
void arrow_up_pressed(Fl_Widget *, void*m){
    Main_Window *Win = (Main_Window*)m;
    if(Win->OpenedNow == -1)
    return;
    Win->mtrx_posY = std::max(std::min(Win->mtrx_posY-1,Win->OpenedMatrix[Win->OpenedNow].n-1),0);
    Win->matrix_redrow();
}
void arrow_right_pressed(Fl_Widget *, void*m){
    Main_Window *Win = (Main_Window*)m;
    if(Win->OpenedNow == -1)
        return;
    Win->mtrx_posX = std::max(std::min(Win->mtrx_posX+1,Win->OpenedMatrix[Win->OpenedNow].m-1),0);
    Win->matrix_redrow();
}

void browser_CB(Fl_Widget *a, void*m){
    Main_Window *Win = (Main_Window*)m;
    if(Win->brow->value()==0)
        return;
    std::cout<<Win->brow->value()<<std::endl;
    Win->OpenedNow = Win->brow->value()-1;
    arrow_up_pressed(a, m);
    arrow_left_pressed(a, m);
    Win->matrix_redrow(true);//with clear
}