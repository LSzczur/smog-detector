#include <Arduino.h>
#include <SPI.h>
#include <pms.h>
#include <U8g2lib.h>

Pmsx003 pms(D3, D4);
U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* cs=*/ 10, /* dc=*/ 9, /* reset=*/ 8);

////////////////////////////////////////

void setup(void) {
  Serial.println("Set OLED");
  u8g2.begin();
  
  u8g2.userInterfaceSelectionList("Set up", 1, "Serial\nPMS7003");
	Serial.begin(115200);
	while (!Serial) {};

  Serial.println("Try to attach an interrupt");
  attachInterrupt(digitalPinToInterrupt(9), updateDisplay, RISING);

  u8g2.userInterfaceSelectionList("Set up", 2, "Serial\nPMS7003");
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
  u8g2.clearDisplay();
  u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
  u8g2.drawFrame(4,4,120,120);
  u8g2.drawGlyph(5, 0, 0x00);
  u8g2.drawGlyph(35, 0, 0x01);
  u8g2.drawGlyph(65, 0, 0x02);
  u8g2.drawGlyph(5, 30, 0x03);
  u8g2.drawGlyph(35, 30, 0x05);
  u8g2.drawGlyph(65, 30, 0x06);
  u8g2.drawGlyph(5, 60, 0x07);
  u8g2.drawGlyph(35, 60, 0x08);
  u8g2.drawGlyph(65, 60, 0x09); 
}

void drawMenu()
{
//  u8g2.clearDisplay();
//  u8g2.setFont(u8g2_font_6x10_tf);
//  u8g2.setFontRefHeightAll();    /* this will add some extra space for the text inside the buttons */
//  u8g2.userInterfaceMessage("Wait for", "PMS7003 setup", "aaa", " Ok \n Cancel ");
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
  drawMenu();
  updateData();
}

