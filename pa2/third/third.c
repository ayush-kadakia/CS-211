#include<stdio.h>
#include<stdlib.h>

double** multiply(double**, int, int, double**, int, int);
double** transpose(double**, int, int);
double** inverse(double**, int);
void print(double**, int, int);
void free_matrix(double**, int);

double** multiply(double** m1, int r1, int c1, double** m2, int r2, int c2){

  double** result;
  int i;
  result = malloc(r1 * sizeof(double*));
  for(i = 0; i<r1; i++){
    result[i] = malloc(c2* sizeof(double));
  }

  int a, b, c;
  double total = 0;

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

double** transpose(double** m1, int r1, int c1){
  double** result;
  int i;
  result = malloc(c1 * sizeof(double*));
  for(i = 0; i<r1; i++){
    result[i] = malloc(r1* sizeof(double));
  }

  int a, b;

  for(a = 0; a < r1; a++){
    for(b = 0; b < c1; b++){
      result[b][a] = m1[a][b];
    }
  }

  return result;
}

double** inverse(double** matrix, int s){
  //make the inverse matrix to be returned
  double** result;
  int i, j, k;
  result = malloc(s * sizeof(double*));
  for(i = 0; i<s; i++){
    result[i] = malloc(s* sizeof(double));
  }

  //make the result the identity matrix
  for(i = 0; i < s; i++){
    for(j = 0; j < s; j++){
      if(i == j)
        result[i][j] = 1;
      else
        result[i][j] = 0;
    }
  }

  //begin gauss-jordan elimniation
  //as outlined in pa2 instructions, we start by transforming the bottom left triangle
  for(i = 0; i< s; i++){
    for(j = i; j<s; j++){
      //we want to make all the diagonal entries 1
      if(matrix[j][i] != 1 && j == i){
        if(matrix[j][i] != 0){
          double temp = matrix[j][i];
          for(k = 0; k < s; k++){
            matrix[j][k] = matrix[j][k] / temp;
            result[j][k] = result[j][k] / temp;
          }
        }
      }
      //if its not a diagonal entry, its under it, and we want to make everything under the diagonal 0
      else if(matrix[j][i] != 0 && j!= i){
        double temp = matrix[j][i];
        for(k = 0; k < s; k++){
          matrix[j][k] = matrix[j][k] - (temp * matrix[i][k]);
          result[j][k] = result[j][k] - (temp * result[i][k]);
        }
      }
    }
  }

  //if we reach this point, the diagonals should be all 1, and everything under it should be 0
  //now we just make the remaining upper right triangle all 0s
  for(i = s - 1; i >= 0; i--){
    for(j = i; j >= 0; j--){
      if(matrix[j][i] != 0 && i != j){
        double temp = matrix[j][i];
        for(k = 0; k < s; k++){
          matrix[j][k] = matrix[j][k] - (temp * matrix[i][k]);
          result[j][k] = result[j][k] - (temp * result[i][k]);
        }
      }
    }
  }

  return result;

}

void print(double** matrix, int r, int c){
    int i,j;
    for(i = 0; i<r; i++){
        for(j = 0; j<c;j++){
            printf("%lf\t",matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(double** matrix, int r){
  int i;
  for(i = 0; i<r; i++){
        free(matrix[i]);
    }
    free(matrix);
}


int main(int argc, char** argv){

//read the train data
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    exit(0);
  }

  int i, j;
  double** matrix1;
  int col;
  fscanf(fp, "%d\n", &col);
  int row;
  fscanf(fp, "%d\n", &row);

  matrix1 = malloc(row * sizeof(double*));
  for(i = 0; i<row; i++){
    matrix1[i] = malloc((col+1)* sizeof(double));
  }
  for(i = 0; i<row; i++){
    for(j = 0; j<col+1; j++){
        fscanf(fp,"%lf,", &matrix1[i][j]);
    }
    fscanf(fp,"\n");
  }

//read the test data
  FILE* fp2 = fopen(argv[2], "r");
  if(fp2 == NULL){
    exit(0);
  }

  double** matrix2;
  int row2;
  fscanf(fp2, "%d\n", &row2);

  matrix2 = malloc(row2 * sizeof(double*));
  for(i = 0; i<row2; i++){
    matrix2[i] = malloc(col* sizeof(double));
  }
  for(i = 0; i<row2; i++){
    for(j = 0; j<col; j++){
        fscanf(fp2,"%lf,", &matrix2[i][j]);
    }
    fscanf(fp2,"\n");
  }


  //make X matrix
  double** X;
  X = malloc(row * sizeof(double*));
  for(i = 0; i < row; i++){
    X[i] = malloc((col+1) * sizeof(double));
  }

  for(i = 0; i< row; i ++){
    X[i][0] = 1; //first col gotta be 0
    for(j = 1; j < (col + 1); j++)
      X[i][j] = matrix1[i][j-1];
  }

  //make Y matrix
  double** Y;
  Y = malloc(row * sizeof(double*));
  for(i = 0; i < row; i++){
    Y[i] = malloc(sizeof(double));
  }

  for(i = 0; i<row;i++){
      Y[i][0] = matrix1[i][col];
  }


  //make W matrix
  double** W;
  W = malloc(col * sizeof(double*));
  for(i = 0; i < col; i++){
    W[i] = malloc(sizeof(double));
  }

  //The formula
  int column = col + 1;

  double** xtranspose = transpose(X, row, column);
  double** xttimesx = multiply(xtranspose, column, row, X, row, column);
  double** inversed = inverse(xttimesx, column);
  double** abovetimesxt = multiply(inversed, column, column, xtranspose, column, row);
  double** weights = multiply(abovetimesxt, column, row, Y, row, 1);

  //using weights to predict
  double y = weights[0][0];

  for(i = 0; i<row2; i++){
    for(j = 0; j < col; j++){
      y = y + weights[j+1][0]*matrix2[i][j];
    }
    printf("%0.0lf\n", y);
    y = weights[0][0];
  }

  //free everything
  fclose(fp);
  fclose(fp2);
  free_matrix(matrix1, row);
  free_matrix(matrix2, row2);
  free_matrix(xttimesx, column);
  free_matrix(inversed, column);
  free_matrix(abovetimesxt, column);
  free_matrix(weights, column);

  return 0;
}
