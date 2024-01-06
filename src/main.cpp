#include <Arduino.h>


#include "drivers/sinric.h"
#include "drivers/strip.h"
#include "drivers/wifi.h"
#include "effect/effect.h"

using namespace smartled;

void setup()
{
  Serial.begin(BaudRate);
  Serial.setDebugOutput(true);
  Serial.println();

  strip::Initialize();

  Serial.println("LED Strip initialized.");

  // Serial.println("Connecting to WiFi network");

  // if(!wifi::IsConnected())
  // {
  //   wifi::Connect();

  //   while (!wifi::IsConnected())
  //   {
  //     delay(500);
  //   }
  // }

  // Serial.println("Connected to WiFi network.");

  // Serial.println("Connecting to SinricPro");

  // sinric::Connect();

  // while (!sinric::IsConnected())
  // {
  //   sinric::Handle();
  //   delay(500);
  // }

  // Serial.println("Connected to SinricPro.");

  Serial.println("Ready.");
}

ShowGenerator ShowRainbow() noexcept 
{
  using namespace std::chrono_literals;

  // 1D rainbow

  auto t = time_ms();

  for (auto i = 0; i < strip::size; i++)
  {
    uint8_t hue = ((i * 255 / strip::size) + t.count() / 100) % 255;

    CHSV hsv = CHSV(hue, 255, 255);

    strip::leds[i] = hsv;
  }

  co_yield 10ms;
}

ShowGenerator Show(CRGB color) noexcept 
{
  using namespace std::chrono_literals;
  
  // 1D perlin noise

  auto t = time_ms();

  for (auto i = 0; i < strip::size; i++)
  {
    auto n = triwave8(((i * 8) + t.count() / 100) % 255);

    strip::leds[i] = blend(color, CRGB::Black, n);
  }
  
  co_yield 10ms;
}

void loop() 
{
  for (auto delay : ShowRainbow())
  {
    FastLED.show();
    FastLED.delay(delay.count());
  }

  // strip::SetBrightness(255);

  // for(auto sleep : lava_flow.Show(Color(0, 0, 0)))
  // {
  //   FastLED.show();
  //   FastLED.delay(sleep.count());

  //   delay(sleep.count());
  // }
}

// void loop()
// {
//   for (;;)
//   {
//     sinric::Handle();

//     if (sinric::IsPowerOn())
//     {
//       strip::SetBrightness(sinric::GetBrightness());

//       Color color = sinric::GetColor();

//       std::fill(strip::leds.begin(), strip::leds.end(), color);
//     }
//     else
//     {
//       strip::SetBrightness(0);
//     }

//     strip::Show();

//     delay(100);
//   }
// }
