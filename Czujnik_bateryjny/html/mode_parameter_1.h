#ifndef MODE_PARAMETER_1_H_
#define MODE_PARAMETER_1_H_

namespace Supla {
namespace Html {

class ModeParameter_1 : public Supla::HtmlElement {
 public:
  ModeParameter_1() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg) {
      uint32_t value = 0; // default value
      uint32_t value1 = 0; // default value
      cfg->getUInt32(SELECT_MODE_1, &value);
      

      // form-field BEGIN
      sender->send("<div class=\"form-field\">");
      sender->sendLabelFor(SELECT_MODE_1, "Czujnik AHT10");
      sender->send("<select");
      sender->sendNameAndId(SELECT_MODE_1);
      sender->send("onchange=\"modeToggle();\">");
      sender->send("<option value=\"0\"");
      sender->send(selected(value == 0));
      sender->send(">Brak Czujnika</option>");
      sender->send("<option value=\"1\"");
      sender->send(selected(value == 1));
      sender->send(">Włącz czujnik AHT10</option>");
      sender->send("</select>");
      sender->send("</div>");
      // form-field END
      

    }
      
  }
  bool handleResponse(const char* key, const char* value) {
    auto cfg = Supla::Storage::ConfigInstance();
    if (cfg && strcmp(key, SELECT_MODE_1) == 0) {
      int inFormValue = stringToUInt(value);
      cfg->setUInt32(SELECT_MODE_1, inFormValue);
      selectMode_1 = inFormValue;
      return true;
    }
    return false;    
  }
  
 protected:
  

}; // ModeParameter

}; // namespace Html
}; // namespace Supla

#endif