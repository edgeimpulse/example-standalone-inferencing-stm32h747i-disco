/******************************************************************************
 * File Name   : MX_Device.h
 * Date        : 14/02/2024 09:44:44
 * Description : STM32Cube MX parameter definitions
 * Note        : This file is generated by STM32CubeMX (DO NOT EDIT!)
 ******************************************************************************/

#ifndef __MX_DEVICE_H
#define __MX_DEVICE_H

/*---------------------------- Clock Configuration ---------------------------*/

#define MX_LSI_VALUE                            32000
#define MX_LSE_VALUE                            32768
#define MX_HSI_VALUE                            64000000
#define MX_HSE_VALUE                            25000000
#define MX_EXTERNAL_CLOCK_VALUE                 12288000
#define MX_PLLDSIFreq_Value                     500000000
#define MX_SYSCLKFreq_VALUE                     400000000
#define MX_HCLKFreq_Value                       200000000
#define MX_CortexFreq_Value                     400000000
#define MX_APB1Freq_Value                       100000000
#define MX_APB2Freq_Value                       100000000
#define MX_CECFreq_Value                        32000
#define MX_RTCFreq_Value                        32000
#define MX_USBFreq_Value                        400000000
#define MX_WatchDogFreq_Value                   32000
#define MX_DSIFreq_Value                        62500000
#define MX_DSIPHYCLKFreq_Value                  96000000
#define MX_DSITXEscFreq_Value                   15625000
#define MX_SPDIFRXFreq_Value                    400000000
#define MX_MCO1PinFreq_Value                    64000000
#define MX_MCO2PinFreq_Value                    400000000

/*-------------------------------- NVIC1      --------------------------------*/
#define MX_NVIC1                                1

/* GPIO Configuration */

/*-------------------------------- SYS        --------------------------------*/
#define MX_SYS                                  1

/* GPIO Configuration */

/*-------------------------------- CORTEX_M7  --------------------------------*/
#define MX_CORTEX_M7                            1

/* GPIO Configuration */

/*-------------------------------- USART1     --------------------------------*/
#define MX_USART1                               1
#define MX_USART1_VM                            VM_ASYNC

/* GPIO Configuration */

/* Pin PA9 */
#define MX_USART1_TX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART1_TX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART1_TX_Pin                        PA9
#define MX_USART1_TX_GPIOx                      GPIOA
#define MX_USART1_TX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART1_TX_GPIO_Pin                   GPIO_PIN_9
#define MX_USART1_TX_GPIO_AF                    GPIO_AF7_USART1
#define MX_USART1_TX_PinAttribute               CortexM7

/* Pin PA10 */
#define MX_USART1_RX_GPIO_ModeDefaultPP         GPIO_MODE_AF_PP
#define MX_USART1_RX_GPIO_Speed                 GPIO_SPEED_FREQ_LOW
#define MX_USART1_RX_Pin                        PA10
#define MX_USART1_RX_GPIOx                      GPIOA
#define MX_USART1_RX_GPIO_PuPd                  GPIO_NOPULL
#define MX_USART1_RX_GPIO_Pin                   GPIO_PIN_10
#define MX_USART1_RX_GPIO_AF                    GPIO_AF7_USART1
#define MX_USART1_RX_PinAttribute               CortexM7

/*-------------------------------- GPIO       --------------------------------*/
#define MX_GPIO                                 1

/* GPIO Configuration */

#endif  /* __MX_DEVICE_H */

