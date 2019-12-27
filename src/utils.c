#include "utils.h"

//function to check if the character is a valid character of a large integer
int isValidLargeIntChar(char ch){
  if(ch=='$' || ch==',' || (ch>='0' && ch<='9')){
    return 1;
  }
  else{
    return 0;
  }
}

//returns max of two integers
int max(int a, int b){
  int res = a;

  if(b>res){
    res=b;
  }

  return res;
}
