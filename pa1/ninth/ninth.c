#include<stdio.h>
#include<stdlib.h>

struct node{
  int a;
  struct node * left;
  struct node * right;
};

struct node * root = NULL;
void freetree(struct node*);
void search(struct node*, int, int);
void insert(int);
void delete(int);

void freetree(struct node* bst){
  if(bst == NULL)
    return;

  freetree(bst->left);
  freetree(bst->right);

  free(bst);
}

void delete(int i){
  //based off my bst delete from data structures
  struct node * x = root;
  struct node * prev = NULL;

  //find where the node to be deleted is
  while(x != NULL){
    if(i == x->a)
      break;

    prev = x;

    if(i < x->a)
      x = x->left;
    else
      x = x->right;
  }

  //the tree is empty or the node doesnt exist
  if(x == NULL){
    printf("fail\n");
    return;
  }

  //if there is a right and left child, we have to get to the min in the right subtree
  if(x->left != NULL && x->right != NULL){
    struct node * y = x->right;
    prev = x;

    while(y->left != NULL){
      prev = y;
      y = y->left;
    }
    x->a = y->a;
    x = y;
  }

  //if the node to be deleted is root
  if(prev == NULL){
    if(x->left != NULL)
      root = x->left;
    else
      root = x->right;

    printf("success\n");
    return;
  }

  //if we reach this point, we know x only has one child, parent of node to be deleted is now the child of that deleted node
  if(x == prev->right){
    if(x->left != NULL)
      prev->right = x->left;
    else
      prev->right = x->right;
  }
  else{
    if(x->left != NULL)
      prev->left = x->left;
    else
      prev->left = x->right;
  }
  printf("success\n");
  return;

}

void search(struct node* bst, int i, int h){
  if(bst == NULL)
    printf("absent\n");
  else if(bst->a == i)
    printf("present %d\n", h);
  else if(bst->a > i)
    return search(bst->left, i, h+1);
  else
    return search(bst->right, i, h+1);
}

void insert(int i){
  struct node * ptr = root;
  struct node * prev = NULL;
  int height = 1;

  while(ptr != NULL){
    if(ptr->a == i){
      printf("duplicate\n");
      return;
    }

    prev = ptr;

    if(ptr->a > i){
      ptr = ptr->left;
      height++;
    }
    else{
      ptr = ptr->right;
      height++;
    }
  }

  struct node* temp = malloc(sizeof(struct node));
  temp->a = i;

  if(prev == NULL){
    root = temp;
    printf("inserted %d\n", height);
    return;
  }

  if(i < prev->a){
    prev->left = temp;
    printf("inserted %d\n", height);
    return;
  }
  else{
    prev->right = temp;
    printf("inserted %d\n", height);
    return;
  }

}

int main(int argc, char** argv){
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    printf("error");
    exit(0);
  }

  while(!feof(fp)){
    char ok;
    int val;
    fscanf(fp, "%c %d\n", &ok, &val);
    if(ok == 'i'){
      insert(val);
    }
    else if(ok == 's'){
      search(root, val, 1);
    }
    else{
      delete(val);
    }
  }
  // search(root, 5, 1);
  //
  // insert(4);
  // insert(5);
  // search(root, 5, 1);

  freetree(root);
  fclose(fp);



  return 0;
}
