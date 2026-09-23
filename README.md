# MyMalloc-MyFree

Implémentation basique d'un allocateur mémoire en C, en L2.

## Contexte

Ce projet vient d'un TP de L2 où on avait le choix entre deux sujets : un exercice de nettoyage de fichiers ou l'implémentation d'un allocateur mémoire. J'ai pris le second parce que c'est ce qui m'intéressait le plus.

L'idée : refaire `malloc` et `free` à la main, sur un pool mémoire statique, pour comprendre ce qui se passe vraiment derrière ces deux fonctions.

## Ce qui est implémenté

- Pool mémoire statique alloué en zone BSS
- Liste doublement chaînée pour tracker les blocs
- Stratégie **first-fit** pour trouver un bloc libre
- Réutilisation des blocs libérés (marquage `est_libre`)
- Header caché juste avant le pointeur retourné à l'utilisateur (pour retrouver le bloc en O(1) au `free`)
- Programme de test qui alloue/libère aléatoirement 1500 blocs et vérifie l'intégrité mémoire avec un marqueur `0xDEADBEEF`

## Ce qui n'est pas implémenté

Volontairement absent, pour rester au niveau attendu du TP :

- Pas de **coalescing** : deux blocs libres adjacents ne fusionnent pas → fragmentation à long terme
- Pas de **splitting** : réutiliser un bloc de 1000 octets pour une demande de 50 en gaspille 950
- Pas d'**alignement mémoire** explicite
- Pas de gestion multi-thread

Un vrai `malloc` (type `dlmalloc`, `ptmalloc`) fait plusieurs milliers de lignes justement pour gérer ces cas. Ici l'objectif était pédagogique.

## Compilation

```
make
```

## Utilisation

```
./test
```

Le programme lance un stress test : 1500 allocations de taille aléatoire, avec des libérations aléatoires tous les 10 tours, puis un nettoyage final. Détecte les corruptions mémoire.

## Fichiers

- `my_malloc.h` — struct `Bloc` et prototypes
- `my_malloc.c` — implémentation de `my_malloc` / `my_free`
- `test.c` — programme de test
- `Makefile` — compilation
