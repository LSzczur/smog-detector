#include "Oled.hpp"
#include <SPI.h>

Oled::Oled() :
    u8g2( U8G2_R0, /* clock=*/14, /* data=*/16, /* cs=*/12, /* dc=*/13 )
{
    SPI.begin();
    u8g2.begin();
}

Oled::~Oled()
{
}

void Oled::updateDisplay()
{
    static uint8_t n;

    Serial.print( "OLED TEST" );

    u8g2.clearBuffer();
    u8g2.setFont( u8g2_font_logisoso16_tf );
    u8g2.setCursor( 0, 35 );
    u8g2.print( "OLED TEST" );
    u8g2.setCursor( 0, 70 );
    u8g2.print( n );
    n++;
    u8g2.sendBuffer();
}