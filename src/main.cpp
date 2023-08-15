#include <Arduino.h>

#include "core/strip.h"
#include "core/sinric.h"
#include "core/wifi.h"

#include <variant>

using namespace smartled;

void setup() {
  Serial.begin(BaudRate);

  Serial.println("Starting...");

  Serial.println("Initializing LED Strip...");
  strip::Initialize();
  Serial.println("LED Strip initialized.");

  Serial.print("Connecting to WiFi network");
  if(!wifi::IsConnected())
  {
    wifi::Connect();

    while (!wifi::IsConnected())
    {
      Serial.print(".");
      delay(500);
    }
  }
  Serial.println("");
  Serial.println("Connected to WiFi network.");

  Serial.println("Connecting to SinricPro...");
  sinric::Connect();
  Serial.println("Connected to SinricPro.");

  Serial.println("Ready.");
}

void loop() {
  for(;;)
  {
    sinric::Handle();

    if (sinric::IsPowerOn())
    {
      Color color = sinric::GetColor();

      std::fill(strip::leds.begin(), strip::leds.end(), color);

      strip::Show();
    }

    delay(100);
  }
}
