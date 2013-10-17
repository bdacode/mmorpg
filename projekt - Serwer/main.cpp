//SERWER
#include <iostream>
#include <cstdio>
#include <enet/enet.h>
#include <fstream>

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
    int ID=1;

    ENetAddress address;
    ENetHost * server;

    string mapa;

    fstream file("map.txt", ios::in);
    if(!file.good())
        cout << "\nI can't find map!";
    else {
        /*string size_map="", size_w, size_h;
        file >> size_map;
        size_t pos = size_map.find('x');
        if(pos != string::npos) {
            size_w = size_map.substr(0, pos);
            size_h = size_map.substr(pos);
        }
        pos = size_map.find(' ');
        mapa = size_map.substr(pos);*/

        getline(file, mapa);
    }

    /***over variables***/

    address.host = ENET_HOST_ANY;
    address.port = PORT;
    server=enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);
    if(server==NULL){
        fprintf(stderr, "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }
    printf("\nSERVER START\n");

    while(1){
        serviceResult=1;

        while(serviceResult>0){
            serviceResult = enet_host_service(server, &event, 1000); //1000 milisekund
            switch (event.type){
                case ENET_EVENT_TYPE_CONNECT:{
                    printf ("\nA new client connected from %x:%u.\n", event.peer -> address.host, event.peer -> address.port);
                    event.peer -> data = (void*)"Client information";
                    //event.peer->data = (void*)ID;

                    //++ID;
                }
                break;

                case ENET_EVENT_TYPE_RECEIVE:{
                    printf ("\nDOSTANO: '%s', client [%s], kanal [%u].", //event.packet -> dataLength,
                            event.packet -> data, event.peer -> data, event.channelID);

                    if(receive(event.packet->data, "UP")) {
                        char message[] = "Klient nacisnal klawisz 'UP'!\n";
                        ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);

                        enet_host_broadcast(server, 0, p);
                        cout << "\nWYSLANO";
                    }
                    if(receive(event.packet->data, "CLICK")) {
                        char message[] = "Klient nacisnal przycisk!\n";
                        ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);

                        enet_host_broadcast(server, 0, p);
                        cout << "\nWYSLANO";
                    }

                    if(receive(event.packet->data, "sendMeMap")) {
                        //char message[mapa.size()] = mapa.c_str();
                        ENetPacket *p = enet_packet_create(mapa.c_str(), mapa.size()+1, ENET_PACKET_FLAG_RELIABLE);

                        enet_host_broadcast(server, 0, p);
                        cout << "\nWYSLANO MAPE";
                    }

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
