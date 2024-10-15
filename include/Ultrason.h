#ifndef __ULTRASON_H__
#define __ULTRASON_H__

#include <NewPingESP8266.h>

#include "interfaces/IOptions.h"
#include "interfaces/Initialisation.h"
#include "interfaces/UltrasonOpts.h"

class Ultrason : public Initialisation, public IOption<UltrasonOption> {
   private:
    NewPingESP8266* sonar;
    const int TRIGGER_PIN = 12;
    const int ECHO_PIN = 11;
    const int MAX_DISTANCE = 200;  // sensor distance MAX in cm
    const unsigned long TRIGGER =
        15;  // in cm distance between the end of littiere and cat
    unsigned long initialDistance = 0;

   public:
    void init();
    void setOption(UltrasonOption& opt);
    int getDistanceInCm();
    bool isCatHere();
};

#endif