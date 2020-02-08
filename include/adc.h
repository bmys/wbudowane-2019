#ifndef _ADC_H
#define _ADC_H

#include "display.h"
#include "led.h"
#include "utils.h"
#include <stdlib.h>
#include <stm32f3xx_ll_adc.h>
#include <stm32f3xx_ll_exti.h>
#include <stm32f3xx_ll_gpio.h>
#include <stm32f3xx_ll_rcc.h>

#define ENABLE_TEMPERATURE_INPUT_GPIO LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA)
#define TEMPERATURE_PORT GPIOC
#define TEMPERATURE_PIN LL_GPIO_PIN_2
#define SUPPLY_VOLTAGE 3.0f
#define ADC_RESOLUTION 4095
#define EXEMPLARY_RESISTOR 2000.0f
#define SAMPLES_NUMBER 500
#define ADC_RESOLUTION_F (float)ADC_RESOLUTION

#define CALCULATE_ADC_VOLTAGE(ADC_VALUE) SUPPLY_VOLTAGE * (ADC_VALUE / ADC_RESOLUTION_F)
#define CALCULATE_ADC_PERCENTAGE(ADC_VALUE) (ADC_VALUE / ADC_RESOLUTION_F) * 100.0f
#define CALCULATE_TERMISTOR_RESISTANCE(ADC_VALUE) EXEMPLARY_RESISTOR / (ADC_RESOLUTION_F / (float)ADC_VALUE - 1.0f)

#define TEMP_SENSOR KTY_81_210

#ifdef TEMP_SENSOR
    #if TEMP_SENSOR == KTY_81_210
        static inline float calculateTemperature(float R){
            return -154.8932968777756 + 
            0.11127343542824086 * pow(R, 1)  
            -5.61920123411026e-06 * pow(R, 2) 
            -3.844955939593453e-09 * pow(R, 3) + 
            6.89403940508061e-13  * pow(R, 4);
        }
    #endif
#else
    #error TEMPERATURE SENSOR NOT DEFINIED
#endif

extern short ADC_AVG_VALUE;
void adcInit();
void analogInputInit();
void startConversion();
void printADC();

#endif