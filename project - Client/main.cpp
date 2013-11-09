//CLIENT
#include "main.h"
#include "input.h"
#include "logger.h"
#include "camera.h"

#include "gui.hpp"
#include "map.h"
#include "player.h"
#include "init.h"
#include "client.h"
#include "account.hpp"
#include "audio.hpp"

CKeyboard key;
CMouse mouse;

const
int     WIN_W = 800, WIN_H = 600,
        WIN_FPS = 60;
string  WIN_NAME = "MMORPG Alpha 0.1";
bool fullscreen = false;

#define PORT 1234
string serverIP = "25.56.234.57"; // Rhagui
//string serverIP = "192.168.0.102"; // SeaMonster131 (2)

/***GlobalVariables&Functions***/
ALLEGRO_FONT* font;
int doThread = 60;

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
    CCamera* camera = new CCamera();

    /*object*/
    cButton test(0, 500, 100, 100, "send", GUI_MOVE);
    cButton logout(110, 570, 180, 30, "send", "logout", GUI_STATIC);

    cButton b_register(10,100, 200,50, "send", "Register", GUI_STATIC);
    cButton b_login   (300,300, 200,50, "send", "Login", GUI_STATIC);

    cTextBox menu_login   (250,250, 150,40, "dark", GUI_STATIC);
    cTextBox menu_password(410,250, 150,40, "dark", GUI_STATIC);

    cMessageBox info_menu(400, 300, 200, 50, "dark", "This \n is \n message box!", GUI_MOVE);

    string name=""; string password="";
    bool update_player_pos = false;
    /***over variables***/

    logger << "START: Allegro5";
    al_set_app_name(WIN_NAME.c_str());
    timer = al_create_timer(1.0 / WIN_FPS);

    if(fullscreen)
    {
        al_set_new_display_flags(ALLEGRO_FULLSCREEN);
        al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    }

    display = al_create_display(WIN_W,WIN_H);

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_start_timer(timer);

    loadMusic();
    newMusic(0);
    font = al_load_font("media/font.ttf", 20, 0);

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
            updateFPS(1);

            /*** MENU ***/
            if(GameMode == gm_menu) {
                b_register.render();
                b_login.render();
                menu_login.render();
                menu_password.render();

                // DEBUG - wybor IP serwera

                if(serverIP == "25.56.234.57") al_draw_text(font, al_map_rgb(255,0,0), 10, 10, 0, "25.56.234.57 (Rhagui)");
                else al_draw_text(font, al_map_rgb(255,255,255), 10, 10, 0, "25.56.234.57 (Rhagui)");

                if(serverIP == "25.193.13.94") al_draw_text(font, al_map_rgb(255,0,0), 10, 40, 0, "25.193.13.94 (SeaMonster131)");
                else al_draw_text(font, al_map_rgb(255,255,255), 10, 40, 0, "25.193.13.94 (SeaMonster131)");

                if(mouse.bound(10,10, 200,30) && mouse.Press(1)) serverIP = "25.56.234.57";
                if(mouse.bound(10,40, 200,70) && mouse.Press(1)) serverIP = "25.193.13.94";

                // end DEBUG

                if(b_register.get_click()) {
                    name=menu_login.getText();
                    password=menu_password.getText();

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
                        if(login(name, password, player, camera)) {
                            logger << "INIT: map";
                            sendToServer("sendMeMap");
                            if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                                map->createMap(event.packet);
                                map->load();
                                newMusic(1);
                                GameMode = gm_gameplay;
                            }
                        }
                        cout << "\nZarejestrowano i zalogowano!";
                    }
                }

                if(b_login.get_click()) {
                    name=menu_login.getText();
                    password=menu_password.getText();

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
                        continue;
                    }
                    if(login(name, password, player, camera)) {
                        logger << "INIT: map";
                        sendToServer("sendMeMap");
                        if(event.type == ENET_EVENT_TYPE_RECEIVE) {
                            map->createMap(event.packet);
                            map->load();
                            //string mess = "newPlayer"+player->nick;
                            //ENetPacket *p = enet_packet_create(mess.c_str(), mess.length(), ENET_PACKET_FLAG_RELIABLE);
                            //enet_host_broadcast(client, 0, p);

                            newMusic(1);
                            GameMode = gm_gameplay;
                            logger << "Start gameplay";
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
                            /*if(event.packet->dataLength >= 9) {
                                if(receive(event.packet->data, "newPlayer")) {
                                    cout << "\nDo gry dolaczyl nowy gracz";
                                    string mes = getPacket(event.packet->data);
                                    mes.erase(0,9);
                                    if(mes != player->nick) {
                                        v_otherPlayers.push_back(COtherPlayer(mes));
                                    }
                                }
                            }*/

                            //if(event.channelID == 0)
                            //    cout << "E";

                            //serviceResult = 0;

                            //enet_packet_destroy (event.packet);
                        break;

                        case ENET_EVENT_TYPE_DISCONNECT:
                            printf("%s disconected.\n", event.peer -> data);
                        break;
                    }
                }

                /*** LOGIC ***/
                player->update(key);
                //update_player_pos = true;
                //if(update_player_pos)

                if(doThread <= 10)
                    ++doThread;
                else {
                    _beginthread(player_updatePos, 0, player); // watek na zarzadzanie pozycja graczy
                }

                camera->follow(player);

                if(key.Press(ALLEGRO_KEY_ESCAPE)) break;

                if(test.get_click()){ newMusic(2); info_menu.setText("This \n is \n SPARTA!"); /*sendToServer("klikniecie buttona");*/ }
                if(logout.get_click()) {
                    newMusic(0);
                    enet_peer_disconnect(peer, 0);
                    enet_host_destroy(client);

                    GameMode = gm_menu;
                }

                /*** DRAW ***/
                updateMusic();
                map->render(camera);
                player->render();
                info_menu.render();

                for(int i = 0; i < v_otherPlayers.size(); ++i) {
                    camera->update();
                    al_draw_bitmap_region(IMG_player, (v_otherPlayers[i].dir-1)*50,0, 50,100, v_otherPlayers[i].pos.x+175, v_otherPlayers[i].pos.y, 0);


                    al_draw_filled_rectangle(v_otherPlayers[i].pos.x+25-al_get_text_width(font, v_otherPlayers[i].nick.c_str())/2-10+175, v_otherPlayers[i].pos.y-25,
                                             v_otherPlayers[i].pos.x+25+al_get_text_width(font, v_otherPlayers[i].nick.c_str())/2+10+175, v_otherPlayers[i].pos.y-5,
                                             al_map_rgba(0,0,0, 100));
                    al_draw_text(font, al_map_rgb(255,255,255), v_otherPlayers[i].pos.x+25+175, v_otherPlayers[i].pos.y-30, ALLEGRO_ALIGN_CENTER, v_otherPlayers[i].nick.c_str());
                    camera->reset();

                    //++v_otherPlayers[i].timeFromLastReceive;
                    //if(v_otherPlayers[i].timeFromLastReceive >= 100) // 60 -> ~1 sekunda bez odpowiedzi
                    //    v_otherPlayers.erase(v_otherPlayers.begin()+i);
                }

                test.render();
                logout.render();
            }

            al_flip_display();
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        //if(update_player_pos)
            //_beginthread(player_updatePos, 0, player); // watek na zarzadzanie pozycja graczy

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
