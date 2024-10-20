#include "MySD.h"

MySD::MySD(AsyncWebServer& srv) : server(srv) {}

void MySD::init() {
    File dir = SD.open("/browser", "r");
    while (true) {
        File entry = dir.openNextFile();
        if (!entry) {
            break;
        }
        //const char* forServerPath = String('/browser/' + entry.name()).c_str();
        const char* forServerRoute = String('/' + entry.name()).c_str();
        server.serveStatic(forServerRoute, SDFS, forServerRoute);
    }

    server.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
        request->redirect("/index.html");
    });
    server.onNotFound([](AsyncWebServerRequest* request) {
        request->send(404, "text/plain", "Not found");
    });

    server.begin();
}

