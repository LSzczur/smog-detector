#include "SmogDetector.hpp"

SmogDetector::SmogDetector() :
    oled(),
    sensor(),
    mqttHandle()
{
}

SmogDetector::~SmogDetector()
{
}

bool SmogDetector::Initialize()
{
    // Set debug serial
    Serial.begin( 115200 );

    oled.Initialize();
    sensor.Initialize();
    const IPAddress ip = mqttHandle.Initialize();
    oled.SetIPAddress(ip);

    // Attach an interrupt to button
    attachInterrupt(digitalPinToInterrupt(9),
                    SmogDetector::InterruptHandler,
                    RISING);

}

bool SmogDetector::Loop()
{
    Pmsx003::PmsStatus status = sensor.UpdateData();
    if ( Pmsx003::OK == status )
    {
        oled.UpdateDisplay(sensor.GetDataStructure());
    }
    mqttHandle.Loop();
    //httpServer.handleClient();
}

void SmogDetector::InterruptHandler()
{
    static bool enabled = false;

    Oled::SetEnabled(enabled);
    enabled = !enabled;
}