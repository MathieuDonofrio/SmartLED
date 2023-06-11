#include <Arduino.h>

#include "led_strip.h"

using namespace ledshow;

void setup() {
  Serial.begin(115200);

  strip::Initialize();
}

void loop() {

}
