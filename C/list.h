//
// Created by ADMIN on 6/9/2023.
//

#ifndef PROJETCIR1_GROUPE_6_LIST_H
#define PROJETCIR1_GROUPE_6_LIST_H

#include "movie.h"

struct Cell {
    struct Movie* movie;
    struct Cell* next;
};

struct List {
    unsigned int size;
    struct Cell* head;
};

struct Cell* createCell(struct Movie* movie);
struct List* createEmptyList();
void addFirst(struct List* l, struct Movie* movie);
bool isListEmpty(struct List* l);
struct Movie* getItemPos(struct List* l, unsigned int position, bool* valid);
void deleteFirst(struct List* l);
void printMovies(struct List* l);
unsigned int listSize(struct List* l);
void addItemPos(struct List* l, struct Movie* movie, unsigned int position, bool* valid);
void deleteItemPos(struct List* l, unsigned int position, bool* valid);
void deleteList(struct List** l);
struct List* createListFromArray(int A[], unsigned int size);
struct Cell* belongs(struct List* l, struct Movie* movie);
void reverse(struct List* l);

#endif //PROJETCIR1_GROUPE_6_LIST_H
