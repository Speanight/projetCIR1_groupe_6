//
// Created by ADMIN on 6/9/2023.
//

#include "movie.h"

// Creates an empty movie.
struct Movie* createEmptyMovie() {
    struct Movie* m = malloc(sizeof(struct Movie));
    if (m != NULL) {
        m->duree = 0;
        m->realisateur = malloc(sizeof(char)*64);
        m->genre = malloc(sizeof(char)*64);
        m->titre = malloc(sizeof(char)*64);
    }

    return m;
}

// Creates a movie according to the arguments
struct Movie* createMovie(char* realisateur, char* titre, int duree, char* genre) {
    struct Movie* m = createEmptyMovie();
    strcpy(m->realisateur, realisateur); // Strcpy to not lose the value with malloc and all.
    strcpy(m->titre, titre);
    m->duree = duree;
    strcpy(m->genre, genre);
    return m; // We return the movie.
}

// Used to delete a movie
void deleteMovie(struct Movie* m) {
    free(m->titre); // We free each string...
    m->titre = NULL;
    free(m->realisateur);
    m->realisateur = NULL;
    free(m->genre);
    m->genre = NULL;
    m->duree = 0;
    m = NULL;

    // Enlever 1 à size ! - Non nécessaire : delete d'un seul movie non effectué.
}