#include <Arduino.h>
#include <SPI.h>
#include <pms.h>
#include <U8g2lib.h>

Pmsx003 pms(/* RX=*/ 4, /* TX=*/ 5);
U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 16, /* cs=*/ 12, /* dc=*/ 13);

////////////////////////////////////////

void setup(void)
{
  // Set debug serial
  Serial.begin(115200);
  while (!Serial) {};

  // Set OLED display
  Serial.println("Set OLED");
  SPI.begin();
  u8g2.begin();

  // Attach an interrupt to button
  //Serial.println("Try to attach an interrupt");
  //attachInterrupt(digitalPinToInterrupt(9), updateDisplay, RISING);

  // Set dust sensor
  Serial.println("Set Pmsx003");
  pms.begin();
  pms.waitForData(Pmsx003::wakeupTime);
  pms.write(Pmsx003::cmdModeActive);

}

////////////////////////////////////////

const auto n = Pmsx003::Reserved;

auto lastRead = millis();
Pmsx003::pmsData data[n];

void updateDisplay()
{
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_logisoso16_tf);
  u8g2.setCursor(0, 35);
  u8g2.print("PM1.0 = ");
  u8g2.print(data[Pmsx003::PM1dot0]);
  u8g2.setCursor(0, 70);
  u8g2.print("PM2.5 = ");
  u8g2.print(data[Pmsx003::PM2dot5]);
  u8g2.setCursor(0, 105);
  u8g2.print("PM10 = ");
  u8g2.print(data[Pmsx003::PM10dot0]);

  //  u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
  //  u8g2.drawFrame(4,4,120,120);
  //  u8g2.drawGlyph(5, 0, 0x00);
  //  u8g2.drawGlyph(35, 0, 0x01);
  //  u8g2.drawGlyph(65, 0, 0x02);
  //  u8g2.drawGlyph(5, 30, 0x03);
  //  u8g2.drawGlyph(35, 30, 0x05);
  //  u8g2.drawGlyph(65, 30, 0x06);
  //  u8g2.drawGlyph(5, 60, 0x07);
  //  u8g2.drawGlyph(35, 60, 0x08);
  //  u8g2.drawGlyph(65, 60, 0x09);
  
  u8g2.sendBuffer();
}

Pmsx003::PmsStatus updateData()
{
  Pmsx003::PmsStatus status = pms.read(data, n);

  switch (status) {
    case Pmsx003::OK:
      {
        Serial.println("_________________");
        auto newRead = millis();
        Serial.print("Wait time ");
        Serial.println(newRead - lastRead);
        lastRead = newRead;

        // For loop starts from 3
        // Skip the first three data (PM1dot0CF1, PM2dot5CF1, PM10CF1)
        for (size_t i = Pmsx003::PM1dot0; i < n; ++i) {
          Serial.print(data[i]);
          Serial.print("\t");
          Serial.print(Pmsx003::dataNames[i]);
          Serial.print(" [");
          Serial.print(Pmsx003::metrics[i]);
          Serial.print("]");
          Serial.println();
        }
        break;
      }
    case Pmsx003::noData:
      break;
    default:
      Serial.println("_________________");
      Serial.println(Pmsx003::errorMsg[status]);
  }

  return status;
}

void loop(void)
{
  updateData();
  updateDisplay();

  delay(1000);
}

