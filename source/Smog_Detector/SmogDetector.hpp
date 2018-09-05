#ifndef SMOGDETECTOR_HPP
#define SMOGDETECTOR_HPP

#include <Arduino.h>
#include "Oled.hpp"
#include "DustSensor.hpp"

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

private:
    // OLED display object
    Oled oled;

    // PMS7003 dust sensor object
    DustSensor sensor;

};

#endif
