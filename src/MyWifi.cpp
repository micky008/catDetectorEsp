#include "MyWifi.h"
#include <iostream>
#include <functional>

void MyWIFI::setOption(WifiOption& opt) {
    this->opts = &opt;
}


void MyWIFI::turnWifiMode() {
    //WiFi.disconnect();
    //if (this->opts->getSSID() == NULL) {
    //WiFi.mode(WiFiMode::WIFI_AP);
    Serial.println(this->apModeSSID);
    WiFi.softAP(this->apModeSSID, this->apModeWifi);
    Serial.println(WiFi.softAPIP());
    //}
    //else {
    //   WiFi.mode(WiFiMode::WIFI_STA);
    //    WiFi.begin(this->opts->getSSID(), this->opts->getWifiPwd());
    //}

}

void MyWIFI::init() {
    WiFi.scanNetworks(true);
}

bool MyWIFI::isScanInProgress() {
    wifiResult = WiFi.scanComplete();
    return wifiResult == WIFI_SCAN_RUNNING || wifiResult == WIFI_SCAN_FAILED;
}

bool MyWIFI::isScanEnded() {
    return wifiResult != WIFI_SCAN_RUNNING && wifiResult != WIFI_SCAN_FAILED;
}

void MyWIFI::reset() {
    wifiResult = WIFI_SCAN_RUNNING;
}

List* MyWIFI::getResults() {
    if (list != nullptr) {
        this->deleteList(list);
        list = nullptr;
    }
    list = new List();
    List* first = list;
    for (int i = 0; i < wifiResult; i++) {        
        list->ssidName = WiFi.SSID(i);
         if ((i + 1) < wifiResult) {
             list->next = new List();
             list = list->next;
        }
        delay(2000);
    }
    WiFi.scanDelete();
    wifiResult = WIFI_SCAN_RUNNING;
    return first;
}

void MyWIFI::deleteList(List* curr) {
    while (curr != nullptr) {
        List* temp = curr->next;
        delete curr;
        curr = temp;
    }
}

String MyWIFI::listToJson(List* list) {
    if (list == nullptr) {
        return String();
    }
    List* first = list;
    resForJson = "[";
    while (first->next != nullptr) {
        resForJson += "\"" + first->ssidName + "\"";
    }
    resForJson += "]";
    return resForJson;
}
