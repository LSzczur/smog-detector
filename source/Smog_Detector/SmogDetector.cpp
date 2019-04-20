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
#if DEBUG_MODE
    Serial.begin( 115200 );
#endif

    //oled.Initialize();
    sensor.Initialize();
    const IPAddress ip = mqttHandle.Initialize();
    //oled.SetIPAddress(ip);

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

    // if ( Pmsx003::OK == status )
    // {
    //    oled.UpdateDisplay(data);
    // }

    mqttHandle.Loop(data);
}

//void SmogDetector::InterruptHandler()
// {
    // static bool enabled = false;

    // Oled::SetEnabled(enabled);
    // enabled = !enabled;
// }
