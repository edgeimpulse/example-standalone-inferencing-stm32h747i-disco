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
