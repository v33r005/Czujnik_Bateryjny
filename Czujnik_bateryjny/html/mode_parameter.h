#ifndef MODE_PARAMETER_H_
#define MODE_PARAMETER_H_

namespace Supla {
namespace Html {

class ModeParameter : public Supla::HtmlElement {
 public:
  ModeParameter() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint32_t value = 0; // default value
      uint32_t value1 = 0; // default value
      cfg->getUInt32(SELECT_MODE, &value);
      

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(SELECT_MODE, "Czujnik 1 Wire (GPIO12)");
      sender->send("<select");
      sender->sendNameAndId(SELECT_MODE);
      sender->send("onchange=\"modeToggle();\">");
      sender->send("<option value=\"0\"");
      sender->send(selected(value == 0));
      sender->send(">Brak Czujnika</option>");
      sender->send("<option value=\"1\"");
      sender->send(selected(value == 1));
      sender->send(">DHT22</option>");
      sender->send("<option value=\"2\"");
      sender->send(selected(value == 2));
      sender->send(">DS18B20</option>");
      sender->send("</select>");
      sender->send("</div>");
      // form-field END
      

    }
      
  }
  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, SELECT_MODE) == 0) {
      int inFormValue = stringToUInt(value);
      cfg->setUInt32(SELECT_MODE, inFormValue);
      selectMode = inFormValue;
      return true;
    }
    return false;    
  }
  
 protected:
  

}; // ModeParameter

}; // namespace Html
}; // namespace Supla

#endif