#include "main.h"
#include "input.h"
#include "logger.h"

CKeyboard key;
CMouse mouse;

const
int     WIN_W = 800, WIN_H = 600,
        WIN_FPS = 60;
string  WIN_NAME = "MMORPG alpha 0.1";

#define PORT 1234
string serverIP = "localhost";

/*
wysylanie np:

char message[1024];

if(strlen(message) > 0) {
          ENetPacket *packet = enet_packet_create (message, strlen
 (message) + 1, ENET_PACKET_FLAG_RELIABLE);
           enet_peer_send (peer, 0, packet);
       }
*/


void updateFPS(bool);

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

    logger << "INIT: ENet";
    if(enet_initialize() != 0)
    {
        logger << "ERROR: Init ENet";
        return EXIT_FAILURE;
    }
    ENetHost * client;
    ENetEvent event;
    ENetAddress address;

    client = enet_host_create(NULL /* create a client host */,
                1 /* only allow 1 outgoing connection */,
                2 /* allow up 2 channels to be used, 0 and 1 */,
                57600 / 8 /* 56K modem with 56 Kbps downstream bandwidth */,
                14400 / 8 /* 56K modem with 14 Kbps upstream bandwidth */);
    if(client == NULL)
    {
        logger << "ERROR: Create ENet client host.";
        exit(EXIT_FAILURE);
    }
    enet_address_set_host(&address, serverIP.c_str());
    address.port = PORT;

    ENetPeer* peer = enet_host_connect(client,
                            &address,    /* address to connect to */
                             2,           /* number of channels */
                             0);          /* user data supplied to the receiving host */

    if(peer == NULL)
    {
        logger << "ERROR: Nie ma dostepnego polaczenia do serwera.";
        exit(EXIT_FAILURE);
    }

    /* Try to connect to server within 5 seconds */
    if(enet_host_service(client, &event, 5000) > 0 && event.type == ENET_EVENT_TYPE_CONNECT)
    {
        string mes = "Polaczono do serwera [ "+serverIP+" ]";
        logger << mes;
    }
    else
    {
        /* Either the 5 seconds are up or a disconnect event was */
        /* received. Reset the peer in the event the 5 seconds   */
        /* had run out without any significant event.            */
        enet_peer_reset(peer);

        logger << "ERROR: Nie mozna polaczyc sie z serwerem.";
        exit (EXIT_FAILURE);
    }

    int serviceResult = 1;


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

    char* message = "Witaj serwerze ! :)";
    ENetPacket *packet = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, packet);

    serviceResult = enet_host_service(client, &event, 1000);

    GameMode = gm_gameplay;
    while(1)
    {
        al_wait_for_event(event_queue, &ev);
        al_get_keyboard_state(&klawiatura);
        al_get_mouse_state(&myszka);

        key.Get(klawiatura);
        mouse.Get(myszka);


        if(serviceResult > 0)
        {
            switch(event.type)
            {
                case ENET_EVENT_TYPE_CONNECT:
                    if(event.peer->address.host != address.host)
                    {
                        printf("A new client connected from %x:%u.\n",
                            event.peer -> address.host,
                            event.peer -> address.port);

                        event.peer->data = (void*)"New User";
                    }
                break;

                case ENET_EVENT_TYPE_RECEIVE:
                    printf("A packet of length %u containing '%s' was received from %s on channel %u.\n",
                        event.packet -> dataLength,
                        event.packet -> data,
                        event.peer -> data,
                        event.channelID);

                    enet_packet_destroy (event.packet);

                break;

               case ENET_EVENT_TYPE_DISCONNECT:
                    printf("%s disconected.\n", event.peer -> data);

                break;
            }
        }

        if(ev.type == ALLEGRO_EVENT_TIMER)
        {
            al_clear_to_color(al_map_rgb(200,200,255));

            updateFPS(0);

            if(key.Press(ALLEGRO_KEY_UP))
            {
                char m[] = "KLAWISZ_UP";
                ENetPacket *p = enet_packet_create(m, strlen(m)+1, ENET_PACKET_FLAG_RELIABLE);
                enet_peer_send(peer, 0, p);
                //serviceResult = enet_host_service(client, &event, 1000);
                enet_host_flush(client);

                cout << "\nWYSLANO 'KLAWISZ_UP'";
            }

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

    enet_peer_disconnect(peer, 0);
    atexit(enet_deinitialize);
    enet_host_destroy(client);

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
