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
 
#include "ei_main.h"
#include "uart.h"
#include <string.h>
#include "ei_run_classifier.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

static const float features[] = {
    // copy raw features here (for example from the 'Live classification' page)
0.0300, 0.0000, 10.0900, 0.0300, 0.0000, 10.0900, 0.0300, 0.0000, 10.0900, 0.0300, 0.0000, 10.1000, 0.0200, 0.0000, 10.0900, 0.0300, 0.0000, 10.1000, 0.0200, 0.0200, 10.1000, 0.0400, 0.0000, 10.0900, 0.0400, 0.0000, 10.0900, 0.0300, 0.0000, 10.0900, 0.0300, 0.0000, 10.1000, 0.0200, 0.0000, 10.0900, 0.0400, 0.0000, 10.1000, 0.0300, 0.0000, 10.1100, 0.0300, 0.0000, 10.1100, 0.0300, 0.0000, 10.1000, 0.0200, 0.0000, 10.1000, 0.0300, 0.0000, 10.1000, 0.0400, 0.0000, 10.1000, 0.0500, 0.0000, 10.1000, 0.0500, 0.0300, 10.1200, 0.0500, 0.0300, 10.1200, 1.0700, 0.6800, 10.1400, 0.7900, 1.0600, 10.1500, 0.6100, 0.9400, 10.0800, 0.8500, 1.1600, 10.0700, 0.5600, 1.2000, 10.0700, 0.2800, 0.8900, 10.0600, 0.2800, 0.8900, 10.0600, 0.1000, 0.9300, 10.1900, 0.4500, 1.4000, 9.9000, 0.9800, 1.2200, 9.5600, 0.6900, 0.2200, 9.1300, 0.6000, -0.0700, 10.0300, 1.0900, 0.2300, 9.8400, 1.0900, 0.2300, 9.8400, 1.1200, -0.8700, 10.0500, 0.3500, -3.0400, 9.3000, 0.4200, -3.5700, 9.1100, 0.1600, -2.7100, 6.9900, 0.4800, -2.3000, 9.2200, 0.5300, -1.7200, 9.6600, 0.5300, -1.7200, 9.6600, 0.8200, -1.3500, 9.8700, 0.8600, -1.1100, 9.9800, 0.7200, -1.1700, 9.9600, 0.5900, -1.2600, 9.3100, 0.3100, -1.3400, 10.1100, 0.3500, -1.2000, 10.2200, 0.3500, -1.2000, 10.2200, 0.3100, -0.6500, 9.5800, 0.6800, -0.4200, 8.1300, 1.2600, -0.3600, 9.7000, 1.2600, -0.2900, 9.5600, 1.5700, -0.3700, 8.5900, 2.0300, 0.2100, 9.5900, 2.0300, 0.2100, 9.5900, 1.9700, 1.2000, 9.6700, 2.3800, 2.2300, 8.7700, 2.4200, 3.0000, 8.1200, 1.7200, 3.4900, 8.6600, 1.2000, 2.7200, 7.5400, 0.0500, 1.2200, 6.0000, 0.0500, 1.2200, 6.0000, -1.3200, 0.9900, 7.9800, -1.5100, 1.9600, 5.3700, 1.6200, 2.9700, 7.5300, 0.5500, 3.6900, 8.6500, -0.2100, 3.0100, 10.0400, -0.2100, 3.0100, 10.0400, -0.0300, 2.2400, 8.0300, -0.5800, 2.0300, 8.3300, -0.9200, 1.8000, 7.8200, -1.5900, 1.1200, 9.5300, -0.9200, 0.8500, 8.9500, -1.0200, 0.6800, 10.1600, -1.0200, 0.6800, 10.1600, -1.1000, 0.8100, 8.5200, -0.1500, 0.8200, 9.3600, 0.0400, 0.3700, 9.5000, -0.0600, -0.3100, 9.5500, -0.2500, -1.3600, 6.6500, -0.7800, -2.5100, 10.3300, -0.7800, -2.5100, 10.3300, -1.1200, -2.3500, 9.2800, -1.1200, -1.6600, 9.7400, -0.0600, -1.1100, 9.9600, 0.5800, -1.1200, 9.9500, 0.1900, -1.9000, 9.8000, -0.0100, -1.2000, 9.4900, -0.0100, -1.2000, 9.4900, 0.6500, 0.4700, 10.1800, 0.8300, 0.3700, 9.7800, 1.6700, -1.0300, 9.8200, 0.2900, -2.1200, 10.2800, 0.3700, -2.6300, 9.9900, 1.2000, -1.6000, 10.0400, 1.2000, -1.6000, 10.0400, 0.7300, -1.2000, 10.1600, 1.0600, -1.5300, 9.2400, 1.3600, -1.7700, 10.2800, 0.9400, -1.5000, 7.2100, 1.4700, -0.9100, 7.9600, 0.9800, -0.2900, 8.2500, 0.9800, -0.2900, 8.2500, 1.5600, 0.3300, 8.3700, 1.5900, 0.7100, 6.4100, 1.6300, 1.1100, 8.6900, 1.0300, 1.8100, 8.5800, 1.2300, 2.2200, 7.4900, 0.9200, 2.1200, 8.2300, 0.9200, 2.1200, 8.2300, 1.2200, 2.1800, 7.9800, 1.5000, 2.2600, 8.3200, 1.4700, 2.2700, 6.5800, 0.6800, 2.3700, 6.8500, 0.1900, 2.2100, 8.4100, 0.8600, 1.9700, 8.6700, 0.8600, 1.9700, 8.6700, 0.3000, 2.2100, 8.7300, -0.5800, 1.1500, 9.2800, -0.5900, 0.4200, 8.8800, 0.7500, 1.1400, 9.0000, 2.0400, 2.1600, 8.9800, 2.0400, 2.1600, 8.9800
};

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr)
{
  memcpy(out_ptr, features + offset, length * sizeof(float));
  return 0;
}

int ei_main(void)
{        
    ei_impulse_result_t result = {nullptr};
    USART1_UART_Init();

    while (true) {
        ei_printf("Edge Impulse standalone inferencing (STM32F466RE)\n");

        if (sizeof(features) / sizeof(float) != EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE) {
            ei_printf("The size of your 'features' array is not correct. Expected %d items, but had %u\n",
                    EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE, sizeof(features) / sizeof(float));
            return 1;
        }
        
        ei_printf("Entering the loop!\n");

        while (1) {

            // the features are stored into flash, and we don't want to load everything into RAM
            signal_t features_signal;
            features_signal.total_length = sizeof(features) / sizeof(features[0]);
            features_signal.get_data = &raw_feature_get_data;

            // invoke the impulse
            EI_IMPULSE_ERROR res = run_classifier(&features_signal, &result, true);

            ei_printf("run_classifier returned: %d\n", res);

            if (res != 0) {
                return 1;
            }
                
            ei_printf("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
                    result.timing.dsp, result.timing.classification, result.timing.anomaly);

            // print the predictions
            ei_printf("[");
            for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
                ei_printf("%.5f", result.classification[ix].value);
                #if EI_CLASSIFIER_HAS_ANOMALY == 1
                ei_printf(", ");
                #else
                if (ix != EI_CLASSIFIER_LABEL_COUNT - 1) {
                  ei_printf(", ");
                }
                #endif
            }
            #if EI_CLASSIFIER_HAS_ANOMALY == 1
            ei_printf("%.3f", result.anomaly);
            #endif
            ei_printf("]\n");

            ei_sleep(2000);
        }
    }
}
