#include"graphic.h"
#include"determinant.h"


NewFileDialog::NewFileDialog()
{
    FileChooser.title("Create a file");
    FileChooser.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
    FileChooser.filter("*.mtrx");
    FileChooser.directory("");
    MakeWindow(400,300);
    //MakeButton();
    buttons[Button_names::open_file_exp]= MakeButton(360,0,40,40,"@filesave");
    buttons[Button_names::open_file_exp]->callback(file_chooser_button_CB, (void*)this);
    buttons[Button_names::ok_button] = MakeButton(340,270,60,30,"Ok"); //FIXME! add calback
    buttons[Button_names::ok_button]->callback(ok_button_CB, (void*)this);
    buttons[Button_names::cancel] = MakeButton(280,270,60,30,"Cancel");
    buttons[Button_names::cancel]->callback(cancel_button_CB, (void*)this);
    width_of_matrix = new Fl_Int_Input(120,50,70,30,"matrix height:");
    window->add(width_of_matrix);
    height_of_matrix = new Fl_Int_Input(120,80,70,30,"matrix width :");
    window->add(height_of_matrix);
    Path_display = new Fl_Text_Display(0, 0, 360, 40);
    buffer = new Fl_Text_Buffer();
    buffer->text(choosed.c_str());
    Path_display->buffer(buffer);
    window->add(Path_display);
}

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


void MatrixDrower::draw(Matrix mtrx,size_t Hx, size_t Hy, bool clear/* = false*/){
    if(clear){
        for(int i = 0;i<3;i++)
        for(int j = 0;j<3;j++){
            displays[i][j].buffer->text("");
            numbers[i%2][j].buffer->text("");
        }
    }
    int startX = Hx-1,stopX=Hx+2,
        startY = Hy-1,stopY=Hy+2,
        tmp1= 0,
        tmp2= 0;
    if(mtrx.matrix.size()<4){
        startY = 0;
        stopY = mtrx.matrix.size();
    }
    else if(Hy==0 || Hy==mtrx.matrix.size()-1){
        startY= Hy==0? 0:(mtrx.matrix.size()-3);
        stopY= Hy==0? 3:(mtrx.matrix.size());
    }
    if(mtrx.matrix[0].size()<4){
        startX = 0;
        stopX = mtrx.matrix[0].size();
    }
    else if(Hx==0 || Hx==mtrx.matrix[0].size()-1){
        startX= Hx==0? 0:(mtrx.matrix[0].size()-3);
        stopX= Hx==0? 3:(mtrx.matrix[0].size());
    }
    
    for(int i = startY;i<stopY;i++){
        numbers[VERTICAL][i-startY].buffer->text(std::format("{}",i+1).c_str()); // c++20 module
        for(int j = startX;j<stopX;j++){
            numbers[HORISONTAL][j-startX].buffer->text(std::format("{}",j+1).substr(0,8).c_str()); //FIXME
            displays[i-startY][j-startX].buffer->text(std::format("{}",mtrx.matrix[i][j]).substr(0,8).c_str());
            if(i==Hy&&j==Hx){displays[i-startY][j-startX].highlight();}
            else{displays[i-startY][j-startX].highlight(true);}
        }
    }
}

void Main_Window::init(){

    MakeWindow(800,600);
    brow = new Fl_Hold_Browser(0,25,200,600-25);
    brow->callback(browser_CB, (void*)this);
    window->add(brow);
    Fl_Menu_Item menuitems[] = {
  { "&File",              0, 0, 0, FL_SUBMENU },
    { "&New File",        0, (Fl_Callback *)(new_file_CB), (void*)(this) },
    { "&Open File",        0, 0, 0 },
    { "&Safe File",        0, 0, 0 },
    { 0 },
  { "&Edit",              0, 0, 0, FL_SUBMENU },
    { "&Undo",        0, 0, 0 },
    { "&Redo",        0, 0, 0 },
    { 0 },
  { 0 }
};
    MakeBar(0, 0, 800, 25, menuitems);
    buttons[Button_names::arrow_down] = MakeButton(675,200,50,50,"@2->");
    buttons[Button_names::arrow_down]->callback(arrow_down_pressed, (void*)this);
    buttons[Button_names::arrow_left] = MakeButton(625,150,50,50,"@4->");
    buttons[Button_names::arrow_left]->callback(arrow_left_pressed, (void*)this);
    buttons[Button_names::arrow_up] = MakeButton(675,100,50,50,"@8->");
    buttons[Button_names::arrow_up]->callback(arrow_up_pressed, (void*)this);
    buttons[Button_names::arrow_right] = MakeButton(725,150,50,50,"@->");
    buttons[Button_names::arrow_right]->callback(arrow_right_pressed, (void*)this);
    window->show();
    newfiledialog.Main = this;
    mtrxdrow = new MatrixDrower(300,125,window);
}

void Main_Window::matrix_redrow(bool clear)
{
    std::cout<<mtrx_posX<<"\t"<<mtrx_posY<<std::endl;
    mtrxdrow->draw(OpenedMatrix[OpenedNow],mtrx_posX,mtrx_posY,clear);
}

void Main_Window::add_matrix(std::string filepath)
{
    Matrix mtrx = read_matrix_from_file(filepath);
    mtrx.path_to=filepath;
    OpenedMatrix.push_back(mtrx);
    brow->add(filepath.c_str());
    OpenedNow = OpenedMatrix.size()-1;
    matrix_redrow(true); // clear
    mtrx_posX = 0;
    mtrx_posY = 0;
}

void NewFileDialog::show()
{
    ischoosed = false;
    choosed = "nothing selected";
    buffer->text("nothing selected");
    window->show();
}

int NewFileDialog::call_file_chooser()
{
    return FileChooser.show();
}
