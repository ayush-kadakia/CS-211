#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char** argv){

  int i;
  for(i = 1; i < argc; i++){
    if(argv[i][0] == 'a' || argv[i][0] == 'e' || argv[i][0] == 'i' || argv[i][0] == 'o' || argv[i][0] == 'u' || argv[i][0] == 'A' || argv[i][0] == 'E' || argv[i][0] == 'I' || argv[i][0] == 'O' || argv[i][0] == 'U'){
      int len = strlen(argv[i]);
      int j;
      for(j = 0; j < len; j++)
        printf("%c", argv[i][j]);
      printf("yay ");
    }
    else{
      int len = strlen(argv[i]);
      int fv = len;
      int j;
      for(j = 0; j < len; j++){
        if(argv[i][j] == 'a' || argv[i][j] == 'e' || argv[i][j] == 'i' || argv[i][j] == 'o' || argv[i][j] == 'u' || argv[i][0] == 'A' || argv[i][0] == 'E' || argv[i][0] == 'I' || argv[i][0] == 'O' || argv[i][0] == 'U'){
          fv = j;
          break;
        }
      }


      int k;
      for(k = fv; k < len; k++)
        printf("%c", argv[i][k]);

      int l;
      for(l = 0; l < fv; l++)
        printf("%c", argv[i][l]);

      printf("ay ");
    }
  }

  return 0;

}
