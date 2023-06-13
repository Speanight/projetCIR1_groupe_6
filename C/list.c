#include "list.h"

// Used to create a cell with a movie.
struct Cell* createCell(struct Movie* movie) {
    struct Cell* c = malloc(sizeof(struct Cell)); // allocating memory...
    if (c != NULL) { // If the malloc is successful...
        c->movie = movie; // We add the movie...
        c->next = NULL; // And set the next one to null.
    }
    return c; // We return the cell.
}

// Used to create an empty list.
struct List* createEmptyList() {
    struct List* l = malloc(sizeof(struct List)); // Allocating memory...
    if (l != NULL) { // If the list isn't null...
        l->size = 0; // Its size is equal to 0
        l->head = NULL; // And the head is null (cause the list is empty).
    }
    return l; // We return the list.
}

// Used to add a movie at the beginning of the list.
void addFirst(struct List* l, struct Movie* movie) {
    struct Cell* c = createCell(movie); // We create a cell with the movie...
    if (c != NULL) {
        c->next = l->head; // We set the next element of the cell as being the head of the list.
        l->head = c; // We set the head of the list as being the cell.
        l->size++; // And add one to the size.
    }
}

// Used to delete the first element.
void deleteFirst(struct List* l) {
    struct Cell* c = l->head; // We define a cell as being the head of the list.
    l->head = l->head->next; // We set the head of the list as being the next element.
    l->size--; // We remove 1 from size.
    deleteMovie(c->movie); // We delete the movie from the cell.
    free(c->movie); // We free the movie.
    free(c); // We free the cell.
}

// Used to determine the size of a list.
unsigned int listSize(struct List* l) {
    return l->size; // We return the size of the list.
}

// Used to delete a list.
void deleteList(struct List** l) {
    unsigned int count =listSize(*l); // We obtain the size of the list.
    for (int i = 0; i < count; i++) { // We loop to go through each element...
        deleteFirst(*l); // We delete the first element each time.
    }
    free(*l); // We free the list once we're done.
}

// Used to "copy" a list to another one.
struct List* addFromList(struct List* result, struct List* toAdd) {
    struct Cell* tempCell = toAdd->head; // We create a cell with the head of the list to add.

    while (tempCell != NULL) { // While the temporary cell isn't null...
        addFirst(result, tempCell->movie); // We add the first element to the result list...
        tempCell = tempCell->next; // And go to the next element.
    }

    return result; // The, we return the result.
}