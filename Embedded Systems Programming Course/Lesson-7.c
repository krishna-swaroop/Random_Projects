#include "lm4f120h5qr.h"  // Header file given by TI to define all the macros required to address individual registers

#define LED_RED   (1U << 1)
#define LED_BLUE  (1U << 2)
#define LED_GREEN (1U << 3)
#define GPIO_PORTF_DATA_BITS_R ((volatile unsigned long *)0x40025000)

/*
	// This is the faster Interupt Save Implementation on the APB Bus.
	The APB Bus is a legacy bus in this board to ensure backwards compatibility.
	int main() {
	  SYSCTL_RCGCGPIO_R |= (1U << 5);  // Setting Bit 5 of register RCGCGPIO to 1. Enable clock for GPIOF
	  GPIOF_PORTF_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1,2,3 as outputs
	  GPIOF_PORTF_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
	  
	  GPIO_PORTF_DATA_R = LED_BLUE;
	  GPIO_PORTF_DATA_BITS_R[LED_BLUE] = LED_BLUE;
	  while(1){
		// GPIO_PORTF_DATA_R  |= LED_RED; // This is the de facto standard for setting a bit. Helps to avoid bugs in bigger projects.
		// The following 3 implementations are equivalent and generate the same machine codes.
		// They change the L-C-S cycle to Movs-STR cycle to ensure proper interrupt handling.
		// *((unsigned long volatile *)(0x40025000) + (LED_RED << 2))) = LED_RED
		// *(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;
		GPIO_PORTF_DATA_BITS_R[LED_RED] = LED_RED;
		
		int volatile counter[2] = {0,0}; // Changed to explain pointer arithmetic.
		while(counter[0] < 100000){ //delay loop
		++ counter[0];
		}
		counter = 0;
		// GPIO_PORTF_DATA_R  &= ~LED_RED;  // This notation is the de facto standard for clearing a bit
		GPIO_PORTF_DATA_BITS_R[LED_RED] = 0;
		while((counter+1) < 100000){ // delay loop
		++ counter[1];
		}
	  } 
	  return 0;
	 }
	 
	 // Setting Pins this way changes the Load-Change-Store cycle to Movs-STR cycle 
	 // This change is done to ensure correct data is used in case an interrupt occurs
	 // in the middle of a L-C-S cycle.
 
 */
 // The following is an implementation on the much faster AHB bus.
 int main() {
	  SYSCTL_RCGCGPIO_R |= (1U << 5);  // Setting Bit 5 of register RCGCGPIO to 1. Enable clock for GPIOF
	  SYSCTL_GPIOHBCTL_R |= (1U << 5); // Enabling the faster AHB bus for GPIOF.
	  GPIOF_PORTF_AHB_DIR_R |= (LED_RED | LED_BLUE | LED_GREEN); // set pins 1,2,3 as outputs
	  GPIOF_PORTF_AHB_DEN_R |= (LED_RED | LED_BLUE | LED_GREEN);
	  
	  // GPIO_PORTF_AHB_DATA_R = LED_BLUE;
	  GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
	  while(1){
		// GPIO_PORTF_DATA_R  |= LED_RED; // This is the de facto standard for setting a bit. Helps to avoid bugs in bigger projects.
		// The following 3 implementations are equivalent and generate the same machine codes.
		// They change the L-C-S cycle to Movs-STR cycle to ensure proper interrupt handling.
		// *((unsigned long volatile *)(0x40025000) + (LED_RED << 2))) = LED_RED
		// *(GPIO_PORTF_DATA_BITS_R + LED_RED) = LED_RED;
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
		
		int volatile counter[2] = {0,0}; // Changed to explain pointer arithmetic.
		while(counter[0] < 100000){ //delay loop
		++ counter[0];
		}
		counter = 0;
		// GPIO_PORTF_DATA_R  &= ~LED_RED;  // This notation is the de facto standard for clearing a bit
		GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = 0;
		while((counter+1) < 100000){ // delay loop
		++ counter[1];
		}
	  } 
	  return 0;
 }
 
 