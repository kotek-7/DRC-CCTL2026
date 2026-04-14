#include "main.h"

namespace {
void playTone(uint32_t frequency_hz, uint32_t duration_ms) {
  const uint32_t timer_clock_hz = HAL_RCC_GetPCLK1Freq();
  const uint32_t period = (timer_clock_hz / frequency_hz) - 1U;

  __HAL_TIM_SET_AUTORELOAD(&htim2, period);
  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, (period + 1U) / 2U);

  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_Delay(duration_ms);
  HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}
}

extern "C" void setup(void) {
  playTone(988, 80);
  HAL_Delay(10);
  playTone(1319, 120);
}

extern "C" void loop(void) {}
