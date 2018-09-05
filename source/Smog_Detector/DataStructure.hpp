#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <Arduino.h>

struct DataStructure
{
    uint16_t PM1dot0;        //  3
    uint16_t PM2dot5;        //  4
    uint16_t PM10dot0;       //  5
    uint16_t Particles0dot3; //  6
    uint16_t Particles0dot5; //  7
    uint16_t Particles1dot0; //  8
    uint16_t Particles2dot5; //  9
    uint16_t Particles5dot0; // 10
    uint16_t Particles10;    // 11
};

#endif
