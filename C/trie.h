#ifndef PROJETCIR1_GROUPE_6_TRIE_H
#define PROJETCIR1_GROUPE_6_TRIE_H

#define ALPHABET 26
#define MAX_REALISATEUR_SIZE 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

struct NodeTrie {
    struct NodeTrie* children[ALPHABET];
    bool isRealisateur;
};

int charToInt(char c);

bool lastLetter(struct NodeTrie* trie);
bool getIsWord(struct NodeTrie* trie);

struct NodeTrie* buildTrieFromFile(char* nameFile);

struct NodeTrie* createEmptyNodeTrie();
void insertWord(struct NodeTrie* trie, char* word);
void deleteWord(struct NodeTrie* trie, char* word);
bool findWord(struct NodeTrie* trie, char* word);
void deleteNodeTrie(struct NodeTrie** trie);     // free d'une feuille.
unsigned int numberOfWords(struct NodeTrie* trie);
void deleteTrie(struct NodeTrie* tree);
void displayDict(struct NodeTrie* trie, char* actualWord, int index);

void writeWord(struct NodeTrie* trie);

#endif //PROJETCIR1_GROUPE_6_TRIE_H
