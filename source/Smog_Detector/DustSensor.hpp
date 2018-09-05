#ifndef DUSTSENSOR_HPP
#define DUSTSENSOR_HPP

#include <Arduino.h>
#include <pms.h>

class DustSensor
{
public:
    // Constructor
    DustSensor();

    // Destructor
    ~DustSensor();

    // Update dust sensor data
    Pmsx003::PmsStatus updateData();

private:
    // PMS7003 dust sensor object
    Pmsx003 pms;

    uint16_t data[Pmsx003::Reserved];

};

#endif
