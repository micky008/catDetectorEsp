#include "MyWifi.h"

void MyWIFI::init(WifiOption& opt) {
    this->opts = opt;
    WiFi.disconnect();
    this->turnWifiMode();
}

void MyWIFI::turnWifiMode() {
    if (this->opts.getSSID() == NULL) {
        WiFi.mode(WiFiMode::WIFI_AP);
        WiFi.begin(this->apModeSSID, this->apModeWifi);
    } else {
        WiFi.mode(WiFiMode::WIFI_STA);
        WiFi.begin(this->opts.getSSID(), this->opts.getWifiPwd());
    }
}

List* MyWIFI::scan() {
    if (list != nullptr) {
        this->deleteList(list);
        list = nullptr;
    }
    WiFi.disconnect();
    int n = WiFi.scanNetworks();
    list = new List();
    List* first = list;
    for (int i = 0; i < n; i++) {
        list->ssidName = WiFi.SSID(i);
        if ((i + 1) < n) {
            list->next = new List();
            list = list->next;
        }
    }
    this->turnWifiMode();
    return first;
}

void MyWIFI::deleteList(List* curr) {
    while (curr != nullptr) {
        List* temp = curr->next;
        delete curr;
        curr = temp;
    }
}
