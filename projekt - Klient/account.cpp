#include "account.hpp"

bool registration(string name, string password){
    char wiad[49]="";

    if(name.length()>20){ cout << "Nazwa za dluga!\n"; return false; }
    if(password.length()>20){ cout << "Haslo za dlugie!\n"; return false; }

    string whole="register"+name+":"+password;
    strcat(wiad, whole.c_str());
    sendToServer(wiad);
    cout << "Wyslano\n";

    //while(1) {
        cout << "Oczekiwanie na info od serwera!\n";
        if(event.type == ENET_EVENT_TYPE_RECEIVE) {
            if(receive(event.packet->data, "GOOD")) {
                cout << "REJESTRACJA ZAKONCZONA POMYSLNIE!" << endl;
                return true;
                //break;
            }
            else if(receive(event.packet->data, "FAIL")) {
                cout << "REJESTRACJA ZAKONCZONA NEGATYWNIE!" << endl;
                return false;
                //break;
            }
        }
    //}
}

bool login(string name, string password, CPlayer* player, CCamera* camera){
    char wiad[49]="";

    if(name.length()>20){ cout << "Name too long!\n"; return false; }
    if(password.length()>20){ cout << "Password too long!\n"; return false; }

    string whole="login"+name+":"+password;
    strcat(wiad, whole.c_str());
    player->nick = name;
    sendToServer(wiad);

    cout << "Sent!\n";

    while(1) {
        if(event.type == ENET_EVENT_TYPE_RECEIVE) {

            if(receive(event.packet->data, "GOOD")) {
                cout << "\nLogged!\n" << endl;

                string wiad = getPacket(event.packet->data);

                string var = "";
                int index = 0, what = 0;
                for(int i = 5; i < wiad.size()+2; ++i) {
                    if(wiad[i] != ' ') {
                        var.resize(var.size()+1);
                        var[index] = wiad[i];
                        ++index;
                    }
                    else {
                        index = 0;
                        ++what;
                        if(what == 1) player->hair = atoi(var.c_str());
                        if(what == 2) player->head = atoi(var.c_str());
                        if(what == 3) player->body = atoi(var.c_str());
                        if(what == 4) player->leg = atoi(var.c_str());
                        if(what == 5) player->boots = atoi(var.c_str());
                        if(what == 6) player->pos.x = atoi(var.c_str());
                        if(what == 7) player->pos.y = atoi(var.c_str());
                        var = "";
                    }
                }

                camera->setPos(player->pos.x, player->pos.y);

                return true;
            }
            else if(receive(event.packet->data, "FAIL")) {
                cout << "\nError when logging!\n" << endl;
                return false;
            }
            else {
                cout << "\nUuu smieci dostaje!\n" << endl;
                return false;
            }
        }
    }
}

/*if(!file){
        file >> name >> password;
    } else {
        cout << "Uzytkownik z taka nazwa juz istnieje!\n";
    }
    file.close();

file.open()
    if(file){
        file << name << password;
        cout << "DANE: " << name << " " << password;
    } else {
        cout << "Uzytkownik z taka nazwa nie istnieje!\n";
    }
    file.close();*/
