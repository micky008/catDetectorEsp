#ifndef __WIFI_OPTION_H__
#define __WIFI_OPTION_H__

class WifiOption {
   public:
    virtual const char* getSSID() = 0;
    virtual const char* getWifiPwd() = 0;
};

#endif