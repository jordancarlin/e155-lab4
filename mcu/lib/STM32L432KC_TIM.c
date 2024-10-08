// STM32L432KC_TIM.c
// Source code for Timer functions

#include "STM32L432KC_TIM.h"

void initTIM(TIM_TypeDef * TIMx) {
    // Set up clocks
    RCC->APB2ENR |= (1 << 16);
    // Set prescale
    TIMx->PSC |= 80000-1; // Divides by n + 1. 80 MHz/80000 = 1 kHz
    // activate one-pulse mode (disable timer after overflow)
    TIMx->CR1 |= (0b1 << 3);
    // set auto-reload preload
    TIMx->CR1 |= (0b1 << 7);
    // set UG bit to initialize/update registers
    TIMx->EGR |= (0b1 << 0 );
}

void initTIM_PWM(TIM_TypeDef * TIMx) {
    // Set up clocks
    RCC->APB1ENR1 |= (1 << 0); // Enable clock to timer
    RCC->AHB2ENR |= (1 << 1); // Enable clock to GPIOB
    // Maybe need to set SMS to 0000, but should be reset value
    // Set prescale
    TIMx->PSC |= 799; // Divides by n + 1. 80 MHz/800 = 100 kHz
    // Set output channel 2 to PWM mode 1
    TIMx->CCMR1 |= (0b110 << 12);
    // Enable output compare 2 preload
    TIMx->CCMR1 |= (0b1 << 11);
    // set auto-reload preload
    TIMx->CR1 |= (0b1 << 7);
    // set UG bit to initialize/update registers
    TIMx->EGR |= (0b1 << 0 );
    // enable counter
    TIMx->CR1 |= (0b1 << 0);
    // Enable capture/compare output pin
    TIMx->CCER |= (0b1 << 4);
    // Enable GPIO B3 pin to altmode
    pinMode(3, GPIO_ALT);
    GPIO->AFRL |= (0b0001 << 12);
}

void set_TIM_PWM_freq(TIM_TypeDef * TIMx, uint32_t desiredFreq){
    if (desiredFreq == 0){
        TIMx->CR1 &= ~(0b1 << 0);
        pinMode(3, GPIO_OUTPUT);
        digitalWrite(3, 0);
    } else {
        // if (((GPIO->MODER >> 6 )& 0b11) != 0b01){
            initTIM_PWM(TIMx);
        // }
        // Pulse width modulation mode allows you to generate a signal with
        //  a frequency determined by the value of the TIMx_ARR register and
        //  a duty cycle determined by the value of the TIMx_CCRx register.
        uint32_t freq = 100000/desiredFreq - 1; // 100 kHz / desired frequency = counter
        TIMx->ARR = freq;
        TIMx->CCR1 |= freq/2; // 50% Duty Cycle
        TIMx->CCR2 |= freq/2;
        // set UG bit to initialize/update registers
        TIMx->EGR |= (0b1 << 0 );
    }
}

void PWM(uint32_t desiredFreq){
    set_TIM_PWM_freq(TIM2, desiredFreq);
}

void TIM_delay_millis(TIM_TypeDef * TIMx, uint32_t ms){
    if (((TIMx->CR1 >> 3) & 1) != 1){
        initTIM(TIMx);
    }
    TIMx->CR1 |= 0b1; // Enable counter
    TIMx->ARR = ms;
    while (!(TIMx->SR & 1)); // the actual delay
    TIMx->SR &= ~(0b0); // clear update flag
}

void delay_millis(uint32_t ms){
    TIM_delay_millis(TIM15, ms);
}
