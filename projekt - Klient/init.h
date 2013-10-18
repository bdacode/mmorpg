#ifndef INIT_H_INCLUDED
#define INIT_H_INCLUDED

#include "main.h"

extern ALLEGRO_DISPLAY *display;
extern ALLEGRO_EVENT_QUEUE *event_queue;
extern ALLEGRO_TIMER *timer;
extern ALLEGRO_KEYBOARD_STATE klawiatura;
extern ALLEGRO_MOUSE_STATE myszka;
extern ALLEGRO_EVENT ev;

bool initAllegro();



#endif // INIT_H_INCLUDED
