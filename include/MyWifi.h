#ifndef __MY_WIFI_H__
#define __MY_WIFI_H__
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include "interfaces/WifiOption.h"

class List {
   public:
    List* next = nullptr;
    String ssidName;
};

class MyWIFI {
   public:
    void init(WifiOption& opt);
    List* scan();

   private:
    List* list = nullptr;
    bool isSTAMode = false;
    WifiOption& opts;
    String apModeSSID = "CatDetector";
    String apModeWifi = "0123456";
    void deleteList(List* l);
    void turnWifiMode();
};

#endif
