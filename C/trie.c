#include "trie.h"
#include <stdio.h>
#include <time.h>

// Used to convert a char to an int (using ascii table).
int charToInt(char c) {
    if (c == '-') { // If the char is a -
        return 26; // We return 26 (cause it's not in the alphabet, technically).
    }
    return c-'a'; // Else, we return c-'a'.
}

// Returns the lowercase char.
char* toLower(char* str) {
    int i = 0;
    while (i < strlen(str)) { // For each char in the char*...
        if (str[i] <= 'Z' && str[i] >= 'A') { // If the char is an uppercase letter...
            str[i] = str[i] + 32; // We add 32 to its ascii value (to convert it to a lowercase)
        }
        i++; // We add 1 to i
    }
    return str; // We return the new string.
}

// Gives true if the trie actual is a realisateurs.
bool getIsWord(struct NodeTrie* trie) {
    return trie->isRealisateur;
}

// Creates an empty Trie.
struct NodeTrie* createEmptyNodeTrie() {
    struct NodeTrie* trie = malloc(sizeof(struct NodeTrie)); // We use malloc to initialize it.

    if (trie == NULL) { // If there's a malloc error, we return with NULL.
        printf("error malloc");
        return NULL;
    }

    for (int i = 0; i < ALPHABET; i++) { // For each child in the tree...
        trie->children[i] = NULL; // We initialize the child as NULL.
    }

    trie->isRealisateur = false; // We initialize isRealisateur to false.
    trie->movies = createEmptyList(); // We create an emptyList for the movies...
    return trie; // And return the trie.
}

// Used to insert a movie, also returns the amount of movies of said realisateurs
int insertMovie(struct NodeTrie* trie, struct Movie* m) {
    int i = 0;
    char* realisateur = toLower(m->realisateur); // We lowercase the whole name of realisateurs

    while ((realisateur[i] >= 97 && realisateur[i] <= 123) || realisateur[i] == '-') { // We change the position according to the name for each char.
        int position;
        if (realisateur[i] - 97 >= 0 && realisateur[i] - 97 <= 26) { // If realisateur[i] is a letter in the alphabet...
            position = realisateur[i]-97; // The position will be the ascii code
        }
        else {
            position = 26; // Else, we'll set it to 26
        }
        if (trie->children[position] == NULL) { // If the children at the said position is null...
            trie->children[position] = createEmptyNodeTrie(); // We initialize a new node tree.
        }
        trie = trie->children[position]; // And we go to the said level of the trie
        i++; // We add 1 to i, then start again.
    }
    trie->isRealisateur = true;
    addFirst(trie->movies, m); // We add the movie to the list.

    int ret = trie->movies->size;

    return ret; // We return the number of movies of the realisateur.
}

// Used to find all the movies that start with the char* realisateur.
struct List* findAllMovies(struct NodeTrie* trie, char* realisateur, struct List* result) {
    int i = 0;
    struct NodeTrie* temp = trie; // We create a temporary trie.
    int pos;

    while (i < strlen(realisateur)) { // We go through the whole name of the realisateur.
        pos = charToInt(realisateur[i]); // We convert the char to an int.
        if (temp->children[pos] == NULL) { // If the children is null (doesn't exist)
            return result; // We return nothing
        }
        temp = temp->children[pos]; // Else, we go to said children
        i++; // And starts again by adding 1 to i.
    }
    if (temp->isRealisateur) { // If it's a realisateurs...
        result = addFromList(result, temp->movies); // We add it to the list.
    }
    for (int j = 0; j < ALPHABET; j++) { // We visit the chldren one by one...
        if (temp->children[j] != NULL) { // If one of the children isn't null...
            findAllMovies(temp->children[j], "", result); // We use recursion to find all the movies to those children.
        }
    }
    return result; // We return the list with all the movies.
}

// Used to find the movies that are from the char* realisateur (has to be EXACTLY the same)
struct NodeTrie* findMovies(struct NodeTrie* trie, char* realisateur) {
    int i = 0;
    struct NodeTrie* temp = trie; // We create an empty trie...
    int pos;

    while (i < strlen(realisateur)) { // We visit the whole char*.
        pos = charToInt(realisateur[i]); // We convert the char to an int.
        if (temp->children[pos] == NULL) { // If the children is null...
            return NULL; // We return null.
        }
        temp = temp->children[pos]; // Else, we go to said children.
        i++; // And add 1 to i.
    }
    return temp; // We return temp, which is the trie with all the movies.
}

// Export all the realisateurs to a specified textFile.
void exportAllFromRealisateurs(struct NodeTrie* trie, char* realisateur, char* textFile) {
    struct timespec start; // We start the timer.
    clock_gettime(CLOCK_MONOTONIC, &start);
    struct List* l = createEmptyList(); // We create an empty list
    findAllMovies(trie, realisateur, l); // Find all the movies that correspond to the char* realisateur.
    struct timespec end; // We end the timer.
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // We calculate the difference of time between the end and the start.
    char duree[5];

    FILE *p1;
    p1 = fopen(textFile, "w"); // We open (or create) a file according to the textFile variable.
    fprintf(p1, "%fs\n", time_taken); // We add the time taken at the beginning of the file.

    unsigned int size = listSize(l); // We take the size of the list.
    for (int i = 0; i < size; i++) { // We loop to visit the whole list.
        fprintf(p1, l->head->movie->titre); // We add the movie to the file.
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->realisateur);
        fprintf(p1, ";");
        sprintf(duree, "%d", l->head->movie->duree);
        fprintf(p1, duree);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->genre);
        fprintf(p1, "\n");

        l->head = l->head->next; // We go to the next element.
    }
    fclose(p1); // We close the file.
}

// Deletes and free a NodeTrie.
void deleteNodeTrie(struct NodeTrie** trie) {
    for (int i = 0; i < ALPHABET; i++) { // We go through each children...
        if ((*trie)->children[i] != NULL) { // If it's not set to null...
            deleteNodeTrie(&(*trie)->children[i]); // We use recursion to delete its children.
        }
    }
    // Else...
    int size = listSize((*trie)->movies); // We take the size of the list...
    for (int i = 0; i < size; i++) { // We go through each element...
        struct Cell* c = (*trie)->movies->head; // We take the head in a cell.
        (*trie)->movies->head = (*trie)->movies->head->next; // We point the head to the new head (aka the next element).
        free(c); // We free the cell.
    }
    free((*trie)->movies); // At the end, we free the movies

    free(*trie); // We free the trie.
    *trie = NULL; // We set it to null.
}