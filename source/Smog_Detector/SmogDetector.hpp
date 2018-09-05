#ifndef SMOGDETECTOR_HPP
#define SMOGDETECTOR_HPP

#include <Arduino.h>
#include <pms.h>
#include <U8g2lib.h>

class SmogDetector
{
public:
    // Constructor
    SmogDetector();

    // Destructor
    ~SmogDetector();

    // Initialize module
    bool Initialize();

private:
    // OLED display object
    U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2;

    // PMS7003 dust sensor object
    Pmsx003 pms;
};

#endif
