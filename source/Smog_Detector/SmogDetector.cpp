#include "SmogDetector.hpp"
#include "settings.h"

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
#ifdef DEBUG_MODE
    Serial.begin( 115200 );
#endif

    sensor.Initialize();
    const IPAddress ip = mqttHandle.Initialize();
#ifdef OLED_MODE
    oled.Initialize();
    oled.SetIPAddress(ip);
#endif

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

    const DataStructure data = sensor.GetDataStructure();

    //@TODO Remove
    //yield();

#ifdef OLED_MODE
    if ( Pmsx003::OK == status )
    {
       oled.UpdateDisplay(data);
    }
#endif

    mqttHandle.Loop(data);
}

//void SmogDetector::InterruptHandler()
// {
    // static bool enabled = false;

    // Oled::SetEnabled(enabled);
    // enabled = !enabled;
// }
