
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
//#include <LittleFS.h>
#include "WIFI_CONF.H"
#include "SD.h"
#include "MySD.h"

#include "SPI.h"
#include "FS.h"

/*
  Replace the SSID and Password according to your wifi
*/
const char* ssid = SSID_WIFI;
const char* password = PWD_WIFI;

// Webserver
AsyncWebServer server(80);
MySD mySd(server);


void setup() {
    //initArduino();
    Serial.begin(115200);
    Serial.println("Starting the LittleFS Webserver..");
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);

    SPI.begin();
    Serial.println("spi.begin OK");
    if (!SD.begin(D8)) {
        Serial.println("sd.begin error");
        digitalWrite(2, HIGH);
    }
    // // Connect to WIFI
    WiFi.mode(WIFI_STA);

    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }

    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    mySd.init();

    // server.serveStatic("/index.html", LittleFS, "/index.html");
    // server.serveStatic("/favicon.ico", LittleFS, "/favicon.ico");
    // server.serveStatic("/main-3OPZESND.js", LittleFS, "/main-3OPZESND.js");
    // server.serveStatic("/polyfills-FFHMD2TL.js", LittleFS,
    //                    "/polyfills-FFHMD2TL.js");

    // server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    //     request->redirect("/index.html");
    // });



    // server.begin();
}

void loop() {}
