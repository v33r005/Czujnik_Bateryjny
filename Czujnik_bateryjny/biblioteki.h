#ifndef BIBLIOTEKI_H_
#define BIBLIOTEKI_H_

//#include "Wire.h";
#include <SuplaDevice.h>
#include <supla/network/esp_wifi.h>
Supla::ESPWifi wifi;
#include <supla/control/button.h>
#include <supla/device/status_led.h>
#include <supla/storage/littlefs_config.h>
Supla::LittleFsConfig configSupla;
#include <supla/network/esp_web_server.h>
Supla::EspWebServer suplaServer;
#include <supla/network/html/device_info.h>
#include <supla/network/html/protocol_parameters.h>
#include <supla/network/html/status_led_parameters.h>
#include <supla/network/html/wifi_parameters.h>
#include <supla/device/supla_ca_cert.h>
#include <supla/events.h>
#include <supla/sensor/AHT.h>
#include <supla/device/notifications.h>
#include <supla/time.h>
#include <supla/network/html/div.h>
#include <supla/network/html/h3_tag.h>
#include <supla/network/html/custom_parameter.h>
#include <supla/network/html/custom_text_parameter.h>
#include <supla/network/html/custom_checkbox_parameter.h>
#include <supla/network/html/text_cmd_input_parameter.h>
#include <supla/network/html/select_cmd_input_parameter.h>

Supla::Sensor::AHT *czujnik_AHT = nullptr;  

#ifdef ARDUINO_ARCH_ESP32
#include <HTTPUpdateServer.h>
HTTPUpdateServer httpUpdater;
#else
#include <ESP8266HTTPUpdateServer.h>
ESP8266HTTPUpdateServer httpUpdater;
#endif
#include <supla/storage/eeprom.h>
Supla::Eeprom eeprom;



#endif 