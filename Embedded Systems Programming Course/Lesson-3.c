// Lesson-3
// This lesson explores Variables and Pointers in Embedded programming

int counter = 0; // counter is now a global variable.
// Thus, it can't be viewed in the locals tab. Acces it through the Watch Tab.


int main() {
  int *p_int;       // declaring a pointer with the name p_int which will point to an integer
  p_int = &counter; // Assigning the address of counter as the value of the pointer.
  while(*p_int < 21) {
    ++(*p_int);
  }
  p_int = (int *)0x20000002U; // type casting the value 0x20000002U into p_int.
  // Type casting has to be done as a value of type "unsigned int" can't be assigned to an entity of the type 'int'
  
  *p_int = 0xDEADBEEF;        // This should put the value DEADBEEF to the memory address 0x20000002U.
  /* But due to misalignment of memory this results in-
     Address  Val       val      val      val
     20000000 beef0015 2000dead 00000000 00000000
     
     This misalignment is acceptable in Cortex M4 as it supports unaligned memory access but a family like M0 
     will hav e thrown an error
  */
  
  return 0;
}
