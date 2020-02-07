#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int cacheMiss;
int cacheHit;
int memoryRead;
int memoryWrite;

int timeG = 1;

typedef struct CacheBlock{
  unsigned int valid;
  unsigned long int tag;
  unsigned int time;
} CacheBlock;

int isPowerOfTwo(int);
int isValid(int, int, char*, char*);
int searchCache(CacheBlock**, size_t, int, int, int, char*);
void insertCache(CacheBlock**, size_t, int, int, int);

int isPowerOfTwo(int n){
  if (n == 0) 
    return 0; 
  while (n != 1) 
  { 
      if (n%2 != 0) 
         return 0; 
      n = n/2; 
  } 
  return 1; 
}

int isValid(int cS, int bS, char* cP, char* a){
  if(isPowerOfTwo(cS) == 0 || isPowerOfTwo(bS) == 0){
    return 0;
  }
  if(!(strcmp(cP, "fifo") == 0 || strcmp(cP, "lru") == 0)){
    return 0;
  }
  if(!(strcmp(a, "direct") == 0 || strcmp(a, "assoc") == 0 || strcmp(a, "assoc:") > 0)){
    return 0;
  }
  if((strcmp(a, "assoc:") > 0) && (strcmp(a, "direct") != 0)){
    char n[strlen(a) - 6];
    int j = 0;
    for(int i = 6; i< strlen(a); i++){
      n[j] = a[i];
      j++;
    }
    if(isPowerOfTwo(atoi(n)) == 0)
      return 0;
  }
  return 1;
}

int searchCache(CacheBlock** c, size_t a, int s, int b, int bS, char* cP){
  int num_set_bits = floor(log2(s));
  int num_block_bits = floor(log2(bS));
  int Mask = (1 << num_set_bits) - 1;

  unsigned int set_index = (a >> num_block_bits) & Mask;
  unsigned long tag = (a >> num_block_bits) >> num_set_bits;

  int hit = 0;

  for(int i = 0; i < b; i++){
    if(c[set_index][i].tag == tag){
      hit = 1;
        if(strcmp("lru", cP) == 0){
          c[set_index][i].time = timeG;
          timeG++;
        }
    }
  }

  return hit;
}

void insertCache(CacheBlock** c, size_t a, int s, int b, int bS){
  int num_set_bits = floor(log2(s));
  int num_block_bits = floor(log2(bS));
  int Mask = (1 << num_set_bits) - 1;

  unsigned int set_index = (a >> num_block_bits) & Mask;
  unsigned long tag = (a >> num_block_bits) >> num_set_bits;

  int block = 0;
  int minTime = c[set_index][0].time;

  for(int i = 0; i< b; i++){
    if(c[set_index][i].time < minTime){
      minTime = c[set_index][i].time;
      block = i;
    }
  }

  c[set_index][block].tag = tag;
  c[set_index][block].time = timeG;
  c[set_index][block].valid++;
  timeG++;
  
}

int main(int argc, char** argv){

  int cacheSize = atoi(argv[1]);
  int blockSize = atoi(argv[2]);
  char* cachePolicy = argv[3];
  char* associativity = argv[4];
  int prefetchSize = atoi(argv[5]);
  FILE* fp = fopen(argv[6], "r");
  
  if(isValid(cacheSize, blockSize, cachePolicy, associativity) == 0){
     printf("error");
     exit(0);
  }

  if(prefetchSize < 0){
    printf("error");
    exit(0);
  }

  if(fp == NULL){
    printf("error");
    exit(0);
  }

  CacheBlock** cache;

  unsigned int sets;
  unsigned int blocks;

  if(strcmp(associativity, "direct") == 0){
    blocks = 1;
    sets = cacheSize/blockSize;
  }

  if(strcmp(associativity, "assoc") == 0){
    sets = 1;
    blocks = cacheSize/blockSize;
  }

  if((strcmp(associativity, "assoc:") > 0) && (strcmp(associativity, "direct") != 0)){
    char n[strlen(associativity) - 6];
    int j = 0;
    for(int i = 6; i< strlen(associativity); i++){
      n[j] = associativity[i];
      j++;
    }
    blocks = atoi(n);
    sets = cacheSize/(atoi(n) * blockSize);
  }


  cache = malloc(sets * sizeof(CacheBlock*));
  for(int i = 0; i<sets; i++){
    cache[i] = malloc(blocks* sizeof(CacheBlock));
  }

  char access;
  size_t address;

  while(fscanf(fp, "%c %zx\n", &access, &address) != EOF){
        if(access == '#')
          break;
        if (access == 'W')
            memoryWrite++;
        int there = searchCache(cache, address, sets, blocks, blockSize, cachePolicy);
        if(there == 1){
          cacheHit++;
          continue;
        }
        else{
          cacheMiss++;
          memoryRead++;
          insertCache(cache, address, sets, blocks, blockSize);
        }
  }

  printf("no-prefetch\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", memoryRead, memoryWrite, cacheHit, cacheMiss);

//prefetch 
  memoryRead = 0;
  memoryWrite = 0;
  cacheHit = 0;
  cacheMiss = 0;
  timeG = 1;
  rewind(fp);
  for(int i = 0; i < sets; i++)
    free(cache[i]);
  free(cache);
  cache = malloc(sets * sizeof(CacheBlock*));
  for(int i = 0; i<sets; i++){
    cache[i] = malloc(blocks* sizeof(CacheBlock));
  }

  while(fscanf(fp, "%c %zx\n", &access, &address) != EOF){
    if(access == '#')
      break;
    if (access == 'W')
      memoryWrite++;
    int there = searchCache(cache, address, sets, blocks, blockSize, cachePolicy);
    if(there == 1){
      cacheHit++;
      continue;
    }
    else{
      cacheMiss++;
      memoryRead++;
      insertCache(cache, address, sets, blocks, blockSize);

      //prefetch code
      size_t prefetch_address = address;
      for(int i = 0; i< prefetchSize; i++){
        prefetch_address = prefetch_address + blockSize;
        int thereP = searchCache(cache, prefetch_address, sets, blocks, blockSize, "fifo");
        if(thereP == 0){
          memoryRead++;
          insertCache(cache, prefetch_address, sets, blocks, blockSize);
        }
      }
    }
  }

  printf("with-prefetch\nMemory reads: %d\nMemory writes: %d\nCache hits: %d\nCache misses: %d\n", memoryRead, memoryWrite, cacheHit, cacheMiss);

  for(int i = 0; i < sets; i++)
    free(cache[i]);
  free(cache);
  fclose(fp);

  return 0;
}
