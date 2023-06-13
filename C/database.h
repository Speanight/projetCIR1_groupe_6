#ifndef C_DATABASE_H
#define C_DATABASE_H
#define DUREE_MAX 1200

#include "trie.h"
#include "movie.h"
#include <time.h>

struct Database {
    struct NodeTrie* triParRealisateurs;
    struct List* triParDuree [DUREE_MAX];
    char* realisateurAvecPlusDeFilms;
    char* dbTxt;
    int nbFilmsDuRealisateurAvecPlusDeFilms;
};

struct Database* createEmptyDataBase();
void exportMostMovies(struct Database* db, char* exportFile);

void addMovie(struct Database* db, char* titre, char* realisateur, int duree, char* genre, char* addDB);

void exportWholeDB(struct Database* db, char* exportFile);
void exportFromInterval(struct Database* db, int durationMin, int durationMax, char* exportFile);

struct Database* buildDataBase(char* textFile);

void exportFromDuration(struct Database* db, int duration, char* exportFile);

void deleteDataBase(struct Database* db);

#endif //C_DATABASE_H
