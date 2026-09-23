#ifndef __MY_MALLOC_
#define __MY_MALLOC_

#include <stdlib.h>

#define POOL_SIZE 1000000000

typedef struct Bloc {
    size_t taille;
    struct Bloc *suivant;
    struct Bloc *precedent;
    int est_libre;
}Bloc;

Bloc initBlocMem(size_t size);
void* allocation(size_t size, char *pool, Bloc **myList);
void* my_malloc(size_t size);
void my_free(void* ptr);

#endif
