//
// Created by ADMIN on 6/11/2023.
//

#ifndef C_DICTIONARY_H
#define C_DICTIONARY_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct Dictionary {
    unsigned int size;
    struct dictionaryCell* head;
};

struct dictionaryCell {
    char* realisateur;
    int nbMovies;
    struct dictionaryCell* next;
};


struct dictionaryCell* createEmptyCell();
void addFirstDictionary(char* realisateur, struct Dictionary* d);
struct dictionaryCell* updateCell(char* realisateur);
struct Dictionary* createEmptyDictionary();
void updateDictionary(char* textFile, struct Dictionary* d);

#endif //C_DICTIONARY_H
