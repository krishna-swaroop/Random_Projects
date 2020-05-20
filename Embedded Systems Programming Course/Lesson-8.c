// Lesson-8
// This deals with explaining how functions work and tracking how registers change instruction by innstruction.
// It also introduces the concept of a stack in C. And discusses various characteristics of the stack implementation 
// in ARM processors.


#include "lm4f120h5qr.h"

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)

void delay(void);

void delay(void){
	int volatile counter;
	counter=0;
	while(counter[0] < 100000){ //delay loop
		++ counter;
	}
	
}


int main() {
	  SYSCTL_RCGCGPIO_R |= (1U << 5);  // Setting Bit 5 of register RCGCGPIO to 1. Enable clock for GPIOF
	  SYSCTL_GPIOHBCTL_R |= (1U << 5); // Enabling the faster AHB bus for GPIOF.
	  GPIOF_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1,2,3 as outputs
	  GPIOF_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
	  
	  // GPIO_PORTF_AHB_DATA_R = LED_BLUE;
	  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
	  while(1){
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;

		delay();
		
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
		
		delay();
	  } 
	  return 0;
 }
