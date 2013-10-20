#include "player.h"

vector <COtherPlayer> v_otherPlayers;

ALLEGRO_BITMAP* IMG_player;

CPlayer::CPlayer() {
    newPos.x = newPos.y = oldPos.x = oldPos.y = 0;
    timeToSend = 0;

    IMG_player = loadBmp("media/player.png");
}

CPlayer::~CPlayer() {
}

void CPlayer::update(CKeyboard key) {
    if(key.Press(ALLEGRO_KEY_W)) newPos.y--;
    if(key.Press(ALLEGRO_KEY_S)) newPos.y++;
    if(key.Press(ALLEGRO_KEY_A)) newPos.x--;
    if(key.Press(ALLEGRO_KEY_D)) newPos.x++;

    ++timeToSend;
    if(timeToSend >= 20) { // 1/3 sekundy przy 60 FPS
        timeToSend = 0;

        // send position
        char wiad[64];

        char buf[10];
        itoa(newPos.x, buf, 10);
        char buf2[10];
        itoa(newPos.y, buf2, 10);

        char buf3[nick.size()];
        for(int i = 0; i < nick.size(); ++i)
            buf3[i] = nick[i];

        sprintf(wiad, "POS%s=%sx%s", buf3, buf, buf2);

        sendToServer(wiad);

        // receive position
        if(event.type == ENET_EVENT_TYPE_RECEIVE) {

            //cout << "\n\n# #OTRZYMANO: " << getPacket(event.packet->data);

            if(receive(event.packet->data, "POS")) {
                string mes = getPacket(event.packet->data);
                mes.erase(0,3);
                int isFind = mes.find('=');
                string nickInnego = mes.substr(0,isFind);

                if(nickInnego != nick) {
                    bool finded = false;
                    for(int i = 0; i < v_otherPlayers.size(); ++i) {
                        if(v_otherPlayers[i].nick == nickInnego) {
                            int isFindX = mes.find('x');
                            string posX = mes.substr(isFind+1,isFindX);
                            string posY = mes.substr(isFindX+1,mes.size());
                            //cout << "\nPOSX: " << posX << ", Y: " << posY;
                            v_otherPlayers[i].pos.x = atoi(posX.c_str());
                            v_otherPlayers[i].pos.y = atoi(posY.c_str());
                            finded = true;
                        }
                    }
                    if(!finded) {
                        v_otherPlayers.push_back(COtherPlayer(mes.substr(0,isFind)));
                    }
                }
            }
        }
    }
}

void CPlayer::render() {
    // ... TODO
    al_draw_bitmap(IMG_player, newPos.x, newPos.y, 0);
}
