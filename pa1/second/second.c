#include<stdio.h>
#include<stdlib.h>

struct node{
  int a;
  struct node * next;
};

struct node * head = NULL;
void insert(int);
void delete(int);
void print();

void insert(int i){
  //before doing anything we want to see if the new value is already in the LL
  struct node* hi = head;
  while(hi != NULL){
    if(hi->a == i){
      return;
    }
    hi = hi->next;
  }
  //first we make a temp node and assign it the value
  struct node* temp = malloc(sizeof(struct node));
  temp->a = i;

  //if the LL is empty or the new value is less than the head, we make it the head
  if(head == NULL || temp->a < head->a){
    temp->next = head;
    head = temp;
  }
  //otherwise we just look for the value greater than the one to be inserted and insert b4 that
  else{
    struct node* ptr = head;
    while(ptr->next != NULL && ptr->next->a < temp->a){
      ptr = ptr->next;
    }
    temp->next = ptr->next;
    ptr->next = temp;
  }
}

  void delete(int i){
    //we need both ptr and prev because we need to modify the previous nodes next
    struct node* ptr = head;
    struct node* prev;

    if(ptr == NULL){
      return;
    }

    //we have to account for the edge case where the head is the node to be deleted
    if(ptr != NULL && ptr->a == i){
      head = ptr->next;
      //c doesnt garbage collect
      free(ptr);
      return;
    }

    //traverse, find, delete
    while(ptr != NULL){
      if(ptr->a == i){
        prev->next = ptr->next;
        free(ptr);
      }
      prev = ptr;
      ptr = ptr->next;
    }
  }
  void print(){
    struct node* temp2 = head;
    int count = 0;
    while(temp2 != NULL){
      count++;
      temp2 = temp2->next;
    }
    printf("%d\n", count);

    struct node* temp = head;
    while(temp != NULL){
      printf("%d\t", temp->a);
      temp = temp->next;
    }
  }

  int main(int argc, char** argv){

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL){
      printf("error");
      exit(0);
    }

    if(feof(fp) == EOF){
      printf("0");
    }

    while(!feof(fp)){
      char ok;
      int val;
      fscanf(fp, "%c %d\n", &ok, &val);
      if(ok == 'i'){
        insert(val);
      }
      else{
        delete(val);
      }
    }



    print();

    struct node* temp = head;
    while(temp != NULL){
      struct node * temp2 = temp;
      temp = temp->next;
      free(temp2);
    }


    fclose(fp);

    return 0;
  }
