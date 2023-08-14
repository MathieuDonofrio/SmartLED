#include "core/sinric.h"

#include "SinricPro.h"
#include "SinricProLight.h"

#include "config.h"
#include "core/strip.h"

namespace smartled::sinric
{
int global_brightness = 100;
bool power_state = false;

uint8_t Brightness255() noexcept
{
  return map(global_brightness, 0, 100, 0, 255);
}

namespace handlers
{
  bool onPowerState(const String&, bool& state) noexcept
  {
    power_state = state;
    strip::SetBrightness(power_state ? Brightness255() : 0);
    strip::Show();
    return true;
  }

  bool onBrightness(const String&, int& brightness) noexcept
  {
    global_brightness = brightness;
    strip::SetBrightness(Brightness255());
    strip::Show();
    return true;
  }

  bool onAdjustBrightness(const String&, int brightness_delta) noexcept
  {
    global_brightness += brightness_delta;
    strip::SetBrightness(Brightness255());
    strip::Show();
    return true;
  }

  bool onColor(const String&, byte& r, byte& g, byte& b) noexcept
  {
    strip::color = Color(r, g, b);
    strip::Show();
    return true;
  }
} // namespace handlers

void Initialize() noexcept
{
  SinricProLight& light = SinricPro[LightID];

  light.onPowerState(handlers::onPowerState);
  light.onBrightness(handlers::onBrightness);
  light.onAdjustBrightness(handlers::onAdjustBrightness);
  light.onColor(handlers::onColor);

  SinricPro.onConnected([]() { Serial.printf("Connected to SinricPro\r\n"); });
  SinricPro.onDisconnected([]() { Serial.printf("Disconnected from SinricPro\r\n"); });

  SinricPro.begin(AppKey, AppSecret);
}

void Handle() noexcept
{
  SinricPro.handle();
}

bool IsPowerOn() noexcept
{
  return power_state;
}
} // namespace smartled::sinric