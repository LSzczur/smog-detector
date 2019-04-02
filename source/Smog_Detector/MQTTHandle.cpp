#include "MQTTHandle.hpp"

const char * MQTTHandle::ssid = "Wyspa Szczura";
const char * MQTTHandle::password = "hejpiast";
const char * MQTTHandle::hostName = "SMOG Detector";

const char * MQTTHandle::brokerAddress = "192.168.88.200";
const int    MQTTHandle::brokerPort = 1883;

MQTTHandle::MQTTHandle() :
    wifiClient(),
    mqttClient(wifiClient)
{
}

MQTTHandle::~MQTTHandle()
{
}

IPAddress MQTTHandle::Initialize()
{
    const IPAddress ip = WiFiInitialize();
    MQTTInitialize();

    return ip;
}

void MQTTHandle::Callback(char * topic, byte * payload, unsigned int length)
{
    // Callback
}

void MQTTHandle::Loop()
{
    mqttClient.loop();
}

IPAddress MQTTHandle::WiFiInitialize()
{
    // Set and print host name
    Serial.println( "Hostname: " + WiFi.hostname( MQTTHandle::hostName ) );
    // Begin WiFi connection
    WiFi.begin( MQTTHandle::ssid, MQTTHandle::password );
    // Wait for a connection to be established
    while ( WiFi.status() != WL_CONNECTED )
    {
        delay( 500 );
        Serial.print( "." );
    }

    Serial.println( "" );
    Serial.print( "Connected to " );
    Serial.println( ssid );
    Serial.print( "IP address: " );
    Serial.println( WiFi.localIP() );

    return WiFi.localIP();
}

void MQTTHandle::MQTTInitialize()
{
    mqttClient.setServer(MQTTHandle::brokerAddress, MQTTHandle::brokerPort);
    mqttClient.setCallback(MQTTHandle::Callback);
}
