#include <Arduino.h>
#include <HardwareSerial.h>

#include "board_init.h"

HardwareSerial SerialUsart3(USART_RX, USART_TX);

void setup() {
  SerialUsart3.begin(115200);
  SerialUsart3.println("USART3 echo");
}

void loop() {
  while (SerialUsart3.available() > 0) {
    SerialUsart3.write(SerialUsart3.read());
  }
}
