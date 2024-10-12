#include <LittleFS.h>

uint32_t Workspace[10000] PSRAM;
const int len = 1000;

// automatically chose Serial as Serial1 (hardware UART) if NO_USB is on
#ifdef PIO_FRAMEWORK_ARDUINO_NO_USB
#define Serial Serial1
#endif

bool checkdata () {
  for (int i=0; i<len; i++) if (Workspace[i] != i) return false;
  return true;
}

void savedata () {
  for (int i=0; i<len; i++) Workspace[i] = i;
  if (checkdata()) Serial.println("Data setup OK");
  LittleFS.begin();
  File file;
  file = LittleFS.open("/DATA.DAT", "w");
  file.close();
}

void setup() {
  Serial.begin(9600);
  delay(3000); // give serial monitor time to open
  Serial.println("Firmware begin");
}

void loop() {
  savedata();
  Serial.println("Saved");
  if (!checkdata()) Serial.println("Data error");
  delay(5000);
}