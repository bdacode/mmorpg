#include "gui.hpp"

/***button***/
cButton::cButton(int x, int y, int w, int h, string path)
    : click(0)
    , waiting(0){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    this->path="media/gui/"+path+".png";

    centerX=x+w/2; centerY=y+h-10; //BAD
    click=pressed=false;
    name="";
    //char* path2=this->path;

    background=al_load_bitmap(this->path.c_str());
    font_button=al_load_font("media/font.ttf", 20, 0);
}
cButton::cButton(int x, int y, int w, int h, string path, string name)
    : click(0)
    , waiting(0){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    this->path="media/gui/"+path+".png";
    this->name=name;

    centerX=x+w/2; centerY=this->h-30;
    click=pressed=false;
    //char* path2=path;

    background = al_load_bitmap(this->path.c_str());
    font_button = al_load_font("media/font.ttf", 20, 0);
}

void cButton::render(){
    if(click) click=false;
    if(mouse.getX()>=x&&mouse.getY()>=y&&mouse.getX()<=w&&mouse.getY()<=h&&mouse.Press(1)&&click==false)
        pressed=true;
    if(mouse.getX()<x||mouse.getY()<y||mouse.getX()>w||mouse.getY()>h&&mouse.Press(1)&&pressed)
        pressed=false;
    if(mouse.Press(1)==false&&pressed) {
        click=true; pressed=false;
    }
    /***draw***/
    if(pressed) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,20,0));
    else if(mouse.getX()>=x&&mouse.getY()>=y&&mouse.getX()<=w&&mouse.getY()<=h) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,90,0));
    else al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,120,0));
    al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
    al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), centerX, centerY, ALLEGRO_ALIGN_CENTER, name.c_str());
}

/***message box***/
cMessageBox::cMessageBox(int x, int y, int w, int h, string path, string text)
    : life(0){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    this->path="media/gui/"+path+".png";
    this->text=text;

    centerX=x+w/2; centerY=this->h-30;

    background = al_load_bitmap(this->path.c_str());
    font_button = al_load_font("media/font.ttf", 20, 0);
}

void cMessageBox::setText(string text){
    life=0;
    this->text=text;
}

void cMessageBox::render(){
    if(life<60){ //20 ~=1 sec
        life++;
        al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,20,0));
        al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
        al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), centerX, centerY, ALLEGRO_ALIGN_CENTER, text.c_str());
    }
}
