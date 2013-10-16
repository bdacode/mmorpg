//CLIENT
#include "main.h"
#include "input.h"
#include "logger.h"

#include "gui.hpp"
#include "map.h"

CKeyboard key;
CMouse mouse;

const
int     WIN_W = 800, WIN_H = 600,
        WIN_FPS = 60;
string  WIN_NAME = "MMORPG Alpha 0.1";

#define PORT 1234
//string serverIP = "25.56.234.57"; // Rhagui
//string serverIP = "25.193.13.94"; // SeaMonster131
string serverIP = "192.168.0.102"; // SeaMonster131 (2)

/*
wysylanie np:

char message[1024];

if(strlen(message) > 0) {
          ENetPacket *packet = enet_packet_create (message, strlen
 (message) + 1, ENET_PACKET_FLAG_RELIABLE);
           enet_peer_send (peer, 0, packet);
       }
*/

/*client = enet_host_create(NULL // create a client host //,
                1 // only allow 1 outgoing connection //,
                2 // allow up 2 channels to be used, 0 and 1 //,
                57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth //,
                14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth //);
*/

/*
    ENetPeer* peer = enet_host_connect(client,
                            &address,    // address to connect to //
                             2,           // number of channels //
                             0);          // user data supplied to the receiving host //
*/

void updateFPS(bool);
enum gameMode{gm_gameplay = 0, gm_menu = 1} GameMode;

int main(int argc, char * argv[]){
    logger.start("log.txt");
    srand(time(0));

    logger << "LOAD: allegro5";
    ALLEGRO_DISPLAY *display; ALLEGRO_EVENT_QUEUE *event_queue; ALLEGRO_TIMER *timer;
    ALLEGRO_KEYBOARD_STATE klawiatura; ALLEGRO_MOUSE_STATE myszka; ALLEGRO_EVENT ev;

    logger << "INIT: allegro5";
    al_init(); al_init_image_addon(); al_install_keyboard(); al_install_mouse(); al_init_primitives_addon();
    al_init_font_addon(); al_init_ttf_addon(); al_install_audio(); al_init_acodec_addon();

    logger << "INIT: ENet";
    if(enet_initialize() != 0){
        logger << "ERROR: Init ENet";
        return EXIT_FAILURE;
    }
    /***variables***/
    int serviceResult=1;
    char* message="Hello server! :)";

    ENetHost * client;
    ENetEvent event;
    ENetAddress address;

    /*variables game*/
    cButton test(100, 50, "Wyslij");

    /***over variables***/

    client = enet_host_create(NULL, 1, 2, 57600/8, 14400/8);
    if(client == NULL){
        logger << "ERROR: Create ENet client host.";
        exit(EXIT_FAILURE);
    }

    enet_address_set_host(&address, serverIP.c_str());
    address.port = PORT;

    ENetPeer* peer = enet_host_connect(client, &address, 2, 0);
    if(peer==NULL){
        logger << "ERROR: Nie ma dostepnego polaczenia do serwera.";
        exit(EXIT_FAILURE);
    }

    if(enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT){
        string mes = "Polaczono do serwera [ "+serverIP+" ]";
        logger << mes;
    }else{
        enet_peer_reset(peer);

        logger << "ERROR: Nie mozna polaczyc sie z serwerem.";
        exit (EXIT_FAILURE);
    }

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

    logger << "INIT: map";

    message = "sendMeMap";
    ENetPacket *packet = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);

    serviceResult = enet_host_service(client, &event, 1000);

    string map_w="", map_h="";
    int end = 0;
    int index = 0;
    if(event.type == ENET_EVENT_TYPE_RECEIVE)
    {
        bool byloX = false;
        for(int i = 0; i < event.packet->dataLength-1; ++i)
        {
            if(event.packet->data[i] == ' ')
            {
                end = i;
                break;
            }

            if(event.packet->data[i] != 'x')
            {
                if(!byloX) {
                    map_w.resize(map_w.size()+1);
                    map_w[index] = event.packet->data[i];
                    ++index;
                }
                else {
                    map_h.resize(map_h.size()+1);
                    map_h[index] = event.packet->data[i];
                    ++index;
                }
            }
            else {
                index = 0;
                byloX = true;
            }
        }
    }

    int map_wInt = atoi(map_w.c_str()),
        map_hInt = atoi(map_h.c_str());

    CMap* map = new CMap(map_wInt, map_hInt);

    map->load();

    logger << "START: Game Loop";

    GameMode = gm_gameplay;
    while(1)
    {
        al_wait_for_event(event_queue, &ev);
        al_get_keyboard_state(&klawiatura);
        al_get_mouse_state(&myszka);

        key.Get(klawiatura);
        mouse.Get(myszka);

        if(serviceResult>0){
            switch(event.type){
                case ENET_EVENT_TYPE_CONNECT:
                    if(event.peer->address.host != address.host){
                        printf("A new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
                        event.peer->data = (void*)"New User";
                    }
                    break;

                case ENET_EVENT_TYPE_RECEIVE:
                    printf("\nA packet of length %u containing '%s' was received from %s on channel %u.\n",
                        event.packet -> dataLength,
                        event.packet -> data,
                        event.peer -> data,
                        event.channelID);

                    serviceResult = 0;

                    enet_packet_destroy (event.packet);
                    break;

               case ENET_EVENT_TYPE_DISCONNECT:
                    printf("%s disconected.\n", event.peer -> data);
                    break;
            }
        }

        if(ev.type == ALLEGRO_EVENT_TIMER){
            /***UPDATE***/
            al_clear_to_color(al_map_rgb(200,200,255));
            updateFPS(0);

            if(GameMode==gm_menu){
                cout << "menu\n";
            }

            if(GameMode==gm_gameplay){
                /***UPDATE***/
                map->render();

                test.update();

                /***PLAYER_INSTRUCTION***/
                if(key.Press(ALLEGRO_KEY_ESCAPE))
                    break;

                if(key.Press(ALLEGRO_KEY_UP)){
                    message="UP";
                    ENetPacket *p = enet_packet_create((char*)message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(peer, 0, p);
                    enet_host_flush(client);

                    serviceResult = enet_host_service(client, &event, 100);

                    cout << "\nWYSLANO 'UP'";
                }
                if(test.get_click()){
                    message="CLICK";
                    ENetPacket *p = enet_packet_create((char*)message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(peer, 0, p);
                    enet_host_flush(client);

                    serviceResult = enet_host_service(client, &event, 100);

                    cout << "\nWYSLANO KLIKNIÊCIE BUTTONA TEST!";
                }
            }
            /***DRAW***/
            test.draw();

            al_flip_display();
        }
        else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;

        //al_rest(0.001);
    }

    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    enet_peer_disconnect(peer, 0);
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
