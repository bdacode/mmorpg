#ifndef RESOURCE_MANAGER_H_INCLUDED
#define RESOURCE_MANAGER_H_INCLUDED

#include "main.h"

#include "init.h"

enum RES_TYPE { RES_BITMAP, RES_AUDIO };

class CResourceManager {
public:
    RES_TYPE type;
    string name;
    static int ID;


    CResourceManager();
    ~CResourceManager();

    template <typename Arg>
    Arg load(Arg, string);
};

template <typename Arg>
Arg CResourceManager::load(Arg a, string path)
{
    string p = path + ".RES";
    fstream file(p.c_str(), ios::in);
    if(file.good())
    {
        char wC, hC, typeC;
        file >> typeC >> wC >> hC;

        if(typeC == '1') {
            int w = int(wC), h = int(hC);
            ALLEGRO_BITMAP* img = al_create_bitmap(w, h);

            al_lock_bitmap(img, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
            al_set_target_bitmap(img);
            for(int x = 0; x < w; ++x) {
                for(int y = 0; y < h; ++y) {
                    char r, g, b, a;
                    file >> r >> g >> b >> a;

                    int offset = 0;
                    if(x%2 == 0) offset = 1;
                    if(x%3 == 0) offset = 7;

                    al_put_pixel(x,y, al_map_rgba(int(r-offset), int(g-offset), int(b-offset), int(a-offset)));
                    //al_draw_pixel(x,y, al_map_rgba(255,0,0, 100));
                }
            }
            //al_set_target_bitmap(al_get_backbuffer(display));
            al_unlock_bitmap(img);

            //al_save_bitmap("player nowy.png", img);

            return img;
        }

        file.close();
    }
    else
        logger << "ERROR: Cannot open the RES file.";
}


/*else {
                fstream file(path2.c_str(), ios::out);

                file << char(al_get_bitmap_width(img)) << " " << char(al_get_bitmap_height(img)) << " 1 ";

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
            }*/



extern CResourceManager res_manager;

#endif // RESOURCE_MANAGER_H_INCLUDED
