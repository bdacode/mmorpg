//CLIENT
#include "main.h"
#include "input.h"
#include "logger.h"

#include "gui.hpp"
#include "map.h"
#include "player.h"
#include "init.h"
#include "client.h"
#include "account.hpp"

CKeyboard key;
CMouse mouse;

const
int     WIN_W = 800, WIN_H = 600,
        WIN_FPS = 60;
string  WIN_NAME = "MMORPG Alpha 0.1";

#define PORT 1234
//string serverIP = "25.56.234.57"; // Rhagui
string serverIP = "25.193.13.94"; // SeaMonster131
//string serverIP = "192.168.0.102"; // SeaMonster131 (2)

/***GlobalVariables&Functions***/

void updateFPS(bool);
enum gameMode { gm_menu = 0, gm_gameplay = 1 } GameMode;

int main(int argc, char * argv[]){
    logger.start("log.txt");
    srand(time(0));

    if(!initAllegro())
        return 1;

    /***variables***/

    CMap* map = new CMap();
    CPlayer* player = new CPlayer();

    /*object*/
    cButton test(0, 500, 100, 100, "send");
    cButton quit(110, 570, 180, 30, "send", "quit");
    cButton b_register(100,200, 200,100, "button", "Register");
    cButton b_login(100,350, 200, 100, "button", "Login");

    string name=""; string password="";
    /***over variables***/

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

    GameMode = gm_menu;

    map->resize(10,10);

    logger << "START: Game Loop";
    while(1) {
        al_wait_for_event(event_queue, &ev);
        al_get_keyboard_state(&klawiatura);
        al_get_mouse_state(&myszka);

        key.Get(klawiatura);
        mouse.Get(myszka);

        if(ev.type == ALLEGRO_EVENT_TIMER){
            /***UPDATE***/
            al_clear_to_color(al_map_rgb(200,200,255));
            updateFPS(0);

            /*** MENU ***/
            if(GameMode == gm_menu) {
                b_register.update();
                b_register.draw();

                b_login.update();
                b_login.draw();

                if(b_register.get_click()) {
                    cout << "\n\nPodaj nazwe i haslo do rejestracji:\n";
                    cin >> name >> password;
                    if(!connectToServer(serverIP, PORT))
                            break;

                    if(enet_host_service(client, &event, 5000) > 0) {
                        if(event.type == ENET_EVENT_TYPE_CONNECT) {
                            string mes = "Polaczono do serwera [ "+serverIP+" ]";
                            logger << mes;
                        }
                    }
                    else {
                        logger << "ERROR: Nie mozna polaczyc sie z serwerem.";

                        // TODO : messagebox
                    }
                    if(registration(name, password)) {
                        /*logger << "INIT: map";
                        sendToServer("sendMeMap");
                        if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                            map->createMap(event.packet);
                            map->load();
                            GameMode = gm_gameplay;
                        }*/
                        cout << "\nZAREJESTROWANO. Zaloguj sie, by grac!";
                    }
                }

                if(b_login.get_click()) {
                    cout << "\n\nPodaj nazwe i haslo do zalogowania:\n";
                    cin >> name >> password;
                    if(!connectToServer(serverIP, PORT))
                            break;

                    if(enet_host_service(client, &event, 5000) > 0) {
                        if(event.type == ENET_EVENT_TYPE_CONNECT) {
                            string mes = "Polaczono do serwera [ "+serverIP+" ]";
                            logger << mes;
                        }
                    }
                    else {
                        logger << "ERROR: Nie mozna polaczyc sie z serwerem.";

                        // TODO : messagebox
                    }
                    if(login(name, password, player)) {
                        logger << "INIT: map";
                        sendToServer("sendMeMap");
                        if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                            map->createMap(event.packet);
                            map->load();
                            GameMode = gm_gameplay;
                        }
                    }
                }

                if(key.Press(ALLEGRO_KEY_ESCAPE)) break;
            }

            /*** GAMEPLAY ***/
            else if(GameMode == gm_gameplay){
                /*** CONNECTION ***/
                if(serviceResult > 0) {
                    switch(event.type) {
                        case ENET_EVENT_TYPE_CONNECT:
                        if(event.peer->address.host != address.host) {
                            printf("A new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
                            event.peer->data = (void*)"New User";
                        }
                        break;

                        case ENET_EVENT_TYPE_RECEIVE:
                            //if(receive(event.packet->data, "can_go_up")) player->pos.y--;
                            //if(receive(event.packet->data, "can_go_down")) player->pos.y++;
                            //if(receive(event.packet->data, "can_go_left")) player->pos.x--;
                            //if(receive(event.packet->data, "can_go_right")) player->pos.x++;
                            serviceResult = 0;

                            enet_packet_destroy (event.packet);
                        break;

                        case ENET_EVENT_TYPE_DISCONNECT:
                            printf("%s disconected.\n", event.peer -> data);
                        break;
                    }
                }

                /*** LOGIC ***/
                test.update();
                quit.update();

                player->update(key);

                if(key.Press(ALLEGRO_KEY_ESCAPE)) break;

                if(test.get_click()) sendToServer("klikniecie buttona");
                if(quit.get_click()) {
                    enet_peer_disconnect(peer, 0);
                    enet_host_destroy(client);

                    GameMode = gm_menu;
                }

                /*** DRAW ***/
                map->render();
                player->render();

                test.draw();
                quit.draw();
            }

            al_flip_display();
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        //al_rest(0.001);
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    //enet_peer_disconnect(peer, 0);
    atexit(enet_deinitialize);
    enet_host_destroy(client);

    return 0;
}

int _time(clock());
int cfps(0), FPS(0);
int amount = 0;

void updateFPS(bool write){
    if(_time+1000<clock()){
        _time = clock();
        FPS = cfps;
        cfps = 0;
    }
    cfps++;

    if(write){
        amount++;
        if(amount >= 100){
            cout << "\n#FPS: " << FPS;
            amount = 0;
        }
    }
}
