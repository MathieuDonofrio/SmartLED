#include <Arduino.h>

#include "drivers/strip.h"
#include "drivers/sinric.h"
#include "drivers/wifi.h"

using namespace smartled; 

void setup() {
  Serial.begin(BaudRate); 
  Serial.setDebugOutput(true);
  Serial.println();

  strip::Initialize();

  Serial.println("LED Strip initialized.");

  Serial.println("Connecting to WiFi network");

  if(!wifi::IsConnected())
  {
    wifi::Connect();

    while (!wifi::IsConnected())
    {
      delay(500);
    }
  }

  Serial.println("Connected to WiFi network.");

  Serial.println("Connecting to SinricPro");

  sinric::Connect();

  while (!sinric::IsConnected())
  {
    sinric::Handle();
    delay(500);
  }

  Serial.println("Connected to SinricPro.");

  Serial.println("Ready.");
}

void loop() {
  for(;;)
  {
    sinric::Handle();

    if (sinric::IsPowerOn())
    {
      strip::SetBrightness(sinric::GetBrightness());

      Color color = sinric::GetColor();

      std::fill(strip::leds.begin(), strip::leds.end(), color);
    }
    else
    {
      strip::SetBrightness(0);
    }

    strip::Show();

    delay(100);
  }
}
