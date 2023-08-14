#include <Arduino.h>

#include "core/strip.h"
#include "core/sinric.h"
#include "core/wifi.h"

#include "effects/static_color_effect.h"

using namespace smartled;

void setup() {
  Serial.begin(BaudRate);
  strip::Initialize();
  wifi::Connect();
  sinric::Initialize();
}

void loop() {
  sinric::Handle();

  if (sinric::IsPowerOn())
  {
    std::fill(strip::leds.begin(), strip::leds.end(), strip::color);
    strip::Show();
  }

  delay(100);
}

// #include <Arduino.h>

// #include "led_strip.h"
// #include "effects/static_color_effect.h"
// #include "effects/color_wipe_effect.h"
// #include "effects/cylon_effect.h"
// #include "effects/twinkle_effect.h"

// using namespace ledshow;

// StaticColorEffect static_color_effect(Color::White);
// ColorWipeEffect color_wipe_effect(Color::Green, 100ms);
// CylonEffect cylon_effect(Color::Red, 3, 100ms, 500ms);
// TwinkleEffect twinkle_effect(Color::Blue, 8, 150ms);

// void setup() {
//   Serial.begin(115200);

//   strip::Initialize();
// }

// void loop() {
//   twinkle_effect.OnStart();

//   strip::Show();

//   while(true)
//   {
//     for(auto d : twinkle_effect.Show())
//     {
//       strip::Show();
//       delay(d.count());
//     }    
//   }
// }
