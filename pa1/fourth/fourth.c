#include<stdio.h>
#include<stdlib.h>

void print(int**, int, int);
int** multiply(int**, int, int, int**, int, int);

void print(int** matrix, int r, int c){
    int i,j;
    for(i = 0; i<r; i++){
        for(j = 0; j<c;j++){
            printf("%d\t",matrix[i][j]);
        }
        printf("\n");
    }

}

int** multiply(int** m1, int r1, int c1, int** m2, int r2, int c2){

  int** result;
  int i;
  result = malloc(r1 * sizeof(int*));
  for(i = 0; i<r1; i++){
    result[i] = malloc(c2* sizeof(int));
  }

  int a, b, c, total;
  for(a = 0; a < r1; a++){
    for(b = 0; b < c2; b++){
      for(c = 0; c < r2; c++){
        total = total + m1[a][c] * m2[c][b];
      }

      result[a][b] = total;
      total = 0;
    }
  }

  return result;
}

int main(int argc, char** argv){
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    exit(0);
  }

  int i, j;
  //declare matrix 1, read its rows and cols and malloc
  int** matrix1;
  int row1;
  int col1;
  fscanf(fp, "%d %d\n", &row1, &col1);
  matrix1 = malloc(row1 * sizeof(int*));
  for(i = 0; i<row1; i++){
    matrix1[i] = malloc(col1* sizeof(int));
  }

  //fill in matrix 1
  for(i = 0; i<row1; i++){
    for(j = 0; j<col1; j++){
        fscanf(fp,"%d", &matrix1[i][j]);
    }
    fscanf(fp,"\n");
  }


  //declare matrix 2, read its rows and cols and malloc
  int** matrix2;
  int row2;
  int col2;
  fscanf(fp, "%d %d\n", &row2, &col2);
  matrix2 = malloc(row2 * sizeof(int*));
  for(i = 0; i<row2; i++){
    matrix2[i] = malloc(col2* sizeof(int));
  }

  //fill in matrix 2
  for(i = 0; i<row2; i++){
    for(j = 0; j<col2; j++){
        fscanf(fp,"%d", &matrix2[i][j]);
    }
    fscanf(fp,"\n");
  }

  if(col1 != row2){
    printf("bad-matrices\n");
    exit(0);
  }
  else{
  int** output = multiply(matrix1, row1, col1, matrix2, row2, col2);
  print(output, row1, col2);
  for(i = 0; i<row1; i++){
        free(output[i]);
    }
    free(output);
  }

  for(i = 0; i<row1; i++){
        free(matrix1[i]);
    }
    free(matrix1);


  for(i = 0; i<row2; i++){
        free(matrix2[i]);
    }
    free(matrix2);

    fclose(fp);


  return 0;
}
