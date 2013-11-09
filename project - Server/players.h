#ifndef PLAYERS_H_INCLUDED
#define PLAYERS_H_INCLUDED

#include "main.h"


class CClient {
public:
    int x, y;
    string nick;

    CClient();
    CClient(int, int, string);
};

extern vector <CClient> v_clients;

#endif // PLAYERS_H_INCLUDED
