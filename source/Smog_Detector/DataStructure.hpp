#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <Arduino.h>
#include <pms.h>

enum DataState
{
    PM1dot0 = 0,
    PM2dot5 = 1,
    PM10dot0 = 2
};

struct DataStructure
{
    public:
        DataStructure& operator=( const uint16_t data[] )
        {
            PM1dot0        = data[Pmsx003::PM1dot0];
            PM2dot5        = data[Pmsx003::PM2dot5];
            PM10dot0       = data[Pmsx003::PM10dot0];
            Particles0dot3 = data[Pmsx003::Particles0dot3];
            Particles0dot5 = data[Pmsx003::Particles0dot5];
            Particles1dot0 = data[Pmsx003::Particles1dot0];
            Particles2dot5 = data[Pmsx003::Particles2dot5];
            Particles5dot0 = data[Pmsx003::Particles5dot0];
            Particles10    = data[Pmsx003::Particles10];
        }

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
