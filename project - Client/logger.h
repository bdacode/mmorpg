#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

class CLogger
{
    fstream file;

    public:

    void start(char*);
    void stop();
    void operator << (string data)
    {
        cout << endl;
        cout << "#LOG:  " << data;
        if(file.good())
        {
            string logMsg = "\n"+data;
            file << logMsg;
        }
    }

};

extern CLogger logger;

#endif // LOGGER_H_INCLUDED
