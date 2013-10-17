#include "player.h"

ALLEGRO_BITMAP* IMG_player;

CPlayer::CPlayer() {
    pos.x = pos.y = 0;

    IMG_player = loadBmp("media/player.png");
}

CPlayer::~CPlayer() {
}

void CPlayer::render() {
    // ... TODO
    al_draw_bitmap(IMG_player, pos.x, pos.y, 0);
}
