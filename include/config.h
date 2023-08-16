#ifndef CONFIG_H
#define CONFIG_H

#include <array>
#include <cstdint>

namespace smartled
{
constexpr const char* WiFiSSID = "BELL130";
constexpr const char* WiFiPass = "2C6DE112FC34";
constexpr const uint8_t* WiFiBSSID = nullptr; // For faster connection

constexpr const char* AppKey = "2b091221-c2a9-41da-86d4-c7376f6cf4ae";
constexpr const char* AppSecret = "d86b6b81-9d21-49bd-b908-687f900cd165-93042aa4-fbe4-4a6d-b407-a3da8c3bb9bb";
constexpr const char* LightID = "64d98e980ef5b4609b0444fa";

constexpr uint32_t BaudRate = 115200;

constexpr uint32_t LedAmount = 16;
constexpr uint8_t DataPin = 3;
} // namespace smartled

#endif