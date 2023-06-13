#ifndef PROJETCIR1_GROUPE_6_TRIE_H
#define PROJETCIR1_GROUPE_6_TRIE_H

#define ALPHABET 27

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "movie.h"
#include "list.h"
#include "database.h"

struct NodeTrie {
    struct NodeTrie* children[ALPHABET];
    bool isRealisateur;
    struct List* movies;
};

int charToInt(char c);

char* toLower(char* str);

struct NodeTrie* createEmptyNodeTrie();
int insertMovie(struct NodeTrie* trie, struct Movie* m);
void deleteNodeTrie(struct NodeTrie** trie); // free d'une feuille.

void exportAllFromRealisateurs(struct NodeTrie* trie, char* realisateur, char* textFile);

struct List* findAllMovies(struct NodeTrie* trie, char* realisateur, struct List* result);

#endif //PROJETCIR1_GROUPE_6_TRIE_H
