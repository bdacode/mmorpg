#ifndef ACCOUNT_HPP_INCLUDED
#define ACCOUNT_HPP_INCLUDED

#include "main.h"
#include "bitmap.h"
#include "input.h"
#include "client.h"
#include "player.h"

bool registration(string, string);
bool login(string, string, CPlayer*, CCamera*);


#endif // ACCOUNT_HPP_INCLUDED
