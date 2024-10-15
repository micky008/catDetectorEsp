
#include "Ultrason.h"

void Ultrason::init() {
    sonar = new NewPingESP8266(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
}

int Ultrason::getDistanceInCm() { return sonar->ping_cm(); }

void Ultrason::setOption(UltrasonOption& opt) {
    initialDistance = opt.getDistance();
}

bool Ultrason::isCatHere() {
    return (initialDistance - sonar->ping_cm()) >= TRIGGER;
}