#include<stdio.h>
#include<stdlib.h>


int sanity(int**, int, int);
int isUnsolved(int**);
int preCheck(int**);
int solve(int**);
void print(int**);


int isUnsolved(int** hexa){
  for(int  i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(hexa[i][j] == -1)
        return 1;
    }
  }
  return 0;
}

int sanity(int** hexa, int r, int c){
  int num = hexa[r][c];
  for (int i = 0; i < 16; i++) {
    if ((hexa[i][c] == num) && (i != r))
      return 0;
    if ((hexa[r][i] == num) && (i != c))
      return 0;
  }

  int rowStart = ((r / 4)) * 4;
  int colStart = ((c / 4)) * 4;

  for (int row = rowStart; row < rowStart + 4; row++)
		for (int col = colStart; col < colStart + 4; col++)
			if ((hexa[row][col] == num) && (row != r) && (col != c))
			{
				return 0;
			}

  return 1;
}

int preCheck(int** hexa){
  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 16; j++){
      if(hexa[i][j] != -1){
        if(sanity(hexa, i, j) != 1){
          return 0;
        }
      }
    }
  }
  return 1;
}

int solve(int** hexa){
  int cellsSolved = 0;
  for(int i = 0; i<16; i++){
    for(int j = 0; j < 16; j++){
      if(hexa[i][j] == -1){
        int n = 0;
        int sol;
        for(int k = 0; k < 16; k++){
          hexa[i][j] = k;
          if(sanity(hexa, i, j) == 1){
            n = n + 1;
            sol = k;
            // printf("%d\n", sol);
          }
        }
        hexa[i][j] = -1;
        if(n == 1){
          hexa[i][j] = sol;
          cellsSolved++;
        }
        // else{
        //   printf("value of r is %d, col is %d, and n is %d\n", i, j, n);
        //   return 0;
        // }
      }
    }
  }
  return cellsSolved;
}

void print(int** matrix) {
	for (int i = 0; i < 16; i++) {
		for (int j = 0; j < 16; j++) {
			printf("%X\t", matrix[i][j]);
		}
		printf("\n");
		}
}

int main(int argc, char** argv){
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    exit(0);
  }

  int** hexadoku;
  int i;
  int j;

  hexadoku = malloc(16 * sizeof(int*));
  for(i = 0; i<16; i++){
    hexadoku[i] = malloc(16* sizeof(int));
  }

  //fill in grid
  for(i = 0; i<16; i++){
    for(j = 0; j<16; j++){
        int put = -1;
        fscanf(fp,"%X", &put);
        hexadoku[i][j] = put;
    }
    fscanf(fp,"\n");
  }

  // for(int i = 0; i< 16; i++){
  //   for(int j = 0; j < 16; j++){
  //   }
  // }

  if(preCheck(hexadoku) == 0){
    printf("no-solution\n");
    exit(0);
  }

  while(isUnsolved(hexadoku) == 1){
    if(solve(hexadoku) == 0){
      printf("no-solution\n");
      return 1;
    }
  }

  print(hexadoku);
  // if(solve(hexadoku) == 1)
  //   print(hexadoku);
  // else
  //   printf("no-solution\n");

  fclose(fp);
  for(i = 0; i<16; i++){
        free(hexadoku[i]);
    }
    free(hexadoku);

  return 0;
}
