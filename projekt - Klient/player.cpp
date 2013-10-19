#include "player.h"

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
        sprintf(wiad, "%sx%s", buf, buf2);

        sendToServer(wiad);

        // receive position
        if(event.type == ENET_EVENT_TYPE_RECEIVE) {
            if(receive(event.packet->data, wiad))
                oldPos = newPos;
            else
                newPos = oldPos;
        }
    }
}

void CPlayer::render() {
    // ... TODO
    al_draw_bitmap(IMG_player, newPos.x, newPos.y, 0);
}
