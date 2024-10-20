#ifndef ___MYSD_H__
#define ___MYSD_H__

#include "interfaces/Initialisation.h"
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SD.h>

class MySD {
public:
    MySD(AsyncWebServer& server);
    void init();

private:
    AsyncWebServer& server;
};


#endif