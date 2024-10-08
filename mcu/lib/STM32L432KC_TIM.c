// STM32L432KC_TIM.c
// Source code for Timer functions

#include "STM32L432KC_TIM.h"

void initTIM(TIM_TypeDef * TIMx) {
    // Set up clocks
    RCC->APB2ENR |= (1 << 16);
    // Set prescale
    TIMx->PSC |= (40000-1); // Divides by n + 1. 40 MHz/40000 = 1 kHz
    // set UG bit to initialize/update registers
    TIMx->EGR |= (0b1 << 0 );
    TIMx->CR1 |= 0b1; // Enable counter
}

void initTIM_PWM(TIM_TypeDef * TIMx) {
    // Set up clocks
    RCC->APB1ENR1 |= (1 << 0); // Enable clock to timer
    RCC->AHB2ENR |= (1 << 1); // Enable clock to GPIOB
    // Maybe need to set SMS to 0000, but should be reset value
    // Set prescale
    TIMx->PSC |= 399; // Divides by n + 1. 40 MHz/400 = 100 kHz
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
    uint32_t freq;
    if (desiredFreq == 0){
        freq = 0x8FFFFFFF;
    } else {
        freq = 100000/desiredFreq; // 100 kHz / desired frequency = counter
    }

    if ((TIMx->CR1 & 1) != 1){
        initTIM_PWM(TIMx);
    }

    // Pulse width modulation mode allows you to generate a signal with
    //  a frequency determined by the value of the TIMx_ARR register and
    //  a duty cycle determined by the value of the TIMx_CCRx register.
    TIMx->ARR = freq - 1;
    TIMx->CCR2 = freq/2; // 50% Duty Cycle
    // set UG bit to initialize/update registers
    TIMx->EGR |= (0b1 << 0 );
}

void PWM(uint32_t desiredFreq){
    set_TIM_PWM_freq(TIM2, desiredFreq);
}

void TIM_delay_millis(TIM_TypeDef * TIMx, uint32_t ms){
    if ((TIMx->CR1 & 1) != 1){
        initTIM(TIMx);
    }
    TIMx->ARR = ms;
    TIMx->EGR |= 1; // update registers
    TIMx->SR &= ~(0b1); // clear update flag
    TIMx->CNT = 0;
    while (!(TIMx->SR & 1)); // the actual delay
}

void delay_millis(uint32_t ms){
    TIM_delay_millis(TIM15, ms);
}
