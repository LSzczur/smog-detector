#include "Oled.hpp"
#include <SPI.h>

bool Oled::isEnabled = true;

Oled::Oled() :
    u8g2( U8G2_R0, /* clock=*/14, /* data=*/16, /* cs=*/12, /* dc=*/13 ),
    ipaddress(),
    state( PM1dot0 )
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
        u8g2.setFont( u8g2_font_shylock_nbp_tn );
        u8g2.setCursor( 0, 20 );
        u8g2.print( ipaddress.toString() );
        u8g2.setFont( u8g2_font_10x20_tr );
        u8g2.setCursor( 0, 50 );

        switch ( state )
        {
            case PM1dot0:
                u8g2.print( "PM 1.0" );
                u8g2.setFont( u8g2_font_logisoso54_tr );
                ( data.PM1dot0 >= 100 ) ? u8g2.setCursor( 0, 120 ) : u8g2.setCursor( 24, 120 );
                u8g2.print( data.PM1dot0 );
                state = PM2dot5;
                break;
            case PM2dot5:
                u8g2.print( "PM 2.5" );
                u8g2.setFont( u8g2_font_logisoso54_tr );
                ( data.PM2dot5 >= 100 ) ? u8g2.setCursor( 0, 120 ) : u8g2.setCursor( 24, 120 );
                u8g2.print( data.PM2dot5 );
                state = PM10dot0;
                break;
            case PM10dot0:
                u8g2.print( "PM 10" );
                u8g2.setFont( u8g2_font_logisoso54_tr );
                ( data.PM10dot0 >= 100 ) ? u8g2.setCursor( 0, 120 ) : u8g2.setCursor( 24, 120 );
                u8g2.print( data.PM10dot0 );
                state = PM1dot0;
                break;
            default:
                break;
        }
        delay( 1000 );
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