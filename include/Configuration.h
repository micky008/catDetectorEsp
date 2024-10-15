#ifndef __MYCONFIG_H__
#define __MYCONFIG_H__
#include <Preferences.h>

#include "interfaces/Initialisation.h"
#include "interfaces/UltrasonOpts.h"
#include "interfaces/WifiOption.h"

class Configuration : public Initialisation,
                      public UltrasonOption,
                      public WifiOption {
   public:
    void init();
    void saveAll();
    void reset();
    bool isFirstRuntime();
    int getDistance();
    void setDistance(int dist);
    const char* getSSID();
    void setSSID(String ssid);
    const char* getWifiPwd();
    void setWifiPwd(String pwd);

   private:
    const char* KEY_DISTANCE = "dist";
    const char* KEY_SSID = "ssid";
    const char* KEY_WIFIPWD = "pwdwifi";

    Preferences* pref;
    int distance = -1;
    String ssid;
    String wifiPwd;
};

#endif