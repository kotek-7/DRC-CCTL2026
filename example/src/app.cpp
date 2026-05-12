#include "lcd_aqm1602.h"
#include "main.h"

extern "C" {
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c3;
extern I2C_HandleTypeDef hi2c4;
extern TIM_HandleTypeDef htim15;
extern UART_HandleTypeDef huart3;
extern PCD_HandleTypeDef hpcd_USB_FS;
extern TIM_HandleTypeDef htim2;
}

namespace {
Aqm1602 lcd(&hi2c1);

void playTone(uint32_t frequency_hz, uint32_t duration_ms) {
    const uint32_t period = (1000000U / frequency_hz) - 1U;

    __HAL_TIM_SET_AUTORELOAD(&htim15, period);
    __HAL_TIM_SET_COMPARE(&htim15, TIM_CHANNEL_2, (period + 1U) / 2U);

    HAL_TIM_PWM_Start(&htim15, TIM_CHANNEL_2);
    HAL_Delay(duration_ms);
    HAL_TIM_PWM_Stop(&htim15, TIM_CHANNEL_2);
}

volatile bool lcd_update_requested = false;
volatile bool lcd_visible = true;

void showLcd(bool visible) {
    lcd.clear();
    if (!visible) {
        return;
    }

    lcd.setCursor(0, 0);
    lcd.print("DRC-CCTL2026");
    lcd.setCursor(0, 1);
    lcd.print("LCD Example");
}

void updateLedPattern(uint32_t tick_ms) {
    const auto cycle_ms = tick_ms % 300U;
    const bool led1_on = cycle_ms < 100U || cycle_ms >= 285U;
    const bool led2_on = cycle_ms >= 85U && cycle_ms < 200U;
    const bool led3_on = cycle_ms >= 185U && cycle_ms < 300U;

    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, led1_on ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, led2_on ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, led3_on ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
} // namespace

extern "C" void setup(void) {
    lcd.begin();
    showLcd(true);

    playTone(988, 80);
    playTone(1319, 120);

    HAL_TIM_Base_Start_IT(&htim2);
}

extern "C" void loop(void) {
    bool update_lcd = false;
    bool visible = false;

    __disable_irq();
    if (lcd_update_requested) {
        lcd_update_requested = false;
        update_lcd = true;
        visible = lcd_visible;
    }
    __enable_irq();

    if (update_lcd) {
        showLcd(visible);
    }

    HAL_Delay(1);
}

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM2) {
        static uint32_t tick_ms = 0;

        tick_ms++;
        if (tick_ms % 100U == 0U) {
            updateLedPattern(tick_ms);
        }
        if (tick_ms % 500U == 0U) {
            lcd_visible = !lcd_visible;
            lcd_update_requested = true;
        }
    }
}
