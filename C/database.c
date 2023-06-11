//
// Created by ADMIN on 6/11/2023.
//

#include "database.h"


struct Database* createEmptyDataBase() {
    struct Database* db = malloc(sizeof(struct Database));

    if (db == NULL) {
        printf("error malloc");
        return NULL;
    }

    db->triParRealisateurs = createEmptyNodeTrie();
    for (int i = 0; i < DUREE_MAX; i++) {
        db->triParDuree[i] = createEmptyList();
    }

    db->realisateurAvecPlusDeFilms = NULL;
    db->nbFilmsDuRealisateurAvecPlusDeFilms = 0;

    return db;
}

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

    char* realisateur = malloc(sizeof(char)*64);
    char* titre = malloc(sizeof(char)*64);
    int duree;
    char* genre = malloc(sizeof(char)*64);

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

struct List* getMoviesByDuration(struct List** list, int duration) {
    return list[duration];
}

void exportFromDuration(struct Database* db, int duration, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w");
    struct List* l = db->triParDuree[duration];
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