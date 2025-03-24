#ifndef HTML_CLASSES_H_
#define HTML_CLASSES_H_

#include <supla/network/html_element.h>
#include <supla/network/web_sender.h>
#include <supla/storage/config.h>
#include <supla/storage/storage.h>
#include <string.h>

const char *required(bool isRequired) {
  return isRequired ? "required " : "";
}

const char *displayed(bool isDisplayed) {
  return isDisplayed ? "block\">" : "none\">";
}

#include "html/przycisk_update.h"
#include "html/readonly.h"
#include "html/readonly1.h"

#endif
