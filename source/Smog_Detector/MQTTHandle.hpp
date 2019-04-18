#ifndef MQTTHANDLE_HPP
#define MQTTHANDLE_HPP

#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#include "DataStructure.hpp"

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
    void Loop(const DataStructure dataToSend);

private:

    // Initialize WiFi object
    IPAddress WiFiInitialize();

    // Initialize MQTT object
    void MQTTInitialize();

    // Reconnect MQTT
    bool Reconnect();

    // Publish data
    void PublishData(const DataStructure dataToSend);

    // ESP8266 WiFi client object
    WiFiClient wifiClient;

    // MQTT client object
    PubSubClient mqttClient;

    // Milliseconds since last reconnect attempt
    long lastReconnectAttempt;

};

#endif
