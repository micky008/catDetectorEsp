#ifndef __MY_WIFI_H__
#define __MY_WIFI_H__
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "interfaces/WifiOption.h"
#include "interfaces/IOptions.h"
#include "interfaces/Initialisation.h"

class List {
public:
    List* next = nullptr;
    String ssidName;
};

class MyWIFI : public IOption<WifiOption> {
public:
    void setOption(WifiOption& opt);
    void turnWifiMode();


private:
    bool isSTAMode = false;
    WifiOption* opts;
    String apModeSSID = "CatDetector";
    String apModeWifi = "0123456789";
};

#endif
