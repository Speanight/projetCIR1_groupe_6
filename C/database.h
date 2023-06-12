//
// Created by ADMIN on 6/11/2023.
//

#ifndef C_DATABASE_H
#define C_DATABASE_H
#define DUREE_MAX 1200

#include "trie.h"
#include "movie.h"

struct Database {
    struct NodeTrie* triParRealisateurs;
    struct List* triParDuree [DUREE_MAX];
    char* realisateurAvecPlusDeFilms;
    int nbFilmsDuRealisateurAvecPlusDeFilms;
};

struct Database* createEmptyDataBase();
struct Database* createDataBase(char* textFile);
void buildMoviesByDuration(struct Database* db, char* textFile);
struct List* getMoviesByDuration(struct List** list, int duration);

struct Database* buildDataBase(char* textFile);

void exportFromDuration(struct Database* db, int duration, char* exportFile);

void deleteDataBase(struct Database* db);

#endif //C_DATABASE_H
