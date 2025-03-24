#ifndef STOREGE_INIT_H_
#define STORAGE_INIT_H_

Supla::Storage::Init();
auto cfg = Supla::Storage::ConfigInstance();
  if (Supla::Storage::ConfigInstance()->getString(DEV_NAME, devName, 30)) {
    SUPLA_LOG_DEBUG("# Param[%s]: %s", DEV_NAME, devName);
  } else {
    Supla::Storage::ConfigInstance()->setString(DEV_NAME, "Supla-Czujniczek");
  }
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
  if (Supla::Storage::ConfigInstance()->getInt32(PARAM5, &Gorna_Wartosc)) {
    //SUPLA_LOG_DEBUG(" **** Param[%s]: %d", PARAM2, LEDS);
  } else {
    //SUPLA_LOG_DEBUG(" **** Param[%s] is not set", PARAM2);
  }
  if (Supla::Storage::ConfigInstance()->getInt32(PARAM6, &Dolna_Wartosc)) {
    //SUPLA_LOG_DEBUG(" **** Param[%s]: %d", PARAM2, LEDS);
  } else {
    //SUPLA_LOG_DEBUG(" **** Param[%s] is not set", PARAM2);
  }
  if (Supla::Storage::ConfigInstance()->getString(PARAM4, komunikat, 200)) {
    //SUPLA_LOG_DEBUG(" **** Param[%s]: %s", PARAM1, buf);
  } else {
    Supla::Storage::ConfigInstance()->setString(PARAM4, "Low battery, plaese change, or charge");
  }
  if (cfg->getUInt32(SELECT_MODE, &selectMode)) {
  SUPLA_LOG_DEBUG("# Param[%s]: %d", SELECT_MODE, selectMode);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", SELECT_MODE);
  }
  if (cfg->getUInt32(SELECT_MODE_1, &selectMode_1)) {
  SUPLA_LOG_DEBUG("# Param[%s]: %d", SELECT_MODE_1, selectMode_1);
  } else {
    SUPLA_LOG_DEBUG("# Param[%s] is not set", SELECT_MODE_1);
  }

#endif