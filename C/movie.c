//
// Created by ADMIN on 6/9/2023.
//

#include "movie.h"

struct Movie* createEmptyMovie() {
    struct Movie* m = malloc(sizeof(struct Movie));
    if (m != NULL) {
        m->duree = 0;
        m->realisateur = malloc(sizeof(char)*64);
        m->genre = malloc(sizeof(char)*64);
        m->titre = malloc(sizeof(char)*64);
    }
}

struct Movie* createMovie(char* realisateur, char* titre, int duree, char* genre) {
    struct Movie* m = createEmptyMovie();
    strcpy(m->realisateur, realisateur);
    strcpy(m->titre, titre);
    m->duree = duree;
    strcpy(m->genre, genre);
    return m;
}

struct Movie* deleteMovie(struct Movie* m) {
    free(m->titre);
    m->titre = NULL;
    free(m->realisateur);
    m->realisateur = NULL;
    free(m->genre);
    m->genre = NULL;
    m->duree = 0;
    free(m);
    m = NULL;

    // Enlever 1 à size !
}