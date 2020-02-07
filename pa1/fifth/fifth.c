#include<stdio.h>
#include<stdlib.h>

void print(int**, int, int);
char* isMagic(int**, int);

void print(int** matrix, int r, int c){
    int i,j;
    for(i = 0; i<r; i++){
        for(j = 0; j<c;j++){
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }

}

char* isMagic(int** m, int n){
  //check if its all unique
  int a, b, c, d;
  for(a = 0; a < n; a++){
    for(b = 0; b < n; b++){
      for(c = a + 1; c < n; c++){
        for(d = 0; d < n; d++){
          if(m[a][b] == m[c][d]){
            return "not-magic";
          }
        }
      }
    }
  }

  //calculate sum of diag 1
  int s1 = 0;
  int i;
  for(i = 0; i < n; i++){
    s1 = s1 + m[i][i];
  }

  //calcuate sum of diag 2
  int s2 = 0;
  for(i = 0; i < n; i++){
    s2 = s2 + m[i][n-i-1];
  }



  //if these 2 r different, its not magic
  if(s1!=s2){
    return "not-magic";
  }

  //now we have what the sum should be, so we can just compare it to the sum of the rows and columns and if any r diff, return no
  int j;
  for(i = 0; i<n; i++){
    int s3 = 0;
    for(j = 0; j < n; j++){
      s3 = s3 + m[i][j];
    }
    if(s1 != s3){
      return "not-magic";
    }
  }

  for(i = 0; i<n; i++){
    int s4 = 0;
    for(j = 0; j < n; j++){
      s4 = s4 + m[j][i];
    }
    if(s1 != s4){
      return "not-magic";
    }
  }

  //if we reach this point, all the diags and sums in rows and cols r equal
  return "magic";

}


int main(int argc, char** argv){
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    exit(0);
  }

  int i, j;
  int** matrix1;
  int a;
  fscanf(fp, "%d\n", &a);
  matrix1 = malloc(a * sizeof(int*));
  for(i = 0; i<a; i++){
    matrix1[i] = malloc(a* sizeof(int));
  }
  for(i = 0; i<a; i++){
    for(j = 0; j<a; j++){
        fscanf(fp,"%d", &matrix1[i][j]);
    }
    fscanf(fp,"\n");
  }

  // print(matrix1, a, a);
  printf("%s\n", isMagic(matrix1, a));

  for(i = 0; i<a; i++){
        free(matrix1[i]);
    }
    free(matrix1);

  fclose(fp);

  return 0;

}
