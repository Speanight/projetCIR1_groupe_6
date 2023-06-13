#ifndef PROJETCIR1_GROUPE_6_MOVIE_H
#define PROJETCIR1_GROUPE_6_MOVIE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Movie {
    char* realisateur;
    char* titre;
    int duree;
    char* genre;
};

struct Movie* createEmptyMovie();

struct Movie* createMovie(char* realisateur, char* titre, int duree, char* genre);

void deleteMovie(struct Movie* m);

#endif //PROJETCIR1_GROUPE_6_MOVIE_H
