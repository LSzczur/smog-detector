#ifndef HTTPSERVER_HPP
#define HTTPSERVER_HPP

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FS.h"

class HttpServer
{
public:
    // Constructor
    HttpServer();

    // Destructor
    ~HttpServer();

    // Initialize an object
    void Initialize();

    void handleClient();

private:
    // ESP8266 Web Server object
    ESP8266WebServer server;

    // WiFi ssid where sensor connect to
    static const char* ssid;

    // WiFi password where sensor connect to
    static const char* password;
};

#endif
