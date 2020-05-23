// Lesson-16
// Interrupts Part-1

#include <stdint.h>
#include "tm4c_cmsis.h"
#include "bsp.h"

#define SYS_CLOCK_HZ 16000000U

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

int main(){
  // Initialising relevant hardware
  SYSCTL->RCGC2 |= (1U << 5);     // Enable clock for GPIO Portf
  SYSCTL->GPIOHSCTL |= (1U << 5); // Enable AHB bus for faster operation
  GPIO_HS->DIR |= (LED_RED | LED_BLUE | LED_GREEN);
  GPIO_HS->DEN |= (LED_RED | LED_BLUE | LED_GREEN);
  
  // Light up Blue LED
  // GPIO_HS->DATA_Bits[LED_BLUE] = LED_BLUE;
  
  SysTick->LOAD = SYS_CLOCK_HZ/2U - 1U;
  SysTick->VAL  = 0U;
  SysTick->CTRL = (1U << 2) | (1U << 1) | 1U ;
  
  // Blink Red LED  
  while(1) {
    delay(500000);
  }
  
  //return 0;
}
