#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "my_malloc.h"

#define MAX_ALLOC 1500

int main(void) {
    unsigned long int* ptrs[MAX_ALLOC] = {NULL};
    int i;

    srand(time(NULL));

    for (i = 0; i < MAX_ALLOC; i++) {
        size_t size = (rand() % 1000) + 1;
        ptrs[i] = my_malloc(size);

        if (ptrs[i] == NULL) {
            fprintf(stderr, "Tour %d : Echec allocation pour %zu octets\n", i, size);
        } else {
            *ptrs[i] = 0xDEADBEEF;
            fprintf(stderr, "Tour %d : Adr accordée : %p\n", i, (void*)ptrs[i]);

            if (*ptrs[i] != 0xDEADBEEF) {
                printf("CORRUPTION DETECTEE au tour %d !\n", i);
                return 1;
            }
        }

        if (i > 0 && i % 10 == 0) {
            int index_to_free = rand() % i;
            if (ptrs[index_to_free] != NULL) {
                fprintf(stderr, "          Libération aléatoire du tour %d\n", index_to_free);
                my_free(ptrs[index_to_free]);
                ptrs[index_to_free] = NULL;
            }
        }
    }

    printf("\nNettoyage final de tous les blocs restants...\n");
    for (i = 0; i < MAX_ALLOC; i++) {
        if (ptrs[i] != NULL) {
            my_free(ptrs[i]);
        }
    }

    printf("Test terminé avec succès !\n");
    return 0;
}
