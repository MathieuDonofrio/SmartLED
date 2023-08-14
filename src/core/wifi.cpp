#include "core/wifi.h"

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32) || defined(ARDUINO_ARCH_RP2040)
#include <WiFi.h>
#endif

#include "config.h"

namespace smartled::wifi
{
void Connect() noexcept
{
  Serial.printf("\r\n[Wifi]: Connecting");

  if (WiFi.SSID() == WiFiSSID && WiFi.status() == WL_CONNECTED)
  {
    Serial.printf("\r\n[Wifi]: Already connected!");
    return;
  }

  WiFi.persistent(true);
  WiFi.setAutoConnect(true);
  WiFi.setAutoReconnect(true);

#if defined(ESP8266)
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
#elif defined(ESP32)
  WiFi.setSleep(false);
#endif

  WiFi.begin(WiFiSSID, WiFiPass, 0, WiFiBSSID.data());

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.printf(".");
    delay(500);
  }

  IPAddress localIP = WiFi.localIP();
  Serial.printf("\r\n[Wifi]: Connected!\r\n[WiFi]: IP-Address is %s\r\n", localIP.toString().c_str());
}
} // namespace smartled::wifi