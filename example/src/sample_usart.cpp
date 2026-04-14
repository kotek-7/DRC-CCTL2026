#include "main.h"
#include <cstring>

extern "C" void setup(void) {
  static const char banner[] = "USART3 echo\r\n";
  HAL_UART_Transmit(&huart3, reinterpret_cast<const uint8_t*>(banner), sizeof(banner) - 1U,
                    HAL_MAX_DELAY);
}

extern "C" void loop(void) {
  uint8_t ch = 0;
  if (HAL_UART_Receive(&huart3, &ch, 1, 10) == HAL_OK) {
    HAL_UART_Transmit(&huart3, &ch, 1, HAL_MAX_DELAY);
  }
}
