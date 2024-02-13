/*
 * Copyright (c) 2024 EdgeImpulse Inc.
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
#include <string.h>
#include "ei_run_classifier.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

static const float features[] = {
    // copy raw features here (for example from the 'Live classification' page)
0.0900, -7.2700, 1.1500, 0.0900, -7.2700, 1.1500, 0.1500, -8.3100, 0.4000, 0.2500, -9.3800, 0.1400, 1.0700, -10.8600, 0.4100, 1.2800, -11.9900, 0.4600, -0.1800, -12.9600, -0.1800, -2.2100, -13.9100, -1.2300, -2.2100, -13.9100, -1.2300, -5.0800, -15.5300, -2.5000, -8.1900, -17.6200, -2.8000, -9.1600, -19.0100, -2.3000, -6.9000, -19.1800, -0.5000, -4.6700, -18.3200, 0.3200, -4.3200, -16.8300, 0.6900, -4.3200, -16.8300, 0.6900, -5.0600, -15.4700, 1.0200, -5.2300, -14.1000, 2.7200, -5.3400, -11.7900, 4.1200, -5.1000, -8.7100, 5.1500, -4.2400, -4.2700, 6.0200, -1.7800, 0.7100, 6.6700, -1.7800, 0.7100, 6.6700, 1.9100, 6.2100, 6.1300, 6.4500, 7.8900, 7.7000, 9.1500, 7.6200, 9.6000, 9.6000, 10.9000, 7.4100, 10.2700, 15.6600, 3.5300, 13.4500, 18.9200, 1.1500, 13.4500, 18.9200, 1.1500, 16.6600, 18.2000, 1.2800, 17.2400, 18.4400, 1.4300, 18.6300, 19.9500, 0.6100, 19.9300, 19.9700, 0.6600, 19.9600, 19.6700, 2.8000, 19.9200, 15.9700, 5.5100, 17.9200, 13.0700, 6.1400, 17.9200, 13.0700, 6.1400, 16.3400, 11.3400, 6.8700, 16.7600, 9.6800, 8.6400, 15.0800, 8.2600, 10.0000, 10.1000, 7.2800, 8.6200, 5.7300, 5.2400, 7.3900, 3.0300, 3.2200, 6.4500, 3.0300, 3.2200, 6.4500, 1.9300, 1.1300, 6.1500, 0.1100, -0.0800, 4.5300, -1.1600, -1.0600, 1.8500, -1.9000, -2.5200, -0.2600, -3.1900, -4.4700, -1.8800, -4.7100, -6.2100, -3.4600, -4.7100, -6.2100, -3.4600, -5.8400, -8.1900, -4.4700, -6.5500, -10.8400, -4.3900, -7.5200, -13.9100, -3.5200, -8.3100, -17.1300, -2.5500, -8.6800, -18.8500, -2.9400, -8.3900, -18.6800, -3.4700, -8.3900, -18.6800, -3.4700, -7.7200, -17.7400, -3.9000, -6.9600, -16.8100, -3.4200, -6.4700, -16.6800, -2.2000, -8.0400, -16.1300, -0.7200, -9.7600, -14.8400, 0.2600, -8.9100, -11.2400, 1.5800, -8.9100, -11.2400, 1.5800, -5.7100, -6.1500, 4.0400, -2.1800, -1.6600, 6.1900, 1.2500, 2.8000, 7.2900, 3.0800, 5.0000, 7.7600, 3.7800, 6.1600, 9.0100, 4.9900, 9.4300, 8.5600, 4.9900, 9.4300, 8.5600, 8.2000, 15.0100, 6.2400, 14.6400, 18.1400, 4.2800, 15.3300, 13.2200, 6.6200, 9.5500, 9.6000, 6.1400, 7.4800, 14.9400, 3.1400, 14.6600, 19.8900, 2.0800, 14.6600, 19.8900, 2.0800, 19.9600, 19.9700, 5.0600, 19.9600, 19.2300, 8.1800, 18.6700, 17.2700, 6.6500, 14.6500, 16.1300, 5.0600, 13.9700, 14.5600, 5.7600, 14.9600, 12.4600, 8.0500, 14.9600, 12.4600, 8.0500, 15.1100, 10.6200, 9.6200, 13.7000, 8.8000, 10.1000, 11.9400, 8.0400, 9.8400, 8.8500, 7.3500, 9.0300, 6.7700, 6.9900, 7.7400, 4.4900, 6.0100, 7.3800, 4.4900, 6.0100, 7.3800, 0.5300, 3.1900, 5.6300, -0.9600, 0.5400, 4.5800, -1.2200, -1.5400, 2.5700, -0.9200, -2.7500, 1.2200, -1.9300, -3.2600, -0.8300, -5.8000, -2.9600, -3.7600, -5.8000, -2.9600, -3.7600, -11.6100, -3.9400, -6.9100, -12.1300, -8.4600, -7.3300, -8.6800, -12.7600, -2.9300, -6.0000, -15.2600, -1.4900, -6.5000, -16.5700, -2.3300, -9.5700, -16.0000, -3.9900, -12.2400, -16.4700, -5.4500, -12.2400, -16.4700, -5.4500, -12.3200, -18.1800, -3.5300, -9.6900, -18.0500, -2.4900, -6.5600, -16.4900, -1.0900, -4.5400, -14.1400, -0.4900, -3.8300, -11.4700, 0.2200, -4.3100, -8.9800, 1.4100, -4.3100, -8.9800, 1.4100, -4.4400, -7.2200, 2.5500, -1.9000, -4.4700, 4.8200, 1.6400, 0.0000, 6.3600, 4.7100, 3.9100, 6.1200, 7.0500, 5.8700, 5.3300, 7.2000, 5.3600, 5.4800, 7.2000, 5.3600, 5.4800, 6.9200, 7.2900, 4.5900, 8.3100, 10.2800, 3.9200
};

int raw_feature_get_data(size_t offset, size_t length, float *out_ptr)
{
  memcpy(out_ptr, features + offset, length * sizeof(float));
  return 0;
}

int ei_main(void)
{        
    ei_impulse_result_t result = {nullptr};

    while (true) {
        ei_printf("Edge Impulse standalone inferencing (STM32H747I-DISCO)\n");

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
