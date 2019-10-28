#ifndef DUSTSENSOR_HPP
#define DUSTSENSOR_HPP

#include <Arduino.h>
#include <pms.h>
#include "DataStructure.hpp"

class DustSensor
{
public:
    // Constructor
    DustSensor();

    // Destructor
    ~DustSensor();

    // Initialize an object
    void Initialize();

    // Update dust sensor data
    Pmsx003::PmsStatus UpdateData();

    // Get data Structure
    DataStructure& GetDataStructure();

private:
    // PMS7003 dust sensor object
    Pmsx003 pms;

    // Structure contain PMS data
    DataStructure dataStructure;
};

#endif
