#include "gui.hpp"

/***button***/
cButton::cButton(int x, int y, int w, int h, string path, GUI_DYNAMICS dynamics)
    : life(1){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    this->path="media/gui/"+path+".png";
    this->dynamics=dynamics;

    wStatic=w; hStatic=h;
    centerX=x+w/2; centerY=y+h-10; //BAD
    click=pressed=false;
    name="";

    background=al_load_bitmap(this->path.c_str());
    font_button=al_load_font("media/font.ttf", 20, 0);
}
cButton::cButton(int x, int y, int w, int h, string path, string name, GUI_DYNAMICS dynamics)
    : life(1){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    this->path="media/gui/"+path+".png";
    this->name=name;
    this->dynamics=dynamics;

    wStatic=w; hStatic=h;
    click=pressed=false;
    //char* path2=path;

    background = al_load_bitmap(this->path.c_str());
    font_button = al_load_font("media/font.ttf", 20, 0);

    centerX=x+w/2; centerY=y/2+this->h/2 - al_get_font_line_height(font_button)/2;
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

        ///al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
        //al_draw_bitmap(background, x+4, y+4, 0);
        al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), centerX, centerY, ALLEGRO_ALIGN_CENTER, name.c_str());
    }
}

/***message box***/
cMessageBox::cMessageBox(int x, int y, int w, int h, string path, string text, GUI_DYNAMICS dynamics)
    : life(1){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    this->path="media/gui/"+path+".png";
    this->text=text;
    this->dynamics=dynamics;

    //int how much=0;
    wStatic=w; hStatic=h;
    pressed=modified=false;
    centerX=x+w/2; centerY=this->h-30;

    position = text.find("\n"); ///TODO
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
    pressed=modified=false;
    this->text=text;
    position=text.find("\n");
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
            if(mouse.Press(1)==false&&pressed) life=pressed=false;

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

        ///al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
        //al_draw_bitmap(background, x, y, 0);

        for(int i=0; i<5; i++){
            al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), x+6, y+6+(i*15), ALLEGRO_ALIGN_LEFT, text.c_str());
        }
    }
}

/***text box***/
cTextBox::cTextBox(int x, int y, int w, int h, string path, GUI_DYNAMICS dynamics)
    : life(1)
    , block(0){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    this->path="media/gui/"+path+".png";
    this->dynamics=dynamics;

    wStatic=w; hStatic=h;
    pressed=modified=big=false;
    text="";
    centerX=x+w/2; centerY=this->h-30;

    background = al_load_bitmap(this->path.c_str());
    font_button = al_load_font("media/font.ttf", 14, 0);
}

void cTextBox::render(){
    if(life){
        if(block!=0) block++;
        if(block>=20) block=0;
        if(wait!=0) wait++;
        ///if(wait>=4) wait=0;
        if(wait>=8) wait=0;

        if(dynamics==GUI_STATIC){
            if(mouse.bound(x,y,w,h)&&mouse.Press(1)&&!pressed&&block==0){ block++; pressed=true; }
            else if(mouse.bound(x,y,w,h)&&mouse.Press(1)&&pressed&&block==0){ block++; pressed=false; }

            if(pressed){
                for(int i=0; i<250; ++i){
                    if(key.Press(ALLEGRO_KEY_LSHIFT)&&!big&&wait==0){big=true; wait++;}
                    else if(key.Press(ALLEGRO_KEY_LSHIFT)&&big&&wait==0){big=false; wait++;}
                    else if(key.Press(ALLEGRO_KEY_BACKSPACE)&&wait==0&&text.length()>0){ text.erase( text.length()-1, 1); wait++;}
                    if(!key.Press(ALLEGRO_KEY_BACKSPACE)&&!key.Press(ALLEGRO_KEY_LSHIFT)&&key.Press(i)&&wait==0){
                        if(big){switchingHelp=i+76; text+=switchingHelp;}
                        else if(!big){switchingHelp=i+96; text+=switchingHelp;}
                        wait++;
                    }
                }
            }
            if(mouse.Press(1)&&!mouse.bound(x,y,w,h)&&pressed) pressed=false;
        } else if(dynamics==GUI_MOVE){
            if(mouse.bound(x,y,w,h)&&mouseOldX!=mouse.getX()&&mouseOldY!=mouse.getY()&&mouse.Press(1)&&modified==false){
                mouseOldX=mouse.getX(); mouseOldY=mouse.getY();
                distanceX=x-mouse.getX(); distanceY=y-mouse.getY();
                modified=true;
            }

            if(modified){
                x=mouse.getX()+distanceX;
                y=mouse.getY()+distanceY;
                w=x+wStatic; h=y+hStatic;
            } else if(mouse.bound(x,y,w,h)&&mouse.Press(1)&&!pressed&&block==0){ block++; pressed=true; }
            else if(mouse.bound(x,y,w,h)&&mouse.Press(1)&&pressed&&block==0){ block++; pressed=false; }

            mouseOldX=mouse.getX();
            mouseOldY=mouse.getY();

            if(!mouse.Press(1)) modified=false;
            if(mouse.Press(1)&&!mouse.bound(x,y,w,h)&&pressed) pressed=false;
        }

        /***DRAW***/
        if(pressed) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,120,0));
        else if(mouse.bound(x,y,w,h)) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,90,0));
        else al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,20,0));

        ///al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
        //al_draw_bitmap(background, x, y, 0);
        al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), x+6, y+6, ALLEGRO_ALIGN_LEFT, text.c_str());
    }
}
