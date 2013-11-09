#include "players.h"

vector <CClient> v_clients;

CClient::CClient()
{
    x = y = 0;
    nick = "Anonymous";
}

CClient::CClient(int x, int y, string n)
{
    this->x = x;
    this->y = y;
    this->nick = n;
}
