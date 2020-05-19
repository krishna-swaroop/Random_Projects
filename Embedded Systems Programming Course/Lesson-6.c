// Lesson-6
// This lesson deals with Bitwise Operators in C

// The notations followed for setting and clearing bits can only be used if the register being accessed has RW permissions.
#include "lm4f120h5qr.h"  // Header file given by TI to define all the macros required to address individual registers

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)


int main() {
  SYSCTL_RCGCGPIO_R |= (1U << 5);  // Setting Bit 5 of register RCGCGPIO to 1. Enable clock for GPIOF
  GPIOF_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1,2,3 as outputs
  GPIOF_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
  
  GPIO_PORTF_DATA_R = LED_BLUE;
  while(1){
    GPIO_PORTF_DATA_R  |= LED_RED; // This is the de facto standard for setting a bit. Helps to avoid bugs in bigger projects.
    static int counter = 0;
    while(counter < 100000){ //delay loop
    ++ counter;
    }
    counter = 0;
    GPIO_PORTF_DATA_R  &= ~LED_RED;  // This notation is the de facto standard for clearing a bit
    while(counter < 100000){ // delay loop
    ++ counter;
    }
  } 
  return 0;
 }
