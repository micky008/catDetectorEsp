#include "MyWifi.h"

void MyWIFI::setOption(WifiOption& opt) {
    this->opts = &opt;
}

void MyWIFI::turnWifiMode() {
    WiFi.disconnect();
    if (this->opts->getSSID() == NULL) {
        WiFi.softAP(this->apModeSSID, this->apModeWifi);
    }
    else {
        WiFi.mode(WiFiMode::WIFI_STA);
        WiFi.begin(this->opts->getSSID(), this->opts->getWifiPwd());
    }

}
