//SERWER
#include <iostream>
#include <cstdio>
#include <enet/enet.h>

#define PORT 1234
#define MAX_CLIENTS 32

using namespace std;

bool receive(enet_uint8* wiad, char* wiad2) {
    for(int i = 0; i < strlen(wiad2); ++i)
        if(wiad[i] != wiad2[i])
            return false;

    return true;
}

int main(int argc, char ** argv){
    system("title SERWER");

    if(enet_initialize()!=0){
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    /***variables***/
    ENetEvent event;
    int serviceResult = 1;

    ENetAddress address;
    ENetHost * server;

    /***over variables***/

    address.host = ENET_HOST_ANY;
    address.port = PORT;
    server=enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);
    if(server==NULL){
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }
    printf("\nSERVER START\n");

    int ID = 1;
    while(1){
        serviceResult = 1;

        while(serviceResult>0){
            serviceResult = enet_host_service(server, &event, 1000); //1000 milisekund

            /*if(serviceResult <= 0)
            {
                puts("Error with servicing the server");
                exit(EXIT_FAILURE);
            }*/

            switch (event.type){
                case ENET_EVENT_TYPE_CONNECT:{
                    printf ("\nA new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
                    event.peer -> data = (void*)"Client information";
                    //event.peer->data = (void*)ID;

                    //++ID;

                    //message = "Hello my friend :D";
                    //ENetPacket *packet = enet_packet_create (message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                    //enet_peer_send(event.peer, 0, packet);
                }
                break;

                case ENET_EVENT_TYPE_RECEIVE:{
                    printf ("\nDOSTANO: '%s', client [%s], kanal [%u].", //event.packet -> dataLength,
                            event.packet -> data, event.peer -> data, event.channelID);

                    //event.packet->data

                    //if(event.packet->data[0] == 'U' && event.packet->data[1] == 'P') std::cout << "HAAAAAAAAAAAAAA!";

                    if(receive(event.packet->data, "UP")) {
                        char message[] = "Klient nacisnal UP";
                        ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                        //enet_peer_send(peer, 0, p);
                        //enet_host_flush(client);

                        enet_host_broadcast(server, 0, p);
                        //enet_host_flush(server);
                        cout << "\nWYSLANO";
                    }

                    /*ENetAddress add;
                    add.host = event.peer->address.host;
                    add.port = event.peer->address.port;

                    ENetPeer* peer = enet_host_connect(server, &add, 2, 0);

                    char mess[] = "elo";
                    ENetPacket *packet = enet_packet_create(mess, strlen(mess)+1, ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(peer, 0, packet);

                    enet_host_flush (server);*/

                    /// wiadomosc do wszystkich:
                    //enet_host_broadcast(server, 0, event.packet);

                    enet_packet_destroy (event.packet);
                }
                break;

                case ENET_EVENT_TYPE_DISCONNECT:
                    printf ("\n%s disconected.\n", event.peer -> data);
                    event.peer -> data = NULL;
                break;
            }
        }

    }//while(1)

    atexit(enet_deinitialize);
    enet_host_destroy(server);
}
