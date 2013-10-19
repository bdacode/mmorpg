#include "account.hpp"

bool registration(string name, string password){
    char wiad[64];
    char buf[10];
    char buf2[10];
    //itoa(name, buf, 10);
    //itoa(password.y, buf2, 10);
    sprintf(wiad, "%sx%s", buf, buf2);
    sendToServer(wiad);
    sendToServer("rejestration");

    if(event.type == ENET_EVENT_TYPE_RECEIVE) {
        if(receive(event.packet->data, "GOOD")) {
            cout << "REJESTRACJA ZAKONCZONA POMYSLNIE!" << endl;
            return true;
        }
        else if(receive(event.packet->data, "FAIL")) {
            cout << "REJESTRACJA ZAKONCZONA NEGATYWNIE!" << endl;
            return false;
        }
    }
}

void login(string name, string password){
    sendToServer("login");
    if(event.type == ENET_EVENT_TYPE_RECEIVE) {

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
