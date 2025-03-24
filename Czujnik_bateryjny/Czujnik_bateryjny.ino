#include "definicje.h"
#include "biblioteki.h"
#include "zmienne.h"

#include "klasa_bateria.h"

void status_func(int status, const char *msg) {     //    ------------------------ Status polaczednia z serwerem--------------------------
 polaczenie_z_serwerem = status;                                       
}
#include "html_classes.h"

void setup() { 

  Serial.begin(115200);
  #include "storage_init.h"
  pinMode(STATUS_LED_GPIO, OUTPUT);
  c_analog = new myElement(A0, Gorna_Wartosc, Dolna_Wartosc);

    czujnik_AHT = new Supla::Sensor::AHT();
    czujnik_AHT->getChannel()->setValidityTimeSec(65*60);
    czujnik_AHT->getChannel()->setFlag(SUPLA_CHANNEL_FLAG_CHANNELSTATE);
    czujnik_AHT->getChannel()->setFlag(SUPLA_CHANNELSTATE_FIELD_BATTERYPOWERED);
    czujnik_AHT->getChannel()->setFlag(SUPLA_CHANNELSTATE_FIELD_BATTERYLEVEL);

  Supla::Notification::RegisterNotification(-1);  // notifications for device

  auto buttonCfgRelay = new Supla::Control::Button(BUTTON_CFG_RELAY_GPIO, true, true);
  buttonCfgRelay->configureAsConfigButton(&SuplaDevice);
  SuplaDevice.setStatusFuncImpl(&status_func);

  #include "html.h"

  httpUpdater.setup(suplaServer.getServerPtr(), "/update");
  SuplaDevice.setSuplaCACert(suplaCACert);
  SuplaDevice.setSupla3rdPartyCACert(supla3rdCACert);
  SuplaDevice.addFlags(SUPLA_DEVICE_FLAG_SLEEP_MODE_ENABLED);
  SuplaDevice.setName(devName);
  SuplaDevice.begin();
}

void loop() {
  
  
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
        lastTime = millis();
          if (c_analog->getValue() < Bateryjka){
            Supla::Notification::Send(-1, "Battery", komunikat);
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
