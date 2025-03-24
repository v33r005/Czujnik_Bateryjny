#ifndef ZMIENNE_H_
#define ZMIENNE_H_

const char DEV_NAME[] = "dev_name";
char devName[30] = {};
const char PARAM1[] = "param1";
const char PARAM2[] = "param2";
const char PARAM3[] = "param3";
const char PARAM4[] = "param4";
const char PARAM5[] = "param5";
const char PARAM6[] = "param6";
char komunikat[200]= {};
int Usypianie;
int Bateryjka;
int Gorna_Wartosc = 770;
int Dolna_Wartosc = 470;
unsigned long wifimilis = 0;
int wifimilis1 = 0;
int polaczenie_z_serwerem;
int bateria=0;
unsigned long migotkamillis = 0;
unsigned long czas_bezczynności = 0;
static uint32_t lastTime = 0;
int migotka = 0;
int czas = 0;
bool wyslij_wiadomosc = LOW;
const char SELECT_MODE[] = "select_mode";
uint32_t selectMode = 0;
const char SELECT_MODE_1[] = "select_mode_1";
uint32_t selectMode_1 = 0;
const char PARAM_CMD1[] = "cmd1";

#endif