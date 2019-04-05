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

    // @TODO Pin 9 attached to watchdog
    // Needed change in hardware to make interrupt attach possible
    // Attach an interrupt to button
    //attachInterrupt(digitalPinToInterrupt(9),
    //                SmogDetector::InterruptHandler,
    //                RISING);

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

//void SmogDetector::InterruptHandler()
// {
//     Serial.println("BOOM!");
//     // static bool enabled = false;

//     // Oled::SetEnabled(enabled);
//     // enabled = !enabled;
// }
