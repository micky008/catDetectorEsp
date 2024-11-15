#include "Configuration.h"

void Configuration::init() {
    pref = new Preferences();
    pref->begin("catDetector");
    this->distance = pref->getInt(KEY_DISTANCE, -1);
    this->ssid = pref->getString(KEY_SSID, String());
    this->wifiPwd = pref->getString(KEY_WIFIPWD, String());
    this->chatName = pref->getString(KEY_CHATNAME, String());
    this->chatName = pref->getString(KEY_URLSERVER, String());
}

void Configuration::saveAll() {
    pref->putInt(KEY_DISTANCE, distance);
    pref->putString(KEY_SSID, ssid);
    pref->putString(KEY_WIFIPWD, wifiPwd);
    pref->putString(KEY_CHATNAME, chatName);
    pref->putString(KEY_URLSERVER, serverUrl);
}

void Configuration::reset() { pref->clear(); }
bool Configuration::isFirstRuntime() { return distance == -1; }

int Configuration::getInitialDistance() { return distance; }
const char* Configuration::getSSID() { return ssid.isEmpty() ? NULL : ssid.c_str(); }
const char* Configuration::getWifiPwd() { return wifiPwd.c_str(); }
void Configuration::setInitialDistance(int dist) { distance = dist; }
void Configuration::setSSID(String ssidStr) { this->ssid = ssidStr; }
void Configuration::setWifiPwd(String pwd) { this->wifiPwd = pwd; }
String Configuration::getChatName() { return this->chatName; }
void Configuration::setChatName(String name) { this->chatName = name; }
String Configuration::getServerURL() { return this->serverUrl; }
void Configuration::setServerURL(String url) { this->serverUrl = url; }