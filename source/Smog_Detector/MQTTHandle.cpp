#include "MQTTHandle.hpp"

const char * MQTTHandle::ssid = "Wyspa Szczura";
const char * MQTTHandle::password = "hejpiast";
const char * MQTTHandle::hostName = "SMOG Detector";

IPAddress MQTTHandle::brokerAddress(192, 168, 88, 200);
const int    MQTTHandle::brokerPort = 1883;
const char * MQTTHandle::brokerLogin = "SmogDetector";
const char * MQTTHandle::brokerPassword = "SmogIsBad";

MQTTHandle::MQTTHandle() :
    wifiClient(),
    mqttClient(wifiClient),
    lastReconnectAttempt(0)
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
    Serial.println("MQTT Callback!");

    for(int i=0; i < length; ++i)
    {
        Serial.print(static_cast<char>(payload[i]));
    }
    Serial.println();

    const std::string msg = "Hi!";
    byte * pMsg = (byte *)malloc(msg.length());
    memcpy(pMsg, payload, msg.length());
    free(pMsg);

}

void MQTTHandle::Loop()
{
    if (mqttClient.connected())
    {
        mqttClient.loop();
    }
    else
    {
        long now = millis();
        if (now - lastReconnectAttempt > 5000)
        {
            lastReconnectAttempt = now;
            if (Reconnect())
            {
                lastReconnectAttempt = 0;
            }
        }
    }
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

bool MQTTHandle::Reconnect()
{
    if ( mqttClient.connect( MQTTHandle::hostName,
                             MQTTHandle::brokerLogin,
                             MQTTHandle::brokerPassword ) )
    {
        // Once connected, publish an announcement...
        mqttClient.publish( "outTopic", "hello world" );
        // ... and resubscribe
        mqttClient.subscribe( "inTopic" );
    }
    else
    {
        Serial.print( "failed, rc=" );
        Serial.print( mqttClient.state() );
        Serial.println( " try again in 5 seconds" );
        // Wait 5 seconds before retrying
        delay( 5000 );
    }

    return mqttClient.connected();
}