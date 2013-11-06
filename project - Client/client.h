#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include "main.h"

extern int serviceResult;
extern ENetHost * client;
extern ENetEvent event;
extern ENetPeer* peer;
extern ENetAddress address;

void sendToServer(char*);
void sendToServerUnseq(char*, int);
bool receive(enet_uint8*, char*);
bool connectToServer(string, int);
string getPacket(enet_uint8*);

#endif // CLIENT_H_INCLUDED
