#define BASE 10000

typedef struct digit{

  //the value of the digit 0 - (BASE-1)
  int val;

  //pointers to make it a doubly linked list
  struct digit* next;

} *Digit;

typedef struct largeInt{

  //the digit at the LSB of the large integer
  Digit lsb;

  //the digit at the LSB of the large integer
  Digit msb;

  //the number of digits in the large integer
  int num_digits;

} *LargeInt;

//function to create a new digit with a value of val
Digit createDigit(int val);

//function to create an empty large integer
LargeInt createLargeInt();

//function to add a new digit as the LSB to large integer
int addLsbDigit(LargeInt largeInt, int val);

//function to add a new digit as the MSB to large integer
int addMsbDigit(LargeInt largeInt, int digitVal);

//function to read and create a large integer from input
LargeInt inputLargeInt();

//function to print the digits linked list in reverse order using recursion
void printFromMsb(LargeInt largeInt, Digit digitHead);

//function to print a large integer from the linked list representation
void printLargeInt(LargeInt largeInt);

//function to free up the memory of large integer
void freeLargeInt(LargeInt largeInt);

//function to add two large integers
LargeInt addLargeInts(LargeInt a, LargeInt b);

//function to multiply two large integers
LargeInt multiplyLargeInts(LargeInt a, LargeInt b);
