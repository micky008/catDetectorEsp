
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include "WIFI_CONF.H"

/*
  Replace the SSID and Password according to your wifi
*/
const char *ssid = SSID_WIFI;
const char *password = PWD_WIFI;

// Webserver
AsyncWebServer server(80);

void notFound(AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Not found");
}

void setup() {
    //initArduino();
    Serial.begin(115200);
    Serial.println("Starting the LittleFS Webserver..");

    // Begin LittleFS
    if (!LittleFS.begin()) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    // Connect to WIFI
    WiFi.mode(WIFI_STA);
    
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.serveStatic("/index.html", LittleFS, "/index.html");
    server.serveStatic("/favicon.ico", LittleFS, "/favicon.ico");
    server.serveStatic("/main-3OPZESND.js", LittleFS, "/main-3OPZESND.js");
    server.serveStatic("/polyfills-FFHMD2TL.js", LittleFS,
                       "/polyfills-FFHMD2TL.js");

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->redirect("/index.html");
    });

    server.onNotFound(notFound);

    server.begin();
}

void loop() {}
