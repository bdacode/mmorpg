//SERWER
#include <iostream>
#include <cstdio>
#include <enet/enet.h>
#include <fstream>

#define PORT 1234
#define MAX_CLIENTS 32

using namespace std;
ENetEvent event;

bool receive(enet_uint8* wiad, char* wiad2) {
    for(int i = 0; i < strlen(wiad2); ++i)
        if(wiad[i] != wiad2[i])
            return false;
    return true;
}
string getPacket(enet_uint8* wiad){
    string text="";
    for(int i=0; i < event.packet->dataLength; ++i) {
        text.resize( text.size()+1);
        text[i] = event.packet->data[i];
    }
    return text;
}

int main(int argc, char ** argv){
    system("title SERWER");

    if(enet_initialize()!=0){
        fprintf (stderr, "An error occurred while initializing ENet.\n");
        return EXIT_FAILURE;
    }

    /***variables***/
    int serviceResult = 1;
    int ID=1;

    string name, password;
    string packet_name, packet_password;
    bool busy_account=false;
    char* gh;
    fstream file;

    ENetAddress address;
    ENetHost * server;

    string mapa;

    file.open("map.txt", ios::in);
    if(!file.good())
        cout << "\nI can't find map!";
    else {
        getline(file, mapa);
    }
    file.close();

    /***over variables***/

    address.host = ENET_HOST_ANY;
    address.port = PORT;
    server=enet_host_create(&address, MAX_CLIENTS, 2, 0, 0);
    if(server==NULL){
        fprintf(stderr, "\nAn error occurred while trying to create an ENet server host.\n");
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
                    //printf ("\nDOSTANO: '%s', client [%s], kanal [%u].", //event.packet -> dataLength,
                    //        event.packet -> data, event.peer -> data, event.channelID);

                    //cout << "\n$$$ OTRZYMANO OD [" << event.peer->address.host << "] dane: '" << event.packet->data << "'";

                    if(receive(event.packet->data, "register")) {
                        packet_name=getPacket(event.packet->data);
                        packet_password=getPacket(event.packet->data);
                        packet_name.erase( 0, 8 );
                        packet_password.erase( 0, 8 );
                        size_t znalezionaPozycja = packet_name.find( ":" );
                        packet_name.erase( znalezionaPozycja, 20 );
                        packet_password.erase( 0, znalezionaPozycja+1 );
                        busy_account = true;

                        file.open("nick.txt", ios::in);
                        if(file.good())
                        {
                            while(!file.eof())
                            {
                                file >> name >> password;
                                if(packet_name != name)
                                    busy_account = false;
                                else
                                    busy_account = true;

                                if(busy_account){ cout << "\nERROR!\n" << endl; break; }
                            }
                            file.close();
                        }
                        else {
                            cout << "\nERROR: I can't open nick.txt";
                            busy_account=true;
                        }

                        if(!busy_account)
                        {
                            file.open("nick.txt", ios::out | ios::app);
                            file << packet_name << " " << packet_password << "\n";
                            file.close();

                            string path = "users/"+packet_name+".txt";
                            file.open(path.c_str(), ios::out);
                            file << "1 1 1 1 1 0 0"; // hair, head, body, leg, boots, posX, posY
                            file.close();

                            char message[] = "GOOD";
                            ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                            enet_host_broadcast(server, 0, p);
                            cout << "\nZarejestrowano nowego uzytkownika!";
                        }
                        else
                        {
                            char message[] = "FAIL";
                            ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                            enet_host_broadcast(server, 0, p);
                        }
                        file.close();
                    }
                    else if(receive(event.packet->data, "login")) {
                        bool isLogin = false;

                        packet_name=getPacket(event.packet->data);
                        packet_password=getPacket(event.packet->data);
                        packet_name.erase( 0, 5 );
                        packet_password.erase( 0, 5 );
                        size_t znalezionaPozycja = packet_name.find( ":" );
                        packet_name.erase( znalezionaPozycja, 20 );
                        packet_password.erase( 0, znalezionaPozycja+1 );

                        file.open("nick.txt", ios::in);
                        if(file.good())
                        {
                            while(!file.eof())
                            {
                                file >> name >> password;
                                if(packet_name == name && packet_password == password) {
                                    isLogin = true;
                                    break;
                                }
                            }
                            file.close();
                        }
                        else {
                            cout << "\nERROR: I can't open nick.txt";
                            isLogin = false;
                        }

                        if(isLogin)
                        {
                            string path = "users/"+packet_name+".txt";
                            file.open(path.c_str(), ios::in);
                            string hair, head, body, leg, boots, posX, posY;
                            file >> hair >> head >> body >> leg >> boots >> posX >> posY;
                            file.close();

                            string wiad = "GOOD "+hair+" "+head+" "+body+" "+leg+" "+boots+" "+posX+" "+posY;

                            //char message[] = "GOOD";
                            //ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                            ENetPacket *p = enet_packet_create(wiad.c_str(), wiad.size()+1, ENET_PACKET_FLAG_RELIABLE);
                            enet_host_broadcast(server, 0, p);
                        }
                        else
                        {
                            char message[] = "FAIL";
                            ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
                            enet_host_broadcast(server, 0, p);
                        }
                    }
                    else if(receive(event.packet->data, "CLICK")) {
                        char message[] = "Klient nacisnal przycisk!\n";
                        ENetPacket *p = enet_packet_create(message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);

                        enet_host_broadcast(server, 0, p);
                        cout << "\nWYSLANO";
                    }

                    else if(receive(event.packet->data, "sendMeMap")) {
                        ENetPacket *p = enet_packet_create(mapa.c_str(), mapa.size()+1, ENET_PACKET_FLAG_RELIABLE);

                        enet_host_broadcast(server, 0, p);
                        cout << "\nWYSLANO MAPE";
                    }

                    else {
                        char mess[event.packet->dataLength];

                        for(int i = 0; i < event.packet->dataLength; ++i)
                            mess[i] = event.packet->data[i];

                        ENetPacket *p = enet_packet_create(mess, strlen(mess)+1, ENET_PACKET_FLAG_RELIABLE);
                        enet_host_broadcast(server, 0, p);
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
