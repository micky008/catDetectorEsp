#ifndef __MYCONFIG_H__
#define __MYCONFIG_H__
#include <Preferences.h>

#include "interfaces/Initialisation.h"
#include "interfaces/UltrasonOpts.h"
#include "interfaces/WifiOption.h"
#include "interfaces/LittiereOpts.h"

class Configuration : public Initialisation,
                      public UltrasonOption,
                      public LittiereOption,
                      public WifiOption {
   public:
    void init();
    void saveAll();
    void reset();
    bool isFirstRuntime();
    int getInitialDistance();
    void setInitialDistance(int dist);
    const char* getSSID();
    void setSSID(String ssid);
    const char* getWifiPwd();
    void setWifiPwd(String pwd);
    String getChatName();
    void setChatName(String id);
    String getServerURL();
    void setServerURL(String url);


   private:
    const char* KEY_DISTANCE = "dist";
    const char* KEY_SSID = "ssid";
    const char* KEY_WIFIPWD = "pwdwifi";
    const char* KEY_CHATNAME = "chatname";
    const char* KEY_URLSERVER = "urlServer";

    Preferences* pref;
    int distance = -1;
    String ssid;
    String wifiPwd;
    String chatName;
    String serverUrl;
};

#endif