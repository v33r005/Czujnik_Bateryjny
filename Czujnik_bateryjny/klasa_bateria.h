#ifndef KLASA_BATERIA_H_
#define KLASA_BATERIA_H_

class myElement : public Supla::Element {
 public: explicit myElement(int pin, int gorna, int dolna) : pin(pin),
                                                             gorna(gorna), 
                                                             dolna(dolna) 
                                                             {

                                                             }
  
  void onInit() override {
    
  }
  
  double getValue() {
    value = (map(analogRead(pin), dolna, gorna,0,100));
    return value;
  }

  double getRawValue() {
    value = analogRead(pin);
    return value;
  }

  void iterateAlways() override {
    if (millis() - lastReadTime > 2000) {
      lastReadTime = millis();
        czujnik_AHT->getChannel()->setBatteryLevel(getValue());
    }
  }
 protected:
  int pin;
  int dolna;
  int gorna;
  double value;
  uint64_t lastReadTime = 0;
};
myElement *c_analog = nullptr;

#endif