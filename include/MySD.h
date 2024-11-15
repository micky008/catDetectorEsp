#ifndef ___MYSD_H__
#define ___MYSD_H__

#include "interfaces/Initialisation.h"
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

class MySD : public Initialisation {
public:
    MySD(AsyncWebServer& server);
    void init();
    void switchOn();
private:
    void recurs(File dir);
    AsyncWebServer& server;
};


#endif