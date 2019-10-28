#include <ArduinoJson.h>
#include "MQTTHandle.hpp"
#include "settings.h"

bool MQTTHandle::isMqttReadyToSendData = false;

MQTTHandle::MQTTHandle() :
    wifiClient(),
    mqttClient(wifiClient),
    lastReconnectAttempt(0),
    ticker()
{
}

MQTTHandle::~MQTTHandle()
{
    ticker.detach();
}

IPAddress MQTTHandle::Initialize()
{
    const IPAddress ip = WiFiInitialize();
    MQTTInitialize();
    
    // ticker the pin every STAT_PERIOD [s]
    ticker.attach(STAT_PERIOD, MQTTHandle::Interrupt);

    return ip;
}

void MQTTHandle::Interrupt()
{
#ifdef DEBUG_MODE
    Serial.println("Timer interrupt reached!");
#endif
    MQTTHandle::isMqttReadyToSendData = true;
}

void MQTTHandle::Callback(char * topic, byte * payload, unsigned int length)
{
////     @TODO Callback implementation
// #ifdef DEBUG_MODE
//     Serial.println("MQTT Callback!");
// #endif
//     for(int i=0; i < length; ++i)
//     {
// #ifdef DEBUG_MODE
//         Serial.print(static_cast<char>(payload[i]));
// #endif
//     }
// #ifdef DEBUG_MODE
//     Serial.println();
// #endif

//     const std::string msg = "MQTT Callback!";
//     byte * pMsg = (byte *)malloc(msg.length());
//     memcpy(pMsg, payload, msg.length());
//     free(pMsg);
}

void MQTTHandle::Loop(const DataStructure& dataToSend)
{
    if (mqttClient.connected())
    {
        mqttClient.loop();
        if (MQTTHandle::isMqttReadyToSendData)
        {
            PublishData(dataToSend);
            MQTTHandle::isMqttReadyToSendData = false;
        }
    }
    else
    {
        long now = millis();
        if (now - lastReconnectAttempt > 5000)
        {
            lastReconnectAttempt = now;

            //@TODO Remove
            yield();
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
#ifdef DEBUG_MODE
    Serial.println( "Hostname: " + WiFi.hostname( STA_HOST_NAME ) );
#endif
    // Begin WiFi connection
    WiFi.begin( STA_SSID, STA_PASS );
    // Wait for a connection to be established
    while ( WiFi.status() != WL_CONNECTED )
    {
        delay( 500 );
#ifdef DEBUG_MODE
        Serial.print( "." );
#endif
    }

#ifdef DEBUG_MODE
    Serial.println( "" );
    Serial.print( "Connected to " );
    Serial.println( STA_SSID );
    Serial.print( "IP address: " );
    Serial.println( WiFi.localIP() );
#endif

    return WiFi.localIP();
}

void MQTTHandle::MQTTInitialize()
{
    mqttClient.setServer( MQTT_HOST, MQTT_PORT );
    mqttClient.setCallback( MQTTHandle::Callback );
}

bool MQTTHandle::Reconnect()
{
#ifdef DEBUG_MODE
    Serial.print("Reconnect...");
#endif
    if ( mqttClient.connect( MQTT_HOST, MQTT_USER, MQTT_PASS ) )
    {
        // Once connected, publish an announcement...
        mqttClient.publish( TELE_FULLTOPIC, "Connected to MQTT Host!" );
        // ... and resubscribe
        mqttClient.subscribe( SUB_FULLTOPIC );
    }
    else
    {
#ifdef DEBUG_MODE
        Serial.print( "failed, rc=" );
        Serial.print( mqttClient.state() );
        Serial.println( " try again in 5 seconds" );
#endif
        // Wait 5 seconds before retrying
        delay( 5000 );
    }

#ifdef DEBUG_MODE
    Serial.println(mqttClient.connected());
#endif

    return mqttClient.connected();
}

void MQTTHandle::PublishData(const DataStructure dataToSend)
{
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.createObject();
    root["PM1dot0"] = (String)dataToSend.PM1dot0;
    root["PM2dot5"] = (String)dataToSend.PM2dot5;
    root["PM10dot0"] = (String)dataToSend.PM10dot0;
#ifdef DEBUG_MODE
    Serial.println("Publish MQTT Message:");
    root.prettyPrintTo(Serial);
#endif

    char data[200];
    root.printTo( data, root.measureLength() + 1) ;
    mqttClient.publish( PUB_FULLTOPIC, data, true );
    yield();
}
