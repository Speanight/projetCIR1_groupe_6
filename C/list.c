//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"

struct Cell* createCell(struct Movie* movie) {
    struct Cell* c = malloc(sizeof(struct Cell));
    if (c != NULL) {
        c->movie = movie;
        c->next = NULL;
    }
    return c;
}

struct List* createEmptyList() {
    struct List* l = malloc(sizeof(struct List));
    if (l != NULL) {
        l->size = 0;
        l->head = NULL;
    }
    return l;
}

void addFirst(struct List* l, struct Movie* movie) {
    struct Cell* c = createCell(movie);
    if (c != NULL) {
        c->next = l->head;
        l->head = c;
        l->size++;
    }
}

bool isListEmpty(struct List* l) {
    return l->size == 0;
}

struct Movie* getItemPos(struct List* l, unsigned int position, bool* valid) {
    unsigned int size = listSize(l);
    if (position >= size) {
        *valid = false;
        return 0;
    }
    struct Cell* temp = l->head;
    for (int i = 0; i < position; i++) {
        temp = temp->next;
    }
    struct Movie* movie = temp->movie;
    *valid = true;
    return movie;
}

void deleteFirst(struct List* l) {
    struct Cell* c = l->head;
    l->head = l->head->next;
    l->size--;
    deleteMovie(c->movie);
//    if (c->movie != NULL) {
//        free(c->movie);
//    }
    free(c->movie);
    free(c);
}

void printMovies(struct List* l) {
    if (listSize(l) == 0) {
        printf("NULL\n");
        return;
    }
    struct Cell* temp = l->head;

    unsigned int size = listSize(l);
    for (int i = 0; i < size; i++) {
        printf("%s;%s;%d;%s\n", temp->movie->titre, temp->movie->realisateur, temp->movie->duree, temp->movie->genre);
        temp = temp->next;
    }
    printf("NULL\n");
    free(temp);
}

unsigned int listSize(struct List* l) {
    return l->size;
}

void addItemPos(struct List* l, struct Movie* movie, unsigned int position, bool* valid) {
    unsigned int size = listSize(l);

    if (position > size) {
        *valid = false;
        return;
    }

    if (position == 0) {
        addFirst(l, movie);
        *valid = true;
        return;
    }

    struct Cell* temp = l->head;
    struct Cell* tempMax = l->head;
    struct Cell* val = createCell(movie);

    for (int i = 0; i < position; i++) {
        if (i == position-1) {
            tempMax = tempMax->next;
            temp->next = val; // val must contain the value "value" received by the function!
            val->next = tempMax;
        }
        if (temp == NULL) {
            *valid = false;
        }
        else {
            tempMax = tempMax->next; // Used to change the value of the next element.
            temp = temp->next;
        }
    }
    *valid = true;
//    free(val);
//    free(tempMax);
//    free(temp);

    l->size++;
}

void deleteItemPos(struct List* l, unsigned int position, bool* valid) {
    if (l == NULL || listSize(l) == 0) {
        *valid = false;
        return;
    }
    if (position == 0) {
        *valid = true;
        deleteFirst(l);
        return;
    }
    else {
        struct Cell* iter = l->head;
        struct Cell* suprCell;

        for (int i = 0; i < position - 1; i++) { // go to the "position-1" cell
            if (iter->next == NULL) { // if there's no more cell
                *valid = false;
                return;
            }
            iter = iter->next;
        }
        suprCell = iter->next;
        iter->next = iter->next->next;
        free(suprCell);
    }
    l->size--;
    *valid = true;
}

void deleteList(struct List** l) {
    unsigned int count =listSize(*l);
    for (int i = 0; i < count; i++) {
        deleteFirst(*l);
    }
    free(*l);
}

struct List* createListFromArray(int A[], unsigned int size) {
    if (size == 0) {
        return NULL;
    }

    struct List* l = createEmptyList();

    for (int i = size; i > 0; i--) {
        addFirst(l, A[i-1]);
    }

    return l;
}

struct Cell* belongs(struct List* l, struct Movie* movie) {
    struct Cell* temp = l->head;
    unsigned int size = l->size;

    for (int i = 0; i < size; i++) {
        if (temp->movie == movie) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void reverse(struct List* l) {
    bool valid = true;
    int size = listSize(l);

    for (int i = 0; i < size; i++) {
        addFirst(l, getItemPos(l, i, &valid));
        deleteItemPos(l, i+1, &valid);
    }
}

struct List* addFromList(struct List* result, struct List* toAdd) {
    struct Cell* tempCell = toAdd->head;

    while (tempCell != NULL) {
        addFirst(result, tempCell->movie);
        tempCell = tempCell->next;
    }

    return result;
}