#include "Oled.hpp"
#include <SPI.h>

Oled::Oled() :
    u8g2( U8G2_R0, /* clock=*/14, /* data=*/16, /* cs=*/12, /* dc=*/13 )
{
}

Oled::~Oled()
{
}

void Oled::Initialize()
{
    SPI.begin();
    u8g2.begin();
}

void Oled::UpdateDisplay(DataStructure data)
{
    u8g2.clearBuffer();
    u8g2.setFont( u8g2_font_logisoso16_tf );
    u8g2.setCursor( 0, 35 );
    u8g2.print( "PM 1.0 = " );
    u8g2.print( data.PM1dot0 );
    u8g2.setCursor( 0, 70 );
    u8g2.print( "PM 2.5 = " );
    u8g2.print( data.PM2dot5 );
    u8g2.setCursor( 0, 105 );
    u8g2.print( "PM 10 = " );
    u8g2.print( data.PM10dot0 );
    u8g2.sendBuffer();
}