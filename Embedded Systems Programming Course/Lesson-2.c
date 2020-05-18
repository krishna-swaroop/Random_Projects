// Lesson-2
// This lesson explores making changes to flow of control in a program.
// It explores referencing the assembly code to track how the compiler handles loops when compared to explicit statements.

int main() {
  int counter =0;
  while (counter < 21) {
    ++counter;
    if((counter & 1) != 0){
      // do something when the counter is odd
    }
    else{
      // do something when the counter is even
    }
  }
  return 0;
}
