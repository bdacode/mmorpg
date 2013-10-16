#include "gui.hpp"

cButton::cButton(int x, int y, string name)
    : click(0){
    this->x=x;
    this->y=y;
    w=this->x+140;
    h=this->y+30;
    this->name=name;
    click=pressed=false;
    waiting=0;
    font_button = al_load_font("media/font.ttf", 20, 0);
}

void cButton::update(){
    if(click) click=false;
    if(orWait) waiting++;
    if(waiting>=20){waiting=0; orWait=false;}
    if(mouse.getX()>=x&&mouse.getY()>=y&&mouse.getX()<=w&&mouse.getY()<=h&&mouse.Press(1)&&waiting==0&&click==false) {
        pressed=true;
    }
    /*if(mouse.getX()<x&&mouse.getY()<y&&mouse.getX()>w&&mouse.getY()>h&&pressed)
        pressed=false;*/
    if(mouse.Press(1)==false&&pressed) {
        click=true; orWait=true; pressed=false;
    }
}
void cButton::draw(){
    if(pressed) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,20,0));
    else if(mouse.getX()>=x&&mouse.getY()>=y&&mouse.getX()<=w&&mouse.getY()<=h) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,90,0));
    else al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,120,0));
    al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), w-70, h-30, ALLEGRO_ALIGN_CENTER, name.c_str());
}
