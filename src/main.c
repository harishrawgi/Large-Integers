#include <stdio.h>
#include "LargeInt.h"

//function to take one expression as input and calculate the result
int doOneExpression(){

  //large integers to store the current two operands
  LargeInt largeIntA, largeIntB;

  //character to read the input
  int ch;

  printf("\nEnter the expression below:\n");

  //take the first input of large integer
  largeIntA = inputLargeInt();
  if(!largeIntA){
    printf("\nUnable to input large integer.\n");
    return 0;
  }

  //loop over reading the input and calulating results till we see an '='
  do{

    //take the input of the operator ('=', '+', or '*')
    ch = fgetc(stdin);

    //if we get '=', print the current large integer and return
    if(ch == '='){
      printf("\nPrinting the resultant large integer below:\n");
      printLargeInt(largeIntA);

      //taking the new line character at the end
      ch = fgetc(stdin);
      return 1;
    }

    //input another large integer to operate on (operator is stored in ch at this moment)
    largeIntB = inputLargeInt();
    if(!largeIntB){
      printf("\nUnable to input large integer.\n");
      return 0;
    }

    //if the input was of a '+', we add the two integers
    if(ch == '+'){
      largeIntA = addLargeInts(largeIntA, largeIntB);
      if(!largeIntA){
        printf("\nUnable to add large integers.\n");
        return 0;
      }
    }
    //if the input was of a '*', we multiply the two integers
    else if(ch == '*'){
      largeIntA = multiplyLargeInts(largeIntA, largeIntB);
      if(!largeIntA){
        printf("\nUnable to multiply large integers.\n");
        return 0;
      }
    }
    //something invalid was read
    else{
      printf("\nInvalid input.\n");
      return 0;
    }

    //continue with the current result stored in largeIntA
  }while(1);

  //free the large integers that we have been using
  freeLargeInt(largeIntA);
  freeLargeInt(largeIntB);
}

int main(){

  printf("---------------------------------------Large Integer expression calculator program---------------------------------------\n\n\n");

  int ch = 'y';

  //keep repeating as long as user keeps entering y
  while(ch == 'y'){

    //perform one iteration of calulating one single expression
    if(!doOneExpression()){
      printf("\nSomething went wrong! Press y to calculate another expression.\n");
    }else{
      printf("\nPress y to calculate another expression.\n");
    }

    //take input from user to decide whether to continue
    ch = fgetc(stdin);
  }

  printf("\nEnding the program....\n");

  return 0;
}
