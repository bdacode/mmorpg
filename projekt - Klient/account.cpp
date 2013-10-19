#include "account.hpp"

bool registration(string name, string password){
    char wiad[49];

    if(name.length()>20){ cout << "Nazwa za dluga!\n"; return false; }
    if(password.length()>20){ cout << "Haslo za dlugie!\n"; return false; }

    string whole="register"+name+":"+password;
    strcat(wiad, whole.c_str());
    sendToServer(wiad);
    cout << "Wyslano\n";

    while(1){
        if(event.type == ENET_EVENT_TYPE_RECEIVE) {
            if(receive(event.packet->data, "GOOD")) {
                cout << "REJESTRACJA ZAKONCZONA POMYSLNIE!" << endl;
                return true;
                break;
            }
            else if(receive(event.packet->data, "FAIL")) {
                cout << "REJESTRACJA ZAKONCZONA NEGATYWNIE!" << endl;
                return false;
                break;
            }
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
