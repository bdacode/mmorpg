#include "init.h"

ALLEGRO_DISPLAY *display; ALLEGRO_EVENT_QUEUE *event_queue; ALLEGRO_TIMER *timer;
ALLEGRO_KEYBOARD_STATE klawiatura; ALLEGRO_MOUSE_STATE myszka; ALLEGRO_EVENT ev;

bool initAllegro() {
    logger << "LOAD: allegro5";

    logger << "INIT: allegro5";
    al_init(); al_init_image_addon(); al_install_keyboard(); al_install_mouse(); al_init_primitives_addon();
    al_init_font_addon(); al_init_ttf_addon(); al_install_audio(); al_init_acodec_addon();

    logger << "INIT: ENet";
    if(enet_initialize() != 0){
        logger << "ERROR: Init ENet";
        return false;
    }

    return true;
}
