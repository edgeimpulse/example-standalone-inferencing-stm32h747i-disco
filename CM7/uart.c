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
#include "stm32h7xx.h"
#include "stm32h7xx_hal_uart.h"

extern UART_HandleTypeDef huart1;

static uint8_t rx_buffer[256];
static uint8_t rx_idx;

/**
 *
*/
int uart_print(char* msg, uint16_t len)
{
    HAL_UART_Transmit(&huart1,(uint8_t *)msg, len, 5000);
    
    return 0;
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
    
