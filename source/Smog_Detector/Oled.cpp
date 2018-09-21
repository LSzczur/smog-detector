#include "Oled.hpp"
#include <SPI.h>

bool Oled::isEnabled = true;

Oled::Oled() :
    u8g2( U8G2_R0, /* clock=*/14, /* data=*/16, /* cs=*/12, /* dc=*/13 ),
    ipaddress()
{
}

Oled::~Oled()
{
}

void Oled::Initialize()
{
    SPI.begin();
    u8g2.begin();
    u8g2.enableUTF8Print();
}

void Oled::UpdateDisplay( DataStructure data )
{
    
    if ( Oled::isEnabled )
    {
        u8g2.clearBuffer();
        // u8g2.setFont( u8g2_font_open_iconic_all_2x_t );
        // u8g2.drawGlyph( 0, 20, 0x00f7 ); // wifi sign
        u8g2.setFont( u8g2_font_shylock_nbp_tn );
        u8g2.setCursor( 0, 20 );
        u8g2.print( ipaddress.toString() );
        u8g2.setFont( u8g2_font_10x20_tr );
        u8g2.setCursor( 0, 50 );
        u8g2.print( "PM 2.5" );
        u8g2.setFont( u8g2_font_logisoso54_tr );
        ( data.PM2dot5 >= 100 ) ? u8g2.setCursor( 0, 120 ): u8g2.setCursor( 24, 120 );
        
        u8g2.print( data.PM2dot5 );
        // u8g2.setFont( u8g2_font_open_iconic_weather_6x_t );
        // u8g2.drawGlyph( 0, 125, 0x0040 ); // cloud
        // u8g2.drawGlyph( 60, 125, 0x0045 ); // sun
        // u8g2.drawGlyph( 100, 125, 0x0043 ); // rain

        // u8g2.setFont( u8g2_font_logisoso16_tf );
        // u8g2.setCursor( 0, 25 );
        // u8g2.print( "PM 1.0 = " );
        // u8g2.print( data.PM1dot0 );
        // u8g2.setCursor( 0, 50 );
        // u8g2.print( "PM 2.5 = " );
        // u8g2.print( data.PM2dot5 );
        // u8g2.setCursor( 0, 75 );
        // u8g2.print( "PM 10 = " );
        // u8g2.print( data.PM10dot0 );
        // u8g2.setCursor( 0, 100 );
        // u8g2.print( ipaddress );
        u8g2.sendBuffer();
    }
    else
    {
        u8g2.clear();
    }

}

void Oled::SetIPAddress( IPAddress ip )
{
    ipaddress = ip;
}

void Oled::SetEnabled( bool val )
{
    isEnabled = val;
}