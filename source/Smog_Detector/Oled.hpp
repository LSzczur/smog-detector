#ifndef OLED_HPP
#define OLED_HPP

#include <Arduino.h>
#include <U8g2lib.h>

class Oled
{
public:
    // Constructor
    Oled();

    // Destructor
    ~Oled();

    // Update display
    void updateDisplay();

private:
    // OLED display object
    U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2;
};

#endif
