#include "drivers/sinric.h"

#include "SinricPro.h"
#include "SinricProLight.h"

#include "config.h"
#include "utility/color.h"

namespace smartled::sinric
{
bool connected = false;
bool power_state = false;
int brightness = 100;
Color color = Color::White;

namespace handlers
{
  void onConnected() noexcept
  {
    connected = true;
  }

  void onDisconnected() noexcept
  {
    connected = false;
  }

  bool onPowerState(const String&, bool& new_power_state) noexcept
  {
    power_state = new_power_state;
    return true;
  }

  bool onBrightness(const String&, int& new_brightness) noexcept
  {
    brightness = new_brightness;
    return true;
  }

  bool onAdjustBrightness(const String&, int brightness_delta) noexcept
  {
    brightness += brightness_delta;
    return true;
  }

  bool onColor(const String&, byte& r, byte& g, byte& b) noexcept
  {
    color = Color(r, g, b);
    return true;
  }
} // namespace handlers

void Connect() noexcept
{
  SinricProLight& light = SinricPro[LightID];

  SinricPro.onConnected(handlers::onConnected);
  SinricPro.onDisconnected(handlers::onDisconnected);

  light.onPowerState(handlers::onPowerState);
  light.onBrightness(handlers::onBrightness);
  light.onAdjustBrightness(handlers::onAdjustBrightness);
  light.onColor(handlers::onColor);

  SinricPro.restoreDeviceStates(true);

  SinricPro.begin(AppKey, AppSecret);
}

void Handle() noexcept
{
  SinricPro.handle();
}

bool IsConnected() noexcept
{
  return connected;
}

bool IsPowerOn() noexcept
{
  return power_state;
}

uint8_t GetBrightness() noexcept
{
  return map(brightness, 0, 100, 0, 255);
}

Color GetColor() noexcept
{
  return color;
}

} // namespace smartled::sinric