//
// Created by ADMIN on 6/9/2023.
//

#ifndef PROJETCIR1_GROUPE_6_MOVIES_H
#define PROJETCIR1_GROUPE_6_MOVIES_H

#include <stdlib.h>

struct Movie {
    char* realisateur;
    char* titre;
    int duree;
    char* genre;
};

struct Movie* createEmptyMovie() {
    struct Movie* m = malloc(sizeof(struct Movie));
    if (m != NULL) {
    }
}

#endif //PROJETCIR1_GROUPE_6_MOVIES_H
