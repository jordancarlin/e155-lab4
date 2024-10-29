// lab4_jc.c
// Jordan Carlin, jcarlin@hmc.edu
// October 2024
// Fur Elise, E155 Lab 4

#include "../lib/STM32L432KC_TIM.h"
#include "FUR_ELISE.h"
#include "TWINKLE.h"
//#include "../lib/STM32L432KC_RCC.c"

int main(void) {
  configureClock();
  // Play Fur Elise
  int numNotesFurElise = sizeof(furElise)/sizeof(furElise[0]);
  int i = 0;
  while (furElise[i][1] != 0) {
    PWM(furElise[i][0]);
    delay_millis(furElise[i][1]);
    i++;
  }

  // Pause
  PWM(0);
  delay_millis(1000);

  // Play Twinkle Twinkle Little Star
  i = 0;
  while (twinkle[i][1] != 0) {
    PWM(twinkle[i][0]);
    delay_millis(twinkle[i][1]);
    i++;
  }

  PWM(0);
}
