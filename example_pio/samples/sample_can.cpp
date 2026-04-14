#include <Arduino.h>
#include <stm32g4xx_hal.h>

#include "board_init.h"

namespace {
FDCAN_HandleTypeDef Hfdcan1 = {};

void initFdcan1() {
  Hfdcan1.Instance = FDCAN1;
  Hfdcan1.Init.ClockDivider = FDCAN_CLOCK_DIV1;
  Hfdcan1.Init.FrameFormat = FDCAN_FRAME_CLASSIC;
  Hfdcan1.Init.Mode = FDCAN_MODE_NORMAL;
  Hfdcan1.Init.AutoRetransmission = DISABLE;
  Hfdcan1.Init.TransmitPause = DISABLE;
  Hfdcan1.Init.ProtocolException = DISABLE;
  Hfdcan1.Init.NominalPrescaler = 16;
  Hfdcan1.Init.NominalSyncJumpWidth = 1;
  Hfdcan1.Init.NominalTimeSeg1 = 1;
  Hfdcan1.Init.NominalTimeSeg2 = 1;
  Hfdcan1.Init.DataPrescaler = 1;
  Hfdcan1.Init.DataSyncJumpWidth = 1;
  Hfdcan1.Init.DataTimeSeg1 = 1;
  Hfdcan1.Init.DataTimeSeg2 = 1;
  Hfdcan1.Init.StdFiltersNbr = 1;
  Hfdcan1.Init.ExtFiltersNbr = 0;
  Hfdcan1.Init.TxFifoQueueMode = FDCAN_TX_FIFO_OPERATION;

  if (HAL_FDCAN_Init(&Hfdcan1) != HAL_OK) {
    Error_Handler();
  }

  FDCAN_FilterTypeDef filter = {};
  filter.IdType = FDCAN_STANDARD_ID;
  filter.FilterIndex = 0;
  filter.FilterType = FDCAN_FILTER_MASK;
  filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
  filter.FilterID1 = 0x000;
  filter.FilterID2 = 0x000;
  if (HAL_FDCAN_ConfigFilter(&Hfdcan1, &filter) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_FDCAN_ConfigGlobalFilter(&Hfdcan1,
                                   FDCAN_ACCEPT_IN_RX_FIFO0,
                                   FDCAN_ACCEPT_IN_RX_FIFO0,
                                   FDCAN_REJECT_REMOTE,
                                   FDCAN_REJECT_REMOTE) != HAL_OK) {
    Error_Handler();
  }

  if (HAL_FDCAN_Start(&Hfdcan1) != HAL_OK) {
    Error_Handler();
  }
}

void forwardMessage(const FDCAN_RxHeaderTypeDef &rx_header, const uint8_t *rx_data) {
  FDCAN_TxHeaderTypeDef tx_header = {};
  tx_header.Identifier = rx_header.Identifier;
  tx_header.IdType = rx_header.IdType;
  tx_header.TxFrameType = rx_header.RxFrameType;
  tx_header.DataLength = rx_header.DataLength;
  tx_header.ErrorStateIndicator = FDCAN_ESI_ACTIVE;
  tx_header.BitRateSwitch = FDCAN_BRS_OFF;
  tx_header.FDFormat = FDCAN_CLASSIC_CAN;
  tx_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
  tx_header.MessageMarker = 0;

  if (HAL_FDCAN_AddMessageToTxFifoQ(&Hfdcan1, &tx_header, const_cast<uint8_t *>(rx_data)) !=
      HAL_OK) {
    Error_Handler();
  }
}
} // namespace

extern "C" void HAL_FDCAN_MspInit(FDCAN_HandleTypeDef *hfdcan) {
  if (hfdcan->Instance != FDCAN1) {
    return;
  }

  RCC_PeriphCLKInitTypeDef periph_clk = {};
  GPIO_InitTypeDef gpio = {};

  periph_clk.PeriphClockSelection = RCC_PERIPHCLK_FDCAN;
  periph_clk.FdcanClockSelection = RCC_FDCANCLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&periph_clk) != HAL_OK) {
    Error_Handler();
  }

  __HAL_RCC_FDCAN_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  gpio.Pin = GPIO_PIN_8 | GPIO_PIN_9;
  gpio.Mode = GPIO_MODE_AF_PP;
  gpio.Pull = GPIO_NOPULL;
  gpio.Speed = GPIO_SPEED_FREQ_LOW;
  gpio.Alternate = GPIO_AF9_FDCAN1;
  HAL_GPIO_Init(GPIOB, &gpio);
}

void setup() {
  initFdcan1();
}

void loop() {
  if (HAL_FDCAN_GetRxFifoFillLevel(&Hfdcan1, FDCAN_RX_FIFO0) == 0) {
    return;
  }

  FDCAN_RxHeaderTypeDef rx_header = {};
  uint8_t rx_data[8] = {};
  if (HAL_FDCAN_GetRxMessage(&Hfdcan1, FDCAN_RX_FIFO0, &rx_header, rx_data) != HAL_OK) {
    Error_Handler();
  }

  forwardMessage(rx_header, rx_data);
}
