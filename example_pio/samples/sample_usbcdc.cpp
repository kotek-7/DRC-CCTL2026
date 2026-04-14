#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Serial.println("USB CDC echo");
}

void loop() {
  while (Serial.available() > 0) {
    Serial.write(Serial.read());
  }
}
