#ifndef READONLY_H_
#define READONLY_H_

namespace Supla {
namespace Html {

class ReadOnly : public Supla::HtmlElement {
 public:
  ReadOnly() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    sender->send("<div class=\"form-field\">");
    sender->sendLabelFor("read_only", "Odczyt pinu analogowego");
    sender->send("<input type=\"text\" readonly");
    sender->sendNameAndId("read_only");
    sender->send("placeholder=\"");
    if (c_analog != nullptr){
    sender->send(c_analog->getRawValue());
    } 
    sender->send("\">");
    sender->send("</div>");
  }

  bool handleResponse(const char* key, const char* value) {
    return false;
  }
  
  void onProcessingEnd() {}

 protected:

}; // ReadOnly

}; // namespace Html
}; // namespace Supla

#endif
