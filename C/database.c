//
// Created by ADMIN on 6/11/2023.
//

#include "database.h"

// Creates an empty Database. (obsolete kind-of)
struct Database* createEmptyDataBase() {
    struct Database* db = malloc(sizeof(struct Database));

    // If malloc returns an error.
    if (db == NULL) {
        printf("error malloc");
        return NULL;
    }

    db->triParRealisateurs = createEmptyNodeTrie(); // We initialize a Trie for the realisateurs
    for (int i = 0; i < DUREE_MAX; i++) { // We initialize a list for each place in the array.
        db->triParDuree[i] = createEmptyList();
    }

    db->realisateurAvecPlusDeFilms = NULL;
    db->nbFilmsDuRealisateurAvecPlusDeFilms = 0;

    return db;
}

// Adds all movies based on a duration.
void buildMoviesByDuration(struct Database* db, char* textFile) {
    FILE* p1;
    p1 = fopen(textFile, "r");

    if (p1 == NULL) {
        printf("error in opening file.\n");
        return;
    }

    struct List* list [DUREE_MAX];
    for (int i = 0; i < DUREE_MAX; i++) {
        list[i] = malloc(sizeof(struct List));
        list[i] = createEmptyList();
    }

    char* realisateur;
    char* titre;
    int duree;
    char* genre;

    int i = 0;
    char* token;
    char line[256];

    while (fgets(line, sizeof(line),p1)) {
        token = strtok(line, ";");
        realisateur = token;

        token = strtok(NULL, ";");
        titre = token;

        token = strtok(NULL, ";");
        duree = atoi(token);

        token = strtok(NULL, ";");
        genre = token;
        genre[strlen(genre)-2] = 0; // Used to get rid of the \r and \n.

        struct Movie* m = createMovie(realisateur, titre, duree, genre);
        addFirst(list[duree], m);
    }
    fclose(p1);

    for (int i = 0; i < DUREE_MAX; i++) {
        db->triParDuree[i] = list[i];
    }
}

//void getRealisateursWithMostMovies(struct Database* db, char* textFile) {
//    FILE* p1;
//    p1 = fopen(textFile, "r");
//
//    if (p1 == NULL) {
//        printf("error in opening file.\n");
//        return;
//    }
//
//    struct Nodetrie* trie = createEmptyNodeTrie();
//    char* realisateur = malloc(sizeof(char)*64);
//    char* titre = malloc(sizeof(char)*64);
//    int duree;
//    char* genre = malloc(sizeof(char)*64);
//
//    int i = 0;
//    char* token;
//    char line[256];
//
//    while (fgets(line, sizeof(line),p1)) {
//        token = strtok(line, ";");
//        realisateur = token;
//
//        token = strtok(NULL, ";");
//        titre = token;
//
//        token = strtok(NULL, ";");
//        duree = atoi(token);
//
//        token = strtok(NULL, ";");
//        genre = token;
//        genre[strlen(genre)-2] = 0; // Used to get rid of the \r and \n.
//
//        struct Movie* m = createMovie(realisateur, titre, duree, genre);
//
//        insertMovie(trie, m);
//
//
//    }
//    fclose(p1);
//
//    return trie;
//}

struct Database* createDataBase(char* textFile) {
    struct Database* db = createEmptyDataBase();
    db->triParRealisateurs = buildTrieFromFile(textFile, db);
    buildMoviesByDuration(db, textFile);

    return db;
}

struct Database* buildDataBase(char* textFile) {
    FILE* p1;
    p1 = fopen(textFile, "r");

    if (p1 == NULL) {
        printf("error in opening file.\n");
        return NULL;
    }


    struct Database* db = malloc(sizeof(struct Database));

    db->dbTxt = textFile;

    struct List* list [DUREE_MAX];
    for (int i = 0; i < DUREE_MAX; i++) {
//        list[i] = malloc(sizeof(struct List));
        list[i] = createEmptyList();
    }

    struct NodeTrie* trie = createEmptyNodeTrie();
    char* realisateur;
    char* titre;
    int duree;
    char* genre;

    char* biggestRealisateur = malloc(sizeof(char)*64);
    int biggestRealisateurMovies = 0;
    int compareBiggestRealisateurMovies = 0;

    char* token;
    char line[256];

    while (fgets(line, sizeof(line),p1)) {
        token = strtok(line, ";");
        realisateur = token;

        token = strtok(NULL, ";");
        titre = token;

        token = strtok(NULL, ";");
        duree = atoi(token);

        token = strtok(NULL, ";");
        genre = token;
        genre[strlen(genre)-2] = 0; // Used to get rid of the \r and \n.

        struct Movie* m = createMovie(realisateur, titre, duree, genre);
        addFirst(list[duree], m);

        compareBiggestRealisateurMovies = insertMovie(trie, m);

        if (compareBiggestRealisateurMovies > biggestRealisateurMovies) {
            biggestRealisateurMovies = compareBiggestRealisateurMovies;
            strcpy(biggestRealisateur, realisateur);
        }
    }

    printf("%s -> %d\n", biggestRealisateur, biggestRealisateurMovies);
    fclose(p1);


    db->nbFilmsDuRealisateurAvecPlusDeFilms = biggestRealisateurMovies;
    db->realisateurAvecPlusDeFilms = biggestRealisateur;


    for (int i = 0; i < DUREE_MAX; i++) {
        db->triParDuree[i] = list[i];
    }

    db->triParRealisateurs = trie;


//    free(biggestRealisateur);

    return db;
}



struct List* getMoviesByDuration(struct List** list, int duration) {
    return list[duration];
}

void exportMostMovies(struct Database* db, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w");
    fprintf(p1, "%s", db->realisateurAvecPlusDeFilms);
    printf("%s\n", db->realisateurAvecPlusDeFilms);
    fprintf(p1, ";");
    fprintf(p1, "%d", db->nbFilmsDuRealisateurAvecPlusDeFilms);

    fclose(p1);
}

void exportWholeDB(struct Database* db, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w");
    struct List* l = createEmptyList();
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < DUREE_MAX; i++) {
        l = addFromList(l, db->triParDuree[i]);
    }
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    fprintf(p1, "%fs\n", time_taken);
    unsigned int size = listSize(l);

    char duree[5];

    for (int i = 0; i < size; i++) {
        fprintf(p1, l->head->movie->titre);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->realisateur);
        fprintf(p1, ";");
        sprintf(duree, "%d", l->head->movie->duree);
        fprintf(p1, duree);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->genre);
        fprintf(p1, "\n");

        l->head = l->head->next;
    }

    fclose(p1);
}

void exportFromDuration(struct Database* db, int duration, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w");
    struct List* l = createEmptyList();
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    l = addFromList(l, db->triParDuree[duration]);
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
//    struct List* l = db->triParDuree[duration];
    unsigned int size = listSize(l);

    char duree[5];

    fprintf(p1, "%fs\n", time_taken);
    for (int i = 0; i < size; i++) {
        fprintf(p1, l->head->movie->titre);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->realisateur);
        fprintf(p1, ";");
        sprintf(duree, "%d", l->head->movie->duree);
        fprintf(p1, duree);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->genre);
        fprintf(p1, "\n");

        l->head = l->head->next;
    }

    fclose(p1);
}

void addMovie(struct Database* db, char* titre, char* realisateur, int duree, char* genre, char* addDB) {
    struct Movie* m = createMovie(realisateur, titre, duree, genre);

    addFirst(db->triParDuree[duree], m);
    int compareBiggestRealisateurMovies = insertMovie(db->triParRealisateurs, m);

    if (compareBiggestRealisateurMovies > db->nbFilmsDuRealisateurAvecPlusDeFilms) {
        db->nbFilmsDuRealisateurAvecPlusDeFilms = compareBiggestRealisateurMovies;
        strcpy(db->realisateurAvecPlusDeFilms, realisateur);
    }

    if (addDB == NULL) {
        return;
    }

    int compare = strcmp(addDB, "Y");
    if (compare == 0) {
        FILE *p1;
        p1 = fopen(db->dbTxt, "a");
        fprintf(p1, "%s;%s;%d;%s\n", realisateur, titre, duree, genre);

        fclose(p1);
    }
}

void exportFromInterval(struct Database* db, int durationMin, int durationMax, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w");
    struct List* l = createEmptyList();

    for (int i = durationMin; i < durationMax+1; i++) {
        l = addFromList(l, db->triParDuree[i]);
    }
    unsigned int size = listSize(l);
    char duree[5];

    for (int i = 0; i < size; i++) {
        fprintf(p1, l->head->movie->titre);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->realisateur);
        fprintf(p1, ";");
        sprintf(duree, "%d", l->head->movie->duree);
        fprintf(p1, duree);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->genre);
        fprintf(p1, "\n");

        l->head = l->head->next;
    }

    fclose(p1);
}

//void deleteMovieFromDetails(struct Database* db, char* titre, char* realisateur, int duree, char* genre) {
//    struct List* l = db->triParDuree[duree];
//    printf("titre : %s - l->movie->titre : %s\n", titre, l->head->movie->titre);
//
//    int compare;
//    int size = l->size;
//    for (int i = 0; i < size; i++) {
//        compare = strcmp(l->head->movie->titre, titre);
//        if (compare == 0) {
//            compare = strcmp(l->head->movie->realisateur, realisateur);
//            if (compare == 0) {
//                compare = strcmp(l->head->movie->genre, genre);
//                if (compare == 0) {
//                    struct Cell *c = l->head;
//                    l->head = l->head->next;
//                    deleteMovie(c->movie);
//                    free(c);
//                    return;
//                }
//            }
//        }
//        l->head = l->head->next;
//    }
//}

void deleteDataBase(struct Database* db) {
    free(db->realisateurAvecPlusDeFilms);
    db->realisateurAvecPlusDeFilms = NULL;
    db->nbFilmsDuRealisateurAvecPlusDeFilms = NULL;
    for (int i = 0; i < DUREE_MAX; i++) {
        deleteList(&db->triParDuree[i]);
    }

    deleteNodeTrie(&(db->triParRealisateurs));

    free(db);
}