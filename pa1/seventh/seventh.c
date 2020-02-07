#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv){
  int i;
  for(i = 1; i < argc; i++){
    int len = strlen(argv[i]);
    printf("%c", argv[i][len-1]);
  }
  printf("\n");
  return 0;
}
