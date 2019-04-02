#ifndef MQTTHANDLE_HPP
#define MQTTHANDLE_HPP

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

class MQTTHandle
{
public:
    // Constructor
    MQTTHandle();

    // Destructor
    ~MQTTHandle();

    // Initialize class
    IPAddress Initialize();

    // Callback method
    static void Callback(char * topic, byte * payload, unsigned int length);

    // MQTT Loop Handle
    void Loop();

private:

    // Initialize WiFi object
    IPAddress WiFiInitialize();

    // Initialize MQTT object
    void MQTTInitialize();

    // ESP8266 WiFi client object
    WiFiClient wifiClient;

    // MQTT client object
    PubSubClient mqttClient;

    // WiFi ssid where sensor connect to
    static const char* ssid;

    // WiFi password where sensor connect to
    static const char* password;

    // WiFi host name
    static const char * hostName;

    // MQTT server address
    static const char * brokerAddress;

    // MQTT server port
    static const int brokerPort;

};

#endif
