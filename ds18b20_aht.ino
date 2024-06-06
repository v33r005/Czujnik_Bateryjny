#define STATUS_LED_GPIO 2
#define BUTTON_CFG_RELAY_GPIO 0
#define DS1_PIN 12

#include <SuplaDevice.h>
#include <supla/network/esp_wifi.h>
#include <supla/control/button.h>
#include <supla/device/status_led.h>
#include <supla/storage/littlefs_config.h>
#include <supla/network/esp_web_server.h>
#include <supla/network/html/device_info.h>
#include <supla/network/html/protocol_parameters.h>
#include <supla/network/html/wifi_parameters.h>
#include <supla/device/supla_ca_cert.h>
#include <supla/events.h>
#include <supla/sensor/DS18B20.h>
#include <supla/sensor/AHT.h>
#include <supla/device/notifications.h>
#include <supla/time.h>
#include <supla/network/html/custom_parameter.h>

const char PARAM1[] = "param1";
const char PARAM2[] = "param2";
int Usypianie;
int Bateryjka;
unsigned long wifimilis = 0;
byte wifimilis1 = 0;
byte polaczenie_z_serwerem;
byte bateria=0;
unsigned long migotkamillis = 0;
unsigned long czas_bezczynności = 0;
byte migotka = 0;
byte czas = 0;
Supla::ESPWifi wifi;
Supla::LittleFsConfig configSupla;
bool wyslij_wiadomosc = LOW;

Supla::EspWebServer suplaServer;

Supla::Html::DeviceInfo htmlDeviceInfo(&SuplaDevice);
Supla::Html::WifiParameters htmlWifi;
Supla::Html::ProtocolParameters htmlProto;
Supla::Sensor::AHT *tempwilg = nullptr;  
Supla::Sensor::DS18B20 *temperatura = nullptr;

class myElement : public Supla::Element {
 public: myElement(int pin) : pin(pin) {}
  
  void onInit() override {

  }
  
  double getValue() {
    value = (map(analogRead(pin), 450,785,0,100));
    return value;
  }

  void iterateAlways() override {
    if (millis() - lastReadTime > 2000) {
      lastReadTime = millis();
      tempwilg->getChannel()->setBatteryLevel(getValue());
      temperatura->getChannel()->setBatteryLevel(getValue());
    }
  }
 protected:
  int pin;
  double value;
  uint64_t lastReadTime = 0;
};
myElement *c_analog = nullptr;
void status_func(int status, const char *msg) {     //    ------------------------ Status polaczednia z serwerem--------------------------
 polaczenie_z_serwerem = status;                                       
}

void setup() { 

  Serial.begin(115200);
  pinMode(STATUS_LED_GPIO, OUTPUT);
  tempwilg = new Supla::Sensor::AHT();
  c_analog = new myElement(A0);
  Supla::Notification::RegisterNotification(-1);  // notifications for device
  temperatura = new Supla::Sensor::DS18B20(DS1_PIN);

  temperatura->getChannel()->setValidityTimeSec(65*60);
  tempwilg->getChannel()->setValidityTimeSec(65*60);
  temperatura->getChannel()->setFlag(SUPLA_CHANNEL_FLAG_CHANNELSTATE);
  tempwilg->getChannel()->setFlag(SUPLA_CHANNEL_FLAG_CHANNELSTATE);
  tempwilg->getChannel()->setFlag(SUPLA_CHANNELSTATE_FIELD_BATTERYPOWERED);
  tempwilg->getChannel()->setFlag(SUPLA_CHANNELSTATE_FIELD_BATTERYLEVEL);
  temperatura->getChannel()->setFlag(SUPLA_CHANNELSTATE_FIELD_BATTERYPOWERED);
  temperatura->getChannel()->setFlag(SUPLA_CHANNELSTATE_FIELD_BATTERYLEVEL);

  auto buttonCfgRelay = new Supla::Control::Button(BUTTON_CFG_RELAY_GPIO, true, true);
  buttonCfgRelay->configureAsConfigButton(&SuplaDevice);
  SuplaDevice.setStatusFuncImpl(&status_func);
  SuplaDevice.setSuplaCACert(suplaCACert);
  SuplaDevice.setSupla3rdPartyCACert(supla3rdCACert);

  new Supla::Html::CustomParameter(PARAM1, "Device Sleep [min]", 60);
  new Supla::Html::CustomParameter(PARAM2, "Battery Level Notification", 20);

  SuplaDevice.setName("Supla Czujniczek");

  SuplaDevice.addFlags(SUPLA_DEVICE_FLAG_SLEEP_MODE_ENABLED);
  SuplaDevice.begin();
}

void loop() {
  if (Supla::Storage::ConfigInstance()->getInt32(PARAM1, &Usypianie)) {
    //SUPLA_LOG_DEBUG(" **** Param[%s]: %d", PARAM2, LEDS);
  } else {
    //SUPLA_LOG_DEBUG(" **** Param[%s] is not set", PARAM2);
  }
  if (Supla::Storage::ConfigInstance()->getInt32(PARAM2, &Bateryjka)) {
    //SUPLA_LOG_DEBUG(" **** Param[%s]: %d", PARAM2, LEDS);
  } else {
    //SUPLA_LOG_DEBUG(" **** Param[%s] is not set", PARAM2);
  }
  
  SuplaDevice.iterate();

  if (Usypianie > 60){
    Usypianie = 60;
    Supla::Storage::ConfigInstance()->setInt32(PARAM1, 60);
  }
  if (Bateryjka > 99){
    Bateryjka = 99;
    Supla::Storage::ConfigInstance()->setInt32(PARAM2, 99);

  }
  
  if ((polaczenie_z_serwerem != 40)&&(polaczenie_z_serwerem != 17)){
    if (czas == 0){
      czas_bezczynności = (millis()+120000);
      czas=1;
    }
    if (czas == 1){
      if (millis() > czas_bezczynności){
        czas = 2;
      }
    }
    if (czas == 2){
      if ((migotka == 0)&&(millis() > migotkamillis)){
        digitalWrite(STATUS_LED_GPIO, LOW);
        migotkamillis = millis()+200;
        migotka = 1;
      }
      if ((migotka == 1)&&(millis() > migotkamillis)){
        digitalWrite(STATUS_LED_GPIO, HIGH);
        migotkamillis = millis()+200;
        migotka = 2;
      }
      if ((migotka == 2)&&(millis() > migotkamillis)){
        digitalWrite(STATUS_LED_GPIO, LOW);
        migotkamillis = millis()+200;
        migotka = 3;
      }
      if ((migotka == 3)&&(millis() > migotkamillis)){
        digitalWrite(STATUS_LED_GPIO, HIGH);
        migotkamillis = millis()+1000;
        migotka = 0;
      }
    }
  }
  if ((polaczenie_z_serwerem != 40)&&((czas == 0)||(czas == 1))){
    digitalWrite(STATUS_LED_GPIO, HIGH);
  }
  if (polaczenie_z_serwerem == 40){
    czas = 0;
    if ((migotka == 0)&&(millis() > migotkamillis)){
      digitalWrite(STATUS_LED_GPIO, LOW);
      migotkamillis = millis()+100;
      migotka = 1;
    }
    if ((migotka == 1)&&(millis() > migotkamillis)){
      digitalWrite(STATUS_LED_GPIO, HIGH);
      migotkamillis = millis()+100;
      migotka = 0;
    }
  }
  if (polaczenie_z_serwerem == 17) {
    czas = 0;
    if (wyslij_wiadomosc == LOW) {
          if (c_analog->getValue() < Bateryjka){
            Supla::Notification::Send(-1, "Battery", "Low battery, plaese change, or charge");
            wyslij_wiadomosc = HIGH;
          }
      }
    if (wifimilis1 == 0) {
      if (millis() > wifimilis){
        wifimilis = (millis() + 10000);
        wifimilis1 = 1;
        czas = 0;
      }
    }
    if (wifimilis1 == 1){    
      if ((wifimilis - millis())<1000){
        Serial.println("ide spac");
        ESP.deepSleep((Usypianie*60)*1e6);
      }
    }
  }   
}
  
 