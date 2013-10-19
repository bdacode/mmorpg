#include "account.hpp"

ifstream file;
void registration(string name, string password){
    file.open()
    if(!file){
        file >> name >> password;
    } else {
        cout << "Uzytkownik z taka nazwa juz istnieje!\n";
    }
    file.close();
}

void login(string name, string password){
    file.open()
    if(file){
        file << name << password;
        cout << "DANE: " << name << " " << password;
    } else {
        cout << "Uzytkownik z taka nazwa nie istnieje!\n";
    }
    file.close();
}
