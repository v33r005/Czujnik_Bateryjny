#ifndef READONLY1_H_
#define READONLY1_H_

namespace Supla {
namespace Html {

class ReadOnly1 : public Supla::HtmlElement {
 public:
  ReadOnly1() : HtmlElement(HTML_SECTION_FORM) {}

  void send(Supla::WebSender* sender) {
    sender->send("<div class=\"form-field\">");
    sender->sendLabelFor("read_only", "Wartość obliczona w %");
    sender->send("<input type=\"text\" readonly");
    sender->sendNameAndId("read_only");
    sender->send("placeholder=\"");
    if (c_analog != nullptr){
    sender->send(c_analog->getValue());
    sender->send("%");
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
