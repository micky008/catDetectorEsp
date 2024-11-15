#include "MySD.h"

MySD::MySD(AsyncWebServer& srv) : server(srv) {}

void MySD::init() {
    if (!LittleFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
    File dir = LittleFS.open("/browser", "r");
   
    recurs(dir);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->redirect("/browser/index.html");
    });
    server.onNotFound([](AsyncWebServerRequest* request) {
        request->send(404, "text/plain", "Not found");
    });
}


void MySD::recurs(File dir) {
 while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            break;
        }
        if (entry.isDirectory()) {
           recurs(entry);
           continue;
        }
        Serial.println(entry.fullName());
        server.serveStatic(entry.fullName(), LittleFS, entry.fullName());
    }
}

void MySD::switchOn() {
    server.begin();
}