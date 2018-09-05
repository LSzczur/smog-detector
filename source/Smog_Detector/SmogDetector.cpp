#include "SmogDetector.hpp"
#include <SPI.h>

SmogDetector::SmogDetector() :
    oled()
{
}

SmogDetector::~SmogDetector()
{
}

bool SmogDetector::Initialize()
{
    // Set debug serial
    Serial.begin( 115200 );
    while ( !Serial )
    {
    };

    // oled.Test();

    // Set OLED display
    // Serial.println( "Set OLED" );
    // SPI.begin();
    // u8g2.begin();

    //     // Attach an interrupt to button
    //   //sendDebugMsg("Interrupt");
    //   //attachInterrupt(digitalPinToInterrupt(9), updateDisplay, RISING);

    //   // Set dust sensor
    //   sendDebugMsg("Pms7003");
    // //  // Set pin as output
    // //  pinMode(PMS7003_SET_PIN, OUTPUT);
    // //  // Turn on sensor
    // //  digitalWrite(PMS7003_SET_PIN, LOW);

    //   pms.begin();
    //   pms.waitForData(Pmsx003::wakeupTime);
    //   pms.write(Pmsx003::cmdModeActive);

    //   // Start WiFi
    //   sendDebugMsg("WiFi");
    //   initWiFi();

    //   // Start SPIFFS
    //   sendDebugMsg("SPIFFS");
    //   SPIFFS.begin();
    //   File f = SPIFFS.open("/index.html", "r");
    //   if (f)
    //   {
    //     Serial.println("File open success");
    //   }
    //   else
    //   {
    //     Serial.println("File open failed");
    //   }

    //   while(f.available() > 0)
    //   {
    //     Serial.write(f.read());
    //   }

    //   u8g2.clearBuffer();
    //   u8g2.setFont(u8g2_font_logisoso16_tf);
    //   u8g2.setCursor(0, 35);
    //   u8g2.print("Init OK");
    //   u8g2.sendBuffer();
}

bool SmogDetector::Loop()
{
    Pmsx003::PmsStatus status = sensor.updateData();
    if ( Pmsx003::OK == status )
    {
        oled.updateDisplay();
    }
    //server.handleClient();
}