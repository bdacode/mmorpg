#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <fstream>
#include <conio.h>

using namespace std;

int main()
{
    system("title Resource Converter");
    al_init();
    al_init_image_addon();
    string path, path2, type;

    while(1) {
        system("cls");
        cout << "Type EXIT to exit.\n\nType: 'Convert file' 'New name'+RES 'Type'";
        cout << "\nType: RES_BITMAP / RES_AUDIO";
        cout << "\n\nExample:   file.png file RES_BITMAP\n\n\n>> ";
        cin >> path >> path2 >> type;
        path2 += ".RES";

        if     (type == "RES_BITMAP") type = "1";
        else if(type == "RES_AUDIO")  type = "2";
        else                          type = "0";

        if(path == "EXIT" || path == "exit")
            break;

        if(type == "1") { // RES_BITMAP
            ALLEGRO_BITMAP* img = al_load_bitmap(path.c_str());
            ALLEGRO_COLOR color;

            if(!img) cout << "\nCannot open this file!";
            else {
                fstream file(path2.c_str(), ios::out);

                file << "1 " << char(al_get_bitmap_width(img)) << " " << char(al_get_bitmap_height(img)) << " ";

                al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
                for(int x = 0; x < al_get_bitmap_width(img); ++x) {
                    for(int y = 0; y < al_get_bitmap_height(img); ++y) {
                        color = al_get_pixel(img, x, y);
                        int offset = 0;
                        if(x%2 == 0) offset = 1;
                        if(x%3 == 0) offset = 7;
                        int cR = int(color.r*255)+offset;
                        int cG = int(color.g*255)+offset;
                        int cB = int(color.b*255)+offset;
                        int cA = int(color.a*255)+offset;

                        file << char(cR) << " " << char(cG) << " " << char(cB) << " " << char(cA) << " ";
                    }
                }
                al_unlock_bitmap(img);
            }
        } else {
            cout << "\nWrong type!";
        }

        cout << "\nType anything to continue.";

        getch();
    }

    return 0;
}
