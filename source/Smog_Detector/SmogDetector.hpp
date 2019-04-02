#ifndef SMOGDETECTOR_HPP
#define SMOGDETECTOR_HPP

#include <Arduino.h>
#include "Oled.hpp"
#include "DustSensor.hpp"
#include "MQTTHandle.hpp"

class SmogDetector
{
public:
    // Constructor
    SmogDetector();

    // Destructor
    ~SmogDetector();

    // Initialize module
    bool Initialize();

    // Loop
    bool Loop();

    // Button interrupt handler (hardware change needed)
    // static void InterruptHandler();

private:
    // OLED display object
    Oled oled;

    // PMS7003 dust sensor object
    DustSensor sensor;

    // MQTT object
    MQTTHandle mqttHandle;

};

#endif
