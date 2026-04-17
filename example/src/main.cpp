#include "main.h"

extern "C" {
extern FDCAN_HandleTypeDef hfdcan1;
extern FDCAN_HandleTypeDef hfdcan2;
extern FDCAN_HandleTypeDef hfdcan3;
extern I2C_HandleTypeDef hi2c2;
extern I2C_HandleTypeDef hi2c3;
extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart3;
extern PCD_HandleTypeDef hpcd_USB_FS;
}

/*
 * 使いたいサンプルを 1 つだけ include する。
 */
#include "sample_lcd.cpp"
