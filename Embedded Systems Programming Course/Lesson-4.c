// Lesson-4

// Link to datasheet of the board being used in the tutorial : http://www.ti.com/lit/ds/spms376e/spms376e.pdf?&ts=1589833054241
// Link to User Manual for the Evaluation Board : https://www.state-machine.com/quickstart/Tiva-C_Launchpad_User_Manual.pdf

// Blinking an LED by addressing registers

/* From Datasheet, we get the following information relevant to this lesson-
   
   Addresses 0x20000000-0x20007FFF are allocated to the Bit-Banded SRAM. This corresponds to 32KB of RAM.
   Addresses 0x00000000-0x0003FFFF are allocated for On-Chip Flash Memory. 256 KB Flash memory
   Addresses 0x40025000-0x40025FFF are allocated for GPIO Port F to which the On-Board LED is connected to.
   Clock Gating is usually employed in Microcontrollers to save power. So inorder to turn on GPIO Port F, we need 
   to enable RCGCGPIO register which is located at 0x400FE608 (Base:0x400FE000, Offset:0x608). Bit 5 has to be changed to 1
   to enable GPIO port F.
   
   The LED can be turned on by manually changing register values or running the script mentioned in this file.
*/  


int main() {
  *((unsigned int*)0x400FE608U) = 0x20U;  // Setting Bit 5 of register RCGCGPIO to 1
  *((unsigned int*)0x40025400U) = 0x0EU;   
  *((unsigned int*)0x4002551CU) = 0x2EU;
  
  while(1){
    *((unsigned int*)0x400253FCU) = 0x02U; // Enabling the Red bit in the Register (0010 = 0x02)
    int counter = 0;
    while(counter < 100000){
    ++ counter;
    }
    *((unsigned int*)0x400253FCU) = 0x00U;  // Disabling the Red Bit in the register.
    while(counter < 100000){
    ++ counter;
    }
  } 
  return 0;
 }
   

