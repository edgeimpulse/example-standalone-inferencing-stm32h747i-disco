/*
 * Copyright (c) 2023 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an "AS
 * IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
 
#include "uart.h"
#include "stm32h7xx_hal.h"

UART_HandleTypeDef huart1;

static uint8_t rx_buffer[256];
static uint8_t rx_idx;

int uart_print(char* msg, uint16_t len)
{
    HAL_UART_Transmit(&huart1,(uint8_t *)msg, len, 5000);
    
    return 0;
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void USART1_UART_Init(void)
{

    /* USER CODE BEGIN USART1_Init 0 */

    /* USER CODE END USART1_Init 0 */

    /* USER CODE BEGIN USART1_Init 1 */

    /* USER CODE END USART1_Init 1 */
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
    huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    if (HAL_UART_Init(&huart1) != HAL_OK) {
        while(1) {};
    }
    if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
    {
        while(1) {};
    }
    
    if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK) {
        while(1) {};
    }
    
    if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK) {
        while(1) {};
    }

    rx_idx = 0;

}

/**
 *
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    uint8_t rx_byte;
    if (huart->Instance == USART1) {
        HAL_UART_Receive_IT(&huart1, &rx_byte, 1);
        rx_buffer[rx_idx++] = rx_byte;
    }
}
