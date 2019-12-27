#include <stdio.h>
#include <stdlib.h>
#include "LargeInt.h"
#include "utils.h"

//function to create a new digit with value as val
Digit createDigit(int val){

  //check if the value is valid
  if(val < 0 || val > 9999){
    printf("\nInvalid value (%d) for a digit.\n", val);
    return NULL;
  }

  //allocate memory for a new digit
  Digit newDigit = (Digit) malloc(sizeof(struct digit));
  if(!newDigit){
    printf("\nUnable to allocate memory for a new digit.\n");
    return NULL;
  }

  //everything went well, add the value to newDigit and return
  newDigit->val = val;
  newDigit->next=NULL;

  return newDigit;

}

//function to create an empty large integer
LargeInt createLargeInt(){

  //allocate memory for a new large integer
  LargeInt newLargeInt = (LargeInt) malloc(sizeof(struct largeInt));
  if(!newLargeInt){
    printf("\nUnable to create an empty large integer.\n");
    return NULL;
  }

  newLargeInt->lsb = NULL;
  newLargeInt->msb = NULL;
  newLargeInt->num_digits = 0;

  return newLargeInt;

}

//function to add a new digit as the LSB to large integer
int addLsbDigit(LargeInt largeInt, int digitVal){

  //creating a new digit struct object
  Digit digit = createDigit(digitVal);
  if(!digit){
    return 0;
  }

  if(largeInt->num_digits == 0){
    //first digit being added to the large integer
    largeInt->lsb = digit;
    largeInt->msb = digit;
    largeInt->num_digits++;
  }
  else{
    //adding the digit as the new LSB
    digit->next = largeInt->lsb;
    largeInt->lsb = digit;
    largeInt->num_digits++;
  }

  return 1;

}

//function to add a new digit as the MSB to large integer
int addMsbDigit(LargeInt largeInt, int digitVal){

  //creating a new digit struct object
  Digit digit = createDigit(digitVal);
  if(!digit){
    return 0;
  }

  if(largeInt->num_digits == 0){
    //first digit being added to the large integer
    largeInt->lsb = digit;
    largeInt->msb = digit;
    largeInt->num_digits++;
  }
  else{
    //adding the digit as the new MSB
    largeInt->msb->next = digit;
    largeInt->msb = digit;
    largeInt->num_digits++;
  }

  return 1;

}

//function to free up the memory of large integer
void freeLargeInt(LargeInt largeInt){

  //there are zero digits, so we just have to free the large integer
  if(largeInt->num_digits == 0){
    free(largeInt);
    return;
  }


  Digit curDigit = largeInt->lsb;
  Digit nextDigit = curDigit->next;

  //we iterate the list of digits and free one digit at a time
  while(nextDigit){
    free(curDigit);
    curDigit = nextDigit;
    nextDigit = curDigit->next;
  }

  free(curDigit); //free the last digit
  free(largeInt); //free the large integer finally

}

//function to read and create a large integer from input
LargeInt inputLargeInt(){

  //creating a new empty large integer
  LargeInt newLargeInt = createLargeInt();
  if(!newLargeInt){
    return newLargeInt;
  }


  //printf("\nEnter the large integer with digits seprated by comma and ineteger ending with $ (no spaces)\n");

  char digitStr[4];     //stores the current digit being read
  int ch;              //stores the current character being read
  int index = 0;      //index for the digit string

  //continously reading the input from stdin character by character
  while(ch=fgetc(stdin)){

    if(ch == '\n'){
      //ignore any new line characters
      continue;
    }

    //checing if the character read is valid
    int check = isValidLargeIntChar(ch);
    if(!check){
      printf("\nInvalid character input.\n");
      return NULL;
    }

    if(',' == ch && index == 4){
      //if true means that we have read a complete digit and must add it to the large integer

      index=0; //resetting the index for the digit string

      //convert the digit string to actual value
      int digitVal = atoi(digitStr);

      //adding the digit to the large integer as new LSB
      if(!addLsbDigit(newLargeInt, digitVal)){
        printf("\nUnable to add the digit as LSB.\n");
        return NULL;
      }

      //successfully added a new digit, now continue since we have not seen $
      continue;
    }

    else if('$' == ch && index==4){
      //this means we have read the last digit in input and must add it to the large integer

      //convert the digit string tto actual value
      int digitVal = atoi(digitStr);

      //adding the digit to the large integer as new LSB
      if(!addLsbDigit(newLargeInt, digitVal)){
        printf("\nUnable to add the digit as LSB.\n");
        return NULL;
      }

      //successfully added the last digit
      //since we have seen $, we will break the loop to stop reading from the stdin
      break;
    }
    else{
      //means this is a single character of a digit, so we add it to the current digit string
      digitStr[index++] = ch;
    }
  }



  //returning the large integer
  return newLargeInt;

}

//function to print the digits linked list in reverse order using recursion
void printFromMsb(LargeInt largeInt, Digit digitHead){

  //base case for recursion
  if(!digitHead){
    return;
  }

  //recursive call
  printFromMsb(largeInt, digitHead->next);

  //printing the value of current digit
  if(digitHead == largeInt->lsb){
    printf("%04d$", digitHead->val);
  }
  else{
    printf("%04d,", digitHead->val);
  }

}

//function to print a large integer from the linked list representation
void printLargeInt(LargeInt largeInt){

  //nothing to print
  if(largeInt->num_digits == 0){
    printf("\nThe large integer is empty.\n");
    return;
  }

  Digit digitHead = largeInt->lsb;
  printFromMsb(largeInt, digitHead);
}

//function to add two large integers
LargeInt addLargeInts(LargeInt largeIntA, LargeInt largeIntB){

  if(largeIntA == NULL || largeIntB == NULL){
    printf("\nAddition: Unable to add as atleast one of the large ineteger is invalid.\n");
    return NULL;
  }

  //creating a new large integer to store the result of addition operation
  LargeInt resLargeInt = createLargeInt();

  //digits pointing to the current digit being visited in the linked lists
  Digit curDigitA = largeIntA->lsb;
  Digit curDigitB = largeIntB->lsb;

  //the number of digits which we need to iterate
  int num_digits_iterable = max(largeIntA->num_digits, largeIntB->num_digits);

  //carry which will be used during addition operation
  int carry = 0;

  //iterating the digits one by one and adding them together
  for(int i=0; i<num_digits_iterable; i++){
    int result = 0;

    if(!curDigitA){
      //we have iterated over all digits in large integer A
      result = curDigitB->val;
    }
    else if(!curDigitB){
      //we have iterated over all digits in large integer B
      result = curDigitA->val;
    }
    else{
      //both large integers have digits left to add
      result = curDigitA->val + curDigitB->val;
    }

    //if we have carry from previous calculation, add it to the result
    if(carry == 1){
      result+=carry;
      carry = 0;
    }

    //checking if there is a carry from the current result
    if(result>=BASE){
      //if result exceeds BASE, then there is a carry
      result-= BASE;
      carry = 1;
    }

    //adding the result as a new digit in the large integer
    if(!addMsbDigit(resLargeInt, result)){
      printf("\nAddition: Failed to add the result as a new digit.\n");
      return NULL;
    }

    //moving on to the next digits
    if(curDigitA){
      curDigitA = curDigitA->next;
    }
    if(curDigitB){
      curDigitB = curDigitB->next;
    }

  }

  //if carry is still remaining, we need to add a new digit
  if(carry == 1){
    if(!addMsbDigit(resLargeInt, 1)){
      printf("\nAddition: Failed to add the carry as a new digit.\n");
      return NULL;
    }
  }

  //return the resultant large integer
  return resLargeInt;

}

//function to multiply two large integers
LargeInt multiplyLargeInts(LargeInt largeIntA, LargeInt largeIntB){

  if(largeIntA == NULL || largeIntB == NULL){
    printf("\nMultiplication: Unable to multiply as atleast one of the large ineteger is invalid.\n");
    return NULL;
  }

  //creating a new large integer to store the result of multiplication operation
  LargeInt resLargeInt = createLargeInt();
  if(!resLargeInt){
    printf("\nMultiplication: Failed to create a resultant large integer.\n");
    return NULL;
  }

  //these would be used to iterate over A & B in the correct order
  LargeInt smallLargeInt, bigLargeInt;
  if(largeIntA->num_digits > largeIntB->num_digits){
    smallLargeInt = largeIntB;
    bigLargeInt = largeIntA;
  }
  else{
    smallLargeInt = largeIntA;
    bigLargeInt = largeIntB;
  }

  //the current digit for the smaller integer of A & B
  Digit curDigitSmall = smallLargeInt->lsb;

  //looping over the smaller integer and multiplying the current digit with whole of bigger integer
  for(int i=0; i<smallLargeInt->num_digits; i++, curDigitSmall=curDigitSmall->next){

    /*
    current large integer to store the result of multiplication of current digit of smaller integer with all
    other digits of bigger integer
    */
    LargeInt curResLargeInt = createLargeInt();
    if(!curResLargeInt){
      printf("\nMultiplication: Failed to create a resultant large integer.\n");
      return NULL;
    }

    //shifting the integer depending on the index of digit of smaller integer
    for(int k=0;k<i;k++){
      if(!addMsbDigit(curResLargeInt, 0)){
        printf("\nMultiplication: Failed to add MSB digit to large integer.\n");
        return NULL;
      }
    }

    //the current digit of the bigger integer of A & B
    Digit curDigitBig = bigLargeInt->lsb;

    //to store the carry generated during calculations
    int carry=0;

    //looping over the bigger integer and multiplying each of them with current digit of smaller integer
    for(int j=0; j<bigLargeInt->num_digits; j++, curDigitBig=curDigitBig->next){

      //calculating the result of multiplication of two digits and adding any carry
      int res = curDigitBig->val * curDigitSmall->val;
      if(carry>0){
        res += carry;
        carry=0;
      }

      //generating the result of multiplication and carry
      if(res>=BASE){
        carry = res/BASE;
        res = res % BASE;
      }

      //the result of multiplication is added as an MSB to the current large integer
      if(!addMsbDigit(curResLargeInt, res)){
        printf("\nMultiplication: Failed to add MSB digit to large integer.\n");
        return NULL;
      }

    }

    //if any carry is left from iterating over the bigger integer, it is added as an MSB to the large integer of the iteration
    if(carry>0){
      if(!addMsbDigit(curResLargeInt, carry)){
        printf("\nMultiplication: Failed to add MSB digit to large integer.\n");
        return NULL;
      }
    }

    //printf("\nPrinting the large int generated by iterating over the bigger integer for the (%d) time.\n", i+1);

    //printLargeInt(curResLargeInt);

    //the current large integer is added with the overall resultant large integer
    resLargeInt = addLargeInts(resLargeInt, curResLargeInt);
    if(!resLargeInt){
      printf("\nMultiplication: Failed to add two large integers.\n");
      return NULL;
    }
    //printf("\nPrinting the overall large int after iterating over the bigger integer for the (%d) time.\n", i+1);

    //printLargeInt(resLargeInt);

  }

  return resLargeInt;

}
