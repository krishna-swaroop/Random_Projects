// Lesson-5

// Explains the role of C pre-processor in ESD
// Discusses volatile qualifier and its role.

// Using #define will ensure the code is more readable while ensuring that the code is as optimal as directly hardcoding memory values

#include "lm4f120h5qr.h"  // Header file given by TI to define all the macros required to address individual registers


// The following macros are defined differently in the header file and are included only to show a setp-wise evolution of the code.

#define RCGCGPIO    (*((unsigned int*)0x400FE608U))          // clock gating control
#define GPIOF_BASE  0x40025000U
#define GPIOF_DIR   (*((unsigned int*)(GPIOF_BASE + 0x400U))
#define GPIOF_DEN   (*((unsigned int*)(GPIOF_BASE + 0x51CU))
#define GPIOF_DATA  (*((unsigned int*)(GPIOF_BASE + 0x3FCU))

// Adding a volatile qualifier to a variable tells the CPU that its value might change even if no system command manipulates it.


int main() {
  RCGCGPIO = 0x20U;  // Setting Bit 5 of register RCGCGPIO to 1. Enable clock for GPIOF
  GPIOF_DIR = 0x0EU; // set pins 1,2,3 as outputs
  GPIOF_DEN = 0x0EU;
  
  while(1){
    GPIOF_DATA  = 0x02U; // Enabling the Red bit in the Register (0010 = 0x02)
    static int counter = 0;
    while(counter < 100000){ //delay loop
    ++ counter;
    }
    counter = 0;
    GPIOF_DATA  = 0x00U;  // Disabling the Red Bit in the register.
    while(counter < 100000){ // delay loop
    ++ counter;
    }
  } 
  return 0;
 }
