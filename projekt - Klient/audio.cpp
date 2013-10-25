#include "audio.hpp"

ALLEGRO_SAMPLE* music[4];
int id=0;

void loadMusic(){
    /*music[0]=al_load_sample("media/music/menu_theme.ogg");
    music[1]=al_load_sample("media/music/plains.ogg");
    music[2]=al_load_sample("media/music/taverns.ogg");
    music[3]=al_load_sample("media/music/underdark.ogg");
    for(int i=0; i<4; ++i){
        if(!music[i]){
            cout << "Nie udalo sie wczytac muzyki!\n";
        }
    }
    al_reserve_samples(1);*/
}
void newMusic(int ID){
    id=ID;
    al_stop_samples();
    //al_play_sample(music[id], 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP,NULL);
}

void stopMusic(){ al_stop_samples(); }
void updateMusic(){ al_play_sample(music[id], 1.0, 0.0, 1.0,ALLEGRO_PLAYMODE_LOOP,NULL); }
