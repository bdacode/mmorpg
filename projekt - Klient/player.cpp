#include "player.h"

vector <COtherPlayer> v_otherPlayers;

ALLEGRO_BITMAP* IMG_player;

CPlayer::CPlayer() {
    pos.x = pos.y = oldPos.x = oldPos.y = 0;
    timeToSend = 0;

    speed = 2;

    IMG_player = loadBmp("media/player.png");

    w = getBmpW(IMG_player);
    h = getBmpH(IMG_player);
}

CPlayer::~CPlayer() {
}

void __cdecl player_updatePos(void* arg) {

    CPlayer* player = static_cast<CPlayer*>(arg);

    // receive position
    if(event.type == ENET_EVENT_TYPE_RECEIVE) {

        //cout << "\n\n# #OTRZYMANO: " << getPacket(event.packet->data);

        if(receive(event.packet->data, "POS")) {
            string mes = getPacket(event.packet->data);
            mes.erase(0,3);

            string num = "";
            num[0] = mes[0];
            int ilZnakow = atoi(num.c_str());

            mes.erase(0,1);

            string nickInnego = mes.substr(0,ilZnakow);

            int isFind = mes.find_last_of('=');

            int isFindX = mes.find_last_of('x');
            string posX = mes.substr(isFind+1,isFindX-isFind-1);
            string posY = mes.substr(isFindX+1,mes.size());

            if(nickInnego != player->nick)
            {
                bool finded = false;
                for(int i = 0; i < v_otherPlayers.size(); ++i) {
                    if(v_otherPlayers[i].nick == nickInnego) {
                        v_otherPlayers[i].pos.x = atoi(posX.c_str());
                        v_otherPlayers[i].pos.y = atoi(posY.c_str());
                        v_otherPlayers[i].timeFromLastReceive = 0;
                        finded = true;
                        break;
                    }
                }
                if(!finded) {
                    v_otherPlayers.push_back(COtherPlayer(nickInnego));
                }
            }
            else
                player->oldPos = player->pos;
        }
    }

    _endthread();
}

void CPlayer::update(CKeyboard key) {
    if(key.Press(ALLEGRO_KEY_W)) pos.y -= speed;
    if(key.Press(ALLEGRO_KEY_S)) pos.y += speed;
    if(key.Press(ALLEGRO_KEY_A)) pos.x -= speed;
    if(key.Press(ALLEGRO_KEY_D)) pos.x += speed;

    ++timeToSend;

    if(timeToSend >= 10 /*&& (oldPos.x != pos.x || oldPos.y != pos.y)*/) { //  [ 20 = 1/3 sekundy przy 60 FPS ]
        timeToSend = 0;

        // send position
        char wiad[45] = "";

        char buf[10];
        itoa(pos.x, buf, 10);
        char buf2[10];
        itoa(pos.y, buf2, 10);

        char buf4[20];
        itoa(nick.size(), buf4, 10);

        char* buf3 = new char[nick.size()];
        for(int i = 0; i < nick.size(); ++i)
            buf3[i] = nick[i];

        sprintf(wiad, "POS%s%s=%sx%s", buf4, buf3, buf, buf2);

        //sendToServer(wiad);
        sendToServerUnseq(wiad);
    }
}

void CPlayer::render() {
    // ... TODO
    al_draw_bitmap(IMG_player, 400-w/2, 300-h/2, 0);

    al_draw_filled_rectangle(400-al_get_text_width(font, nick.c_str())/2-10, 300-h/2-25,
                             400+al_get_text_width(font, nick.c_str())/2+10, 300-h/2-5,
                             al_map_rgba(0,0,0, 100));
    al_draw_text(font, al_map_rgb(255,255,255), 400, 300-h/2-30, ALLEGRO_ALIGN_CENTER, nick.c_str());
}
