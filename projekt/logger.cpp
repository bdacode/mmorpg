#include "logger.h"

CLogger logger;

void CLogger::start(char* file)
{
    this->file.open(file, ios::out | ios::app);
}

void CLogger::stop()
{
    file.close();
}
