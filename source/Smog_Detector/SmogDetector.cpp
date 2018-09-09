#include "SmogDetector.hpp"

SmogDetector::SmogDetector() :
    oled(),
    sensor(),
    httpServer()
{
}

SmogDetector::~SmogDetector()
{
}

bool SmogDetector::Initialize()
{
    // Set debug serial
    Serial.begin( 115200 );

    oled.Initialize();
    sensor.Initialize();
    httpServer.Initialize();

    //     // Attach an interrupt to button
    //   //sendDebugMsg("Interrupt");
    //   //attachInterrupt(digitalPinToInterrupt(9), updateDisplay, RISING);

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
    Pmsx003::PmsStatus status = sensor.UpdateData();
    if ( Pmsx003::OK == status )
    {
        oled.UpdateDisplay(sensor.GetDataStructure());
    }
    httpServer.handleClient();
}