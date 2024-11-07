// STM32L432KC_RCC.c
// Source code for RCC functions

#include "STM32L432KC_RCC.h"

void configurePLL() {
       // Set clock to 80 MHz
   // Output freq = (src_clk) * (N/M) / P
   // (4 MHz) * (80/2) * 2  = 80 MHz
   // M:, N:, P:
   // Use HSI as PLLSRC

    // Set clock to 80 MHz
    // Output freq = (src_clk) * (N/M) / R
    // (4 MHz) * (40/1) / 2 = 80 MHz
    // M: 1, N: 40, R: 4
    // Use MSI as PLLSRC

    // Turn off PLL
    RCC->CR &= ~(1 << 24);

    // Wait till PLL is unlocked (e.g., off)
    while ((RCC->CR >> 25 & 1) != 0);

    // Load configuration
    // Set PLL SRC to MSI
    RCC->PLLCFGR |= (1 << 0);
    RCC->PLLCFGR &= ~(1 << 1);

    // Set PLLN to 0010100
    RCC->PLLCFGR &= ~(0b11111111 << 8);
    RCC->PLLCFGR |=  (0b0101000 << 8);

    // Set PLLM to 000
    RCC->PLLCFGR &= ~(0b111 << 4);

    // Set PLLR to 00
    RCC->PLLCFGR &= ~(0b1 << 26);
    // RCC->PLLCFGR &= ~(0b1 << 25);
    RCC->PLLCFGR |= (0b1 << 25);

    // Enable PLLR output
    RCC->PLLCFGR |= (1 << 24);

    // Enable PLL
    RCC->CR |= (1 << 24);

    // Wait until PLL is locked
    while ((RCC->CR >> 25 & 1) != 1);
}

void configureClock(){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));
}