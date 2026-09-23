#include <stddef.h>
#include <stdio.h>

#include "my_malloc.h"

Bloc initBlocMem(size_t size){
    Bloc new;

    new.precedent = NULL;
    new.suivant = NULL;
    new.taille = size;
    new.est_libre = 0;

    return new;
}

static char _mem_pool[POOL_SIZE];
static Bloc *myList = NULL;

void* allocation(size_t size, char *pool, Bloc **myList){
    void* ptrFinal = NULL;
    //test des cas speciaux
    if (!pool) {printf("Pool inexistant"); return NULL;}
    if (size >= POOL_SIZE) {printf("Pool trop petit"); return NULL;}
    if (!myList) return NULL;
        //Si le pool est vide
    if (!*myList) {
        Bloc *new = (Bloc*)pool;
        *new = initBlocMem(size);
        *myList = new;

        ptrFinal = &(*(new+1));
    }
    //si le pool n'est pas vide
    else{
        Bloc *tmp = *myList;
        Bloc *dernier = NULL;

        while (tmp) {
            if (tmp->est_libre && tmp->taille >= size) {
                tmp->est_libre = 0; // On le réoccupe !
                return (void*)(tmp + 1);
            }
            dernier = tmp;
            tmp = tmp->suivant;
        }
        char* newAdresse = (char*)dernier + sizeof(Bloc) + dernier->taille;
        if (newAdresse + sizeof(Bloc) + size > pool + POOL_SIZE) return NULL;

        Bloc *new = (Bloc*)newAdresse;

        *new = initBlocMem(size);
        new->est_libre = 0;

        dernier->suivant = new;
        new->precedent = dernier;

        ptrFinal = &(*(new+1));
    }

  return ptrFinal;
}

void* my_malloc(size_t size){
  void *adresse = NULL;
  adresse = allocation(size, _mem_pool, &myList);
  return adresse;
}

void my_free(void* ptr){
    if (ptr == NULL || myList == NULL) return;
    Bloc *cible = (Bloc*)ptr - 1;
    cible->est_libre = 1;
}
