#include "Configuration.h"

void Configuration::init() {
    pref = new Preferences();
    pref->begin("catDetector");
    this->distance = pref->getInt(KEY_DISTANCE, -1);
    this->ssid = pref->getString(KEY_SSID, String());
    this->wifiPwd = pref->getString(KEY_WIFIPWD, String());
}

void Configuration::saveAll() {
    pref->putInt(KEY_DISTANCE, distance);
    pref->putString(KEY_SSID, ssid);
    pref->putString(KEY_WIFIPWD, wifiPwd);
}

void Configuration::reset() { pref->clear(); }
bool Configuration::isFirstRuntime() { return distance == -1; }

int Configuration::getDistance() { return distance; }
const char* Configuration::getSSID() { return ssid.c_str(); }
const char* Configuration::getWifiPwd() { return wifiPwd.c_str(); }
void Configuration::setDistance(int dist) { distance = dist; }
void Configuration::setSSID(String ssidStr) { this->ssid = ssidStr; }
void Configuration::setWifiPwd(String pwd) { this->wifiPwd = pwd; }