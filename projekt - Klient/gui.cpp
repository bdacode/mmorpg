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
cMessageBox::cMessageBox(int x, int y, int w, int h, string path, string text/*, enum move argument*/)
    : life(1){
    this->x=x; this->y=y;
    this->w=this->x+w; this->h=this->y+h;
    wHelp=w; hHelp=h;
    this->path="media/gui/"+path+".png";
    this->text=text;
    pressed=false;
    modified=false;
    //this->MOVE=argument;
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
    if(mouse.getX()>=x&&mouse.getY()>=y&&mouse.getX()<=w&&mouse.getY()<=h&&mouse.Press(1)&&life)
        pressed=true;

    if(mouse.Press(1)&&pressed/*&&MOVE==GUI_MOVE*/){
        if(mouse.getX()<x||mouse.getY()<y||mouse.getX()>w||mouse.getY()>h)
            modified=true;
    }

    if(modified){
        x=mouse.getX();
        y=mouse.getY();
        w=x+wHelp; h=y+hHelp;
    }

    if(mouse.Press(1)==false&&pressed&&modified) {
        pressed=false; modified=false;
    }
    else if(mouse.Press(1)==false&&pressed) {
        life=false; pressed=false; modified=false;
    }

    /***draw***/
    if(life){
        if(pressed) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,120,0));
        else if(mouse.getX()>=x&&mouse.getY()>=y&&mouse.getX()<=w&&mouse.getY()<=h) al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,90,0));
        else al_draw_filled_rectangle(x,y,w,h,al_map_rgb(20,20,0));
        al_draw_scaled_bitmap(background, 0, 0, getBmpW(background), getBmpH(background), x+4, y+4, w-x-8, h-y-8, 0);
        for(int i=0; i<5; i++){
            al_draw_text(font_button, al_map_rgb( 255, 255, 0 ), x+6, y+6+(i*15), ALLEGRO_ALIGN_LEFT, text.c_str());
        }
    }
}
