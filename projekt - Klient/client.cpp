#include "client.h"

int serviceResult = 1;
ENetHost * client;
ENetEvent event;
ENetPeer* peer;
ENetAddress address;

void sendToServer(char* message) {
    ENetPacket *p = enet_packet_create((char*)message, strlen(message)+1, ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(peer, 0, p);

    enet_host_flush(client);

    serviceResult = enet_host_service(client, &event, 5000);

    //serviceResult = enet_host_check_events(client, &event);
}

bool receive(enet_uint8* wiad, char* wiad2) {
    if(wiad == NULL)
        return false;

    for(int i = 0; i < strlen(wiad2); ++i)
        if(wiad[i] != wiad2[i])
            return false;

    return true;
}

bool connectToServer(string serverIP, int PORT) {
    // klient
    client = enet_host_create(NULL, 1, 2, 57600/8, 14400/8);
    if(client == NULL){
        logger << "ERROR: Create ENet client host.";
        return false;
    }

    // adres
    enet_address_set_host(&address, serverIP.c_str());
    address.port = PORT;

    // peer
    peer = enet_host_connect(client, &address, 1, 0);
    if(peer==NULL){
        logger << "ERROR: Nie ma dostepnego polaczenia do serwera.";
        return false;
    }

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
