#include "DustSensor.hpp"

DustSensor::DustSensor() :
    pms( /* RX=*/5, /* TX=*/4 )
{
}

DustSensor::~DustSensor()
{
}

Pmsx003::PmsStatus DustSensor::updateData()
{
    Pmsx003::PmsStatus status = pms.read( data, Pmsx003::Reserved );

    switch ( status )
    {
        case Pmsx003::OK:
        {
            Serial.println( "_________________" );
            auto newRead = millis();
            //Serial.print("Wait time ");
            Serial.println( newRead ); // - lastRead);
            //lastRead = newRead;

            // For loop starts from 3
            // Skip the first three data (PM1dot0CF1, PM2dot5CF1, PM10CF1)
            for ( size_t i = Pmsx003::PM1dot0; i < Pmsx003::Reserved; ++i )
            {
                Serial.print( data[i] );
                Serial.print( "\t" );
                Serial.print( Pmsx003::dataNames[i] );
                Serial.print( " [" );
                Serial.print( Pmsx003::metrics[i] );
                Serial.print( "]" );
                Serial.println();
            }
            break;
        }
        case Pmsx003::noData:
            break;
        default:
            Serial.println( "_________________" );
            Serial.println( Pmsx003::errorMsg[status] );
    }

    return status;
}
