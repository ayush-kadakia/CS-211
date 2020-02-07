#include<stdio.h>
#include<stdlib.h>

int isPrime(int);

int isPrime(int i){

  if(i <= 1){
    return 0;
  }

  for(int a = 2; a*a <= i; a++){
    if(i % a == 0){
      return 0;
    }
  }

  return 1;
}

//reads the file and exits if its null
int main(int argc, char** argv){
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    exit(0);
  }

//counts the number of entries in input file, will exit if none
  int num = 0;
  if(fscanf(fp, "%d\n", &num) ==EOF){
    exit(0);
  }

  for(int i = 0; i < num; i++){
    int temp;
    fscanf(fp, "%d\n", &temp);

    int ans = 0;

    while(temp > 0){
      if(isPrime(temp) == 0){
        ans = 0;
        break;
      }
      else{
        temp = temp/10;
        ans = 1;
      }
    }

    if(ans == 1){
      printf("yes\n");
    }
    else{
      printf("no\n");
    }
  }




  return 0;

}
