#include<stdio.h>
#include<stdlib.h>

struct node{
  int a;
  struct node * next;
};

struct node* hashtable[1000] = {NULL};
int hash(int);
char* insert(int, int);
char* search(int, int);

int hash(int a){
  if(a>=0)
    return a%1000;
  else
    return abs(a%1000);
}

char* insert(int i, int key){

  //make the node for the int and assign it
  struct node* temp = malloc(sizeof(struct node));
  temp->a = i;
  temp->next = NULL;

  //if the LL at that key is empty, set the LL to the new node
  if(hashtable[key] == NULL){
    hashtable[key] = temp;
    return "inserted";
  }
  //if its not empty, we can add it to the end of the LL if it doesnt exist already
  else{
    struct node * ptr = hashtable[key];
    struct node * prev = NULL;

    while(ptr != NULL){
      if(ptr->a == i){
        return "duplicate";
      }
      prev = ptr;
      ptr = ptr->next;
    }
    prev->next = temp;
    return "inserted";
  }
}

char* search(int i, int key){
  //first we want to see if the LL is empty at that key, if it is, then i dosnt exist
  if(hashtable[key] == NULL){
    return "absent";
  }
  else{
    struct node * ptr = hashtable[key];

    while(ptr != NULL){
      if(ptr->a == i){
        return "present";
      }
      ptr = ptr->next;
    }

    //since the loop finished and it couldnt find i, that means it doesnt exist
    return "absent";
  }
}

int main(int argc, char** argv){
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL){
    exit(0);
  }

  while(!feof(fp)){
    char ok;
    int val;
    fscanf(fp, "%c %d\n", &ok, &val);
    if(ok == 'i'){
      printf("%s\n", insert(val, hash(val)));
    }
    else{
      printf("%s\n", search(val, hash(val)));
    }
  }

  int i = 0;
  for(i = 0; i< 1000; i++){
    struct node * temp = hashtable[i];
    while(temp != NULL){
      struct node * temp2 = temp;
      temp = temp->next;
      free(temp2);
    }
  }

  fclose(fp);


  return 0;
}
