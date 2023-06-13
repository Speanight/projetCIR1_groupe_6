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
void deleteFirst(struct List* l);
unsigned int listSize(struct List* l);
void deleteList(struct List** l);

struct List* addFromList(struct List* result, struct List* toAdd);

#endif //PROJETCIR1_GROUPE_6_LIST_H
