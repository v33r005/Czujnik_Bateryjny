#ifndef HTML_H_
#define HTML_H_

  new Supla::Html::DeviceInfo(&SuplaDevice);
  new Supla::Html::WifiParameters;
  new Supla::Html::ProtocolParameters;
  new Supla::Html::DivEnd();
  new Supla::Html::DivBegin("box");
  new Supla::Html::H3Tag("Kalibracja poziomu napięcia baterii");
  new Supla::Html::ReadOnly;
  new Supla::Html::CustomParameter(PARAM5, "Górna wartość napięcia", 770);
  new Supla::Html::CustomParameter(PARAM6, "Dolna wartość napięcia", 470);
  new Supla::Html::ReadOnly1;
  new Supla::Html::DivEnd();
  new Supla::Html::DivBegin("box");
  new Supla::Html::H3Tag("Ustawienia urządzenia");
  new Supla::Html::CustomTextParameter(DEV_NAME, "Nazwa urządzenia", 30);
  new Supla::Html::CustomParameter(PARAM1, "Czas Usypiania [min]", 30);
  new Supla::Html::CustomParameter(PARAM2, "Minimalny próg baterii [%]", 20);
  new Supla::Html::CustomTextParameter(PARAM4, "Komunikat o niskim poziomie baterii", 200);
  auto selectCmd = new Supla::Html::SelectCmdInputParameter(PARAM_CMD1, "Reset do ustawień fabrycznych");
  selectCmd->registerCmd("RESET", Supla::ON_EVENT_1);
  selectCmd->addAction(Supla::RESET_TO_FACTORY_SETTINGS, SuplaDevice, Supla::ON_EVENT_1, true);
  new::Supla::Html::UpdateParameter;

#endif