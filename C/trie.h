#ifndef PROJETCIR1_GROUPE_6_TRIE_H
#define PROJETCIR1_GROUPE_6_TRIE_H

#define ALPHABET 27
#define MAX_REALISATEUR_SIZE 64
#define MAX_GENRE_SIZE 24
#define MAX_TITRE_SIZE 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "movie.h"
#include "list.h"

struct NodeTrie {
    struct NodeTrie* children[ALPHABET];
    bool isRealisateur;
    struct List* movies;
};

int charToInt(char c);

bool lastLetter(struct NodeTrie* trie);
bool getIsWord(struct NodeTrie* trie);
char* toLower(char* str);

struct NodeTrie* buildTrieFromFile(char* nameFile);

struct NodeTrie* createEmptyNodeTrie();
void insertMovie(struct NodeTrie* trie, struct Movie* m);
void deleteWord(struct NodeTrie* trie, char* word);
struct List* findMovies(struct NodeTrie* trie, char* realisateur);
void deleteNodeTrie(struct NodeTrie** trie);     // free d'une feuille.
unsigned int numberOfWords(struct NodeTrie* trie);
void deleteTrie(struct NodeTrie* tree);
void displayDict(struct NodeTrie* trie, char* actualWord, int index);


void exportFromRealisateurs(struct NodeTrie* trie, char* realisateur, char* textFile);
void writeWord(struct NodeTrie* trie);

#endif //PROJETCIR1_GROUPE_6_TRIE_H
