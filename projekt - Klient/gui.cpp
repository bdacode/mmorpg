#include "gui.hpp"

/***button***/
cButton::cButton(int x, int y, int w, int h, string path, GUI_DYNAMICS dynamics)
    : click(0)
    , waiting(0)
    , life(1){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    wStatic=w; hStatic=h;
    this->path="media/gui/"+path+".png";
    this->dynamics=dynamics;

    centerX=x+w/2; centerY=y+h-10; //BAD
    click=pressed=false;
    name="";
    //char* path2=this->path;

    background=al_load_bitmap(this->path.c_str());
    font_button=al_load_font("media/font.ttf", 20, 0);
}
cButton::cButton(int x, int y, int w, int h, string path, string name, GUI_DYNAMICS dynamics)
    : click(0)
    , waiting(0)
    , life(1){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    wStatic=w; hStatic=h;
    this->path="media/gui/"+path+".png";
    this->name=name;
    this->dynamics=dynamics;

    centerX=x+w/2; centerY=this->h-30;
    click=pressed=false;
    //char* path2=path;

    background = al_load_bitmap(this->path.c_str());
    font_button = al_load_font("media/font.ttf", 20, 0);
}

void cButton::render(){
    if(life){
        if(click) click=false;
        if(mouse.bound(x,y,w,h)&&mouse.Press(1)&&click==false) pressed=true;

        if(dynamics==GUI_STATIC){
            if(mouse.bound(x,y,w,h)==false&&mouse.Press(1)&&pressed) pressed=false;
            if(mouse.Press(1)==false&&pressed) {
                click=true; pressed=false;
            }
        } else if(dynamics==GUI_MOVE){
            if(mouseOldX!=mouse.getX()&&mouseOldY!=mouse.getY()&&mouse.Press(1)&&pressed&&modified==false){
                mouseOldX=mouse.getX(); mouseOldY=mouse.getY();
                distanceX=x-mouse.getX(); distanceY=y-mouse.getY();
                modified=true;
            }
            if(modified){
                x=mouse.getX()+distanceX;
                y=mouse.getY()+distanceY;
                w=x+wStatic; h=y+hStatic;
            }

            mouseOldX=mouse.getX();
            mouseOldY=mouse.getY();

            if(mouse.Press(1)==false&&pressed) {
                if(modified==false) click=true;
                pressed=false; modified=false;
            }
        }
        /***draw***/
        if(pressed) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,20,0));
        else if(mouse.bound(x,y,w,h)) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,90,0));
        else al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,120,0));

        al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
        //al_draw_bitmap(background, x+4, y+4, 0);
        al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), centerX, centerY, ALLEGRO_ALIGN_CENTER, name.c_str());
    }
}

/***message box***/
cMessageBox::cMessageBox(int x, int y, int w, int h, string path, string text, GUI_DYNAMICS dynamics)
    : life(1){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    wStatic=w; hStatic=h;
    this->path="media/gui/"+path+".png";
    this->text=text;
    this->dynamics=dynamics;
    pressed=false;
    modified=false;
    //int how much=0;

    centerX=x+w/2; centerY=this->h-30;
    size_t position = text.find("\n");
    while(position != std::string::npos){
        cout << "Fraza zostala odnaleziona na pozycji " << position << endl;
        position = text.find( "\n", position + 2 );
        //how much++;
    }
    //string[how much];

    background = al_load_bitmap(this->path.c_str());
    font_button = al_load_font("media/font.ttf", 14, 0);
}

void cMessageBox::setText(string text){
    life=true;
    pressed=false;
    modified=false;
    this->text=text;
    size_t position = text.find("\n");
    while(position != string::npos){
        cout << "\nFraza zostala odnaleziona na pozycji " << position;
        position = text.find( "\n", position + 2 );
    }
}

void cMessageBox::render(){
    if(life){
        if(mouse.bound(x,y,w,h)&&mouse.Press(1)) pressed=true;


        if(dynamics==GUI_STATIC){
            if(mouse.Press(1)&&!mouse.bound(x,y,w,h)&&pressed) pressed=false;

            if(mouse.Press(1)==false&&pressed) {
                life=false; pressed=false;
            }
        } else if(dynamics==GUI_MOVE){
            if(mouseOldX!=mouse.getX()&&mouseOldY!=mouse.getY()&&mouse.Press(1)&&pressed&&modified==false){
                mouseOldX=mouse.getX(); mouseOldY=mouse.getY();
                distanceX=x-mouse.getX(); distanceY=y-mouse.getY();
                modified=true;
            }
            if(modified){
                x=mouse.getX()+distanceX;
                y=mouse.getY()+distanceY;
                w=x+wStatic; h=y+hStatic;
            }
            mouseOldX=mouse.getX();
            mouseOldY=mouse.getY();

            if(mouse.Press(1)==false&&pressed) {
                if(modified==false) life=false;
                pressed=false; modified=false;
            }
        }

        /***DRAW***/
        if(pressed) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,120,0));
        else if(mouse.bound(x,y,w,h)) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,90,0));
        else al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,20,0));

        al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
        //al_draw_bitmap(background, x, y, 0);

        for(int i=0; i<5; i++){
            al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), x+6, y+6+(i*15), ALLEGRO_ALIGN_LEFT, text.c_str());
        }
    }
}
