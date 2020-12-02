#include <TinyGPS++.h>
#include <Adafruit_NeoPixel.h>

#define PIN           15
#define NUMPIXELS     1

static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;
#define RXD2 38
#define TXD2 39
// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(115200);
  Serial2.begin(GPSBaud, SERIAL_8N1, RXD2, TXD2);

  Serial.println(F("DeviceExample.ino"));
  Serial.println(F("A simple demonstration of TinyGPS++ with an attached GPS module"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setPixelColor(0, pixels.Color(50,50,50));
  pixels.show();
  delay(800);
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();
  delay(200);
  pixels.setPixelColor(0, pixels.Color(125,0,0));
  pixels.show();
  delay(200);
}

void loop()
{
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial2.available() > 0)
    if (gps.encode(Serial2.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
}

void displayInfo()
{
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    pixels.setPixelColor(0, pixels.Color(0,50,0));
    pixels.show();
    delay(100);
  }
  else
  {
    Serial.print(F("INVALID"));
    pixels.setPixelColor(0, pixels.Color(0,0,50));
    pixels.show();
    delay(100);
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();
  delay(200);
  Serial.println();
}
