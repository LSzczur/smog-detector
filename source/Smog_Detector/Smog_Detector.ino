#include <Arduino.h>
#include <SPI.h>
#include <pms.h>
#include <U8g2lib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "FS.h"

const char* ssid = "Wyspa Szczura";
const char* password = "hejpiast";
String page = "";
String text = "";

const auto n = Pmsx003::Reserved;
auto lastRead = millis();
Pmsx003::pmsData data[n];

ESP8266WebServer server(80);   //instantiate server at port 80 (http port)
Pmsx003 pms(/* RX=*/ 4, /* TX=*/ 5);
U8G2_SSD1327_MIDAS_128X128_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 16, /* cs=*/ 12, /* dc=*/ 13);

////////////////////////////////////////

////////////////////////////////////////

void initWiFi()
{
  WiFi.begin(ssid, password); //begin WiFi connection
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/data.txt", []() {
    text = (String)data[Pmsx003::PM2dot5];
    server.send(200, "text/html", text);
  });
  server.on("/", []() {
    page = "<h1>Sensor to Node MCU Web Server</h1><h1>Data:</h1> <h1 id=\"data\">""</h1>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 1000);\r\n";
    page += "function loadData(url, callback){\r\n";
    page += "var xhttp = new XMLHttpRequest();\r\n";
    page += "xhttp.onreadystatechange = function(){\r\n";
    page += " if(this.readyState == 4 && this.status == 200){\r\n";
    page += " callback.apply(xhttp);\r\n";
    page += " }\r\n";
    page += "};\r\n";
    page += "xhttp.open(\"GET\", url, true);\r\n";
    page += "xhttp.send();\r\n";
    page += "}\r\n";
    page += "function updateData(){\r\n";
    page += " document.getElementById(\"data\").innerHTML = this.responseText;\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    server.send(200, "text/html", page);
  });

  server.begin();
  Serial.println("Web server started!");
}

void updateDisplay()
{
//  static bool toogle = true;
//  u8g2.setPowerSave(toogle);
//  toogle = !toogle;

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

  //    u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
  //    u8g2.drawFrame(5,5,120,120);
  //    u8g2.drawGlyph(5, 0, 0x00);
  //    u8g2.drawGlyph(35, 0, 0x01);
  //    u8g2.drawGlyph(65, 0, 0x02);
  //    u8g2.drawGlyph(5, 30, 0x03);
  //    u8g2.drawGlyph(35, 30, 0x05);
  //    u8g2.drawGlyph(65, 30, 0x06);
  //    u8g2.drawGlyph(5, 60, 0x07);
  //    u8g2.drawGlyph(35, 60, 0x08);
  //    u8g2.drawGlyph(65, 60, 0x09);

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

void setup(void)
{
  // Wait for connection
  delay(10000);
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

  // Start WiFi
  Serial.println("Start WiFi");
  initWiFi();

  // Start SPIFFS
  Serial.println("Start SPIFFS");
  SPIFFS.begin();
  File f = SPIFFS.open("/test.txt", "r");
  if (f)
  {
    Serial.println("File open success");
  }
  else
  {
    Serial.println("File open failed");
  }

  f.println();
}

void loop(void)
{
  Pmsx003::PmsStatus status = updateData();
  if (Pmsx003::OK == status)
  {
    updateDisplay();
  }
  server.handleClient();
}

