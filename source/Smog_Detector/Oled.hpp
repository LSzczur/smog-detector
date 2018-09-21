#ifndef OLED_HPP
#define OLED_HPP

#include <Arduino.h>
#include <U8g2lib.h>
#include "DataStructure.hpp"
#include "Ethernet.h"

class Oled
{
public:
    // Constructor
    Oled();

    // Destructor
    ~Oled();

    // Initialize an object
    void Initialize();

    // Update display
    void UpdateDisplay(DataStructure data);

    void SetIPAddress( IPAddress ip );

    static void SetEnabled( bool val );

private:
    // OLED display object
    U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2;

    // IPAddress
    IPAddress ipaddress;

    // 
    static bool isEnabled;
};

#endif
