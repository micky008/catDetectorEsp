
#include <Arduino.h>
#include <ESP8266mDNS.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "AsyncJson.h"
#include "Configuration.h"
#include "MySD.h"
#include "MyWifi.h"
#include "Ultrason.h"

void addCORS(AsyncWebServerResponse* response);

Configuration config;
MyWIFI wifi;
AsyncWebServer server(80);
Ultrason ultrason;
MySD mysd(server);

bool scanInProgress = false;

void setup() {
    Serial.begin(115200);
    config.init();
    mysd.init();
    //ultrason.init();
    // if (config.getSSID() != NULL) {
    //     wifi.setOption(config);
    //     wifi.turnWifiMode();
    //     return;
    // }
    wifi.turnWifiMode();
    server.on("/scan", HTTP_GET, [](AsyncWebServerRequest* request) {
        Serial.println("in scan");
        wifi.init();
        AsyncWebServerResponse* response = request->beginResponse(200, "application/json", "\"value\": \"scan in progress\"");
        addCORS(response);
        request->send(response);
    });
    server.on("/wifis", HTTP_GET, [](AsyncWebServerRequest* request) {
        Serial.println("in wifis");
        if (!wifi.isScanEnded()) {
            AsyncWebServerResponse* resp = request->beginResponse(204);
            addCORS(resp);
            request->send(resp);
            return;
        }
        String res = String("value: \"scan fini\"");
        AsyncWebServerResponse* response = request->beginResponse(200, "application/json", res);
        addCORS(response);
        request->send(response);
    });
    server.on("/ping", HTTP_GET, [](AsyncWebServerRequest* request) {
        String res = "{\"ping\": $dist$ }";
        //res.replace("$dist$", String(ultrason.getDistanceInCm()));
        res.replace("$dist$", String(60));
        AsyncWebServerResponse* response = request->beginResponse(200, "application/json", res);
        addCORS(response);
        request->send(response);
    });

    AsyncCallbackJsonWebHandler* handler = new AsyncCallbackJsonWebHandler("/save", [](AsyncWebServerRequest* request, JsonVariant& json) {
        JsonObject jsonObj = json.as<JsonObject>();
        config.setInitialDistance(jsonObj["distance"].as<int>());
        config.setChatName(jsonObj["chatName"].as<String>());
        config.setServerURL(jsonObj["serverURL"].as<String>());
        config.setSSID(jsonObj["ssid"].as<String>());
        config.setWifiPwd(jsonObj["wifiPwd"].as<String>());
        config.saveAll();
        AsyncWebServerResponse* response = request->beginResponse(200, "application/json", "{\"response\":true}");
        addCORS(response);
        request->send(response);
    });

    server.addHandler(handler);
    mysd.switchOn();
}

void addCORS(AsyncWebServerResponse* response) {
    response->addHeader("Access-Control-Allow-Origin", "*");
    response->addHeader("Access-Control-Allow-Headers", "origin, content-type, accept, authorization");
    response->addHeader("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
}

void loop() {
    // MDNS.update();
    delay(1000);
    if (wifi.isScanInProgress()) {
        return;
    }
    if (wifi.isScanEnded()) {
        List* list = wifi.getResults();
        Serial.println(wifi.listToJson(list));
    }
}



//   HTTPClient http;

//   // Your Domain name with URL path or IP address with path
//   http.begin(client, serverName);

//   // If you need Node-RED/server authentication, insert user and password below
//   //http.setAuthorization("REPLACE_WITH_SERVER_USERNAME", "REPLACE_WITH_SERVER_PASSWORD");

//   // Specify content-type header
//   http.addHeader("Content-Type", "application/x-www-form-urlencoded");
//   // Data to send with HTTP POST
//   String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&value1=24.25&value2=49.54&value3=1005.14";           
//   // Send HTTP POST request
//   int httpResponseCode = http.POST(httpRequestData);