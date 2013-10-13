#include "main.h"
#include "input.h"
#include "logger.h"

CKeyboard key;
CMouse mouse;

const
int     WIN_W = 1024, WIN_H = 768,
        WIN_FPS = 60;
string  WIN_NAME = "MMORPG alpha 0.1";

void updateFPS(bool);

ALLEGRO_FONT* font;

enum gameMode { gm_gameplay = 0, gm_menu = 1 } GameMode;

int main(int argc, char * argv[])
{
    logger.start("log.txt");

    logger << "LOAD: allegro5";
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_TIMER *timer;
    ALLEGRO_KEYBOARD_STATE klawiatura;
    ALLEGRO_MOUSE_STATE myszka;
    ALLEGRO_EVENT ev;

    srand(time(0));

    logger << "INIT: allegro5";
    al_init();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_audio();
    al_init_acodec_addon();

    logger << "START: Allegro5";
    al_set_app_name(WIN_NAME.c_str());
    timer = al_create_timer(1.0 / WIN_FPS);

    //al_set_new_display_flags(ALLEGRO_FULLSCREEN);
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    display = al_create_display(WIN_W,WIN_H);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    logger << "START: Game Loop";

    GameMode = gm_gameplay;
    while(1)
    {
        al_wait_for_event(event_queue, &ev);
        al_get_keyboard_state(&klawiatura);
        al_get_mouse_state(&myszka);

        key.Get(klawiatura);
        mouse.Get(myszka);

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(255,255,255));

            updateFPS(0);

            if(GameMode == gm_gameplay)
            {
            }

            al_flip_display();

            if(key.Press(ALLEGRO_KEY_ESCAPE))
                break;
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        //al_rest(0.001);
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}


int _time(clock());
int cfps(0), FPS(0);
int amount = 0;

void updateFPS(bool write)
{
    if(_time+1000<clock())
    {
        _time = clock();
        FPS = cfps;
        cfps = 0;
    }
    cfps++;

    if(write)
    {
        amount++;
        if(amount >= 100)
        {
            cout << "\n#FPS: " << FPS;
            amount = 0;
        }
    }
}
