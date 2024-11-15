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

class MyWIFI : public Initialisation, public IOption<WifiOption> {
public:
    void setOption(WifiOption& opt);
    List* getResults();
    void turnWifiMode();
    String listToJson(List* list);
    /*Init scan*/
    void init();
    bool isScanInProgress();
    bool isScanEnded();
    void reset();

private:
    List* list = nullptr;
    bool isSTAMode = false;
    WifiOption* opts;
    String apModeSSID = "CatDetector";
    String apModeWifi = "0123456789";
    void deleteList(List* l);
    int wifiResult = WIFI_SCAN_RUNNING;
    String resForJson;
};

#endif
