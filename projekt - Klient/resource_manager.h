#ifndef RESOURCE_MANAGER_H_INCLUDED
#define RESOURCE_MANAGER_H_INCLUDED

#include "main.h"
#include<map>

enum RES_TYPE { RES_BITMAP, RES_AUDIO };

class CResourceManager {
public:
    RES_TYPE type;
    string name;
    static int ID;


    CResourceManager();
    ~CResourceManager();
    void load(RES_TYPE, string);
};


#endif // RESOURCE_MANAGER_H_INCLUDED
