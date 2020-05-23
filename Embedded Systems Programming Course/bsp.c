/* Board Support Package */
#include "tm4c_cmsis.h"
#include "bsp.h"


__stackless void assert_failed (char const *file, int line){
  /*TBD: damage control */
  NVIC_SystemReset(); /* Reset the system */
}

void SysTick_Handler(void){
  GPIO_HS->DATA_Bits[LED_RED] ^= LED_RED;
}
