//
// Created by ADMIN on 6/9/2023.
//

#include "movie.h"

struct Movie* createEmptyMovie() {
    struct Movie* m = malloc(sizeof(struct Movie));
    if (m != NULL) {
        m->duree = 0;
    }
}

struct Movie* createMovie(char* realisateur, char* titre, int duree, char* genre) {
    struct Movie* m = createEmptyMovie();
    m->realisateur = realisateur;
    m->titre = titre;
    m->duree = duree;
    m->genre = genre;

    return m;
}