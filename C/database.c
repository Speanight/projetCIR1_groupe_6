#include "database.h"

// Creates an empty Database. (obsolete kind-of, mainly malloc-side)
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

// Builds a whole database thanks to a text file. Most useful function.
struct Database* buildDataBase(char* textFile) {
    FILE* p1;
    p1 = fopen(textFile, "r"); // We open the file at the specified destination.

    if (p1 == NULL) { // If we can't find it, we return NULL.
        printf("error in opening file.\n");
        return NULL;
    }

    struct Database* db = malloc(sizeof(struct Database)); // We initialize a database...

    db->dbTxt = textFile; // We specify where the database is (useful to add more movies to the DB).

    struct List* list [DUREE_MAX]; // We create an array of list.
    for (int i = 0; i < DUREE_MAX; i++) { // We initialize as an empty list at each position.
        list[i] = createEmptyList();
    }

    struct NodeTrie* trie = createEmptyNodeTrie(); // We create an empty trie...
    // Used for movies attributes found in the file.
    char* realisateur;
    char* titre;
    int duree;
    char* genre;
    char* biggestRealisateur = malloc(sizeof(char)*64);
    int biggestRealisateurMovies = 0;
    int compareBiggestRealisateurMovies = 0;
    char* token;
    char line[256];

    while (fgets(line, sizeof(line),p1)) { // While the file isn't finished, line = to each line of the file one by one.
        token = strtok(line, ";"); // We take the first part before the ";"
        realisateur = token; // Initialize realisateurs as it.

        token = strtok(NULL, ";"); // Same for the second part
        titre = token; // We initialize titre.

        token = strtok(NULL, ";"); // Same for third part
        duree = atoi(token); // We initialize duree, and use atoi() to convert the char* to an int.

        token = strtok(NULL, ";"); // Same for the fourth part.
        genre = token; // We initialize genre.
        genre[strlen(genre)-1] = 0; // Used to get rid of the \r and \n at the end of each line.

        struct Movie* m = createMovie(realisateur, titre, duree, genre); // We create a movie with those attributes.
        addFirst(list[duree], m); // We add it in the list at the corresponding place thanks to the variable duree.

        compareBiggestRealisateurMovies = insertMovie(trie, m); // We insert the movie in the trie, and collect the amount of movies made by that person...

        if (compareBiggestRealisateurMovies > biggestRealisateurMovies) { // If the person we just checked made more movies than the last one kept in memory...
            biggestRealisateurMovies = compareBiggestRealisateurMovies; // We replace it as the new "biggest amount of movies"
            strcpy(biggestRealisateur, realisateur); // We replace the new realisateurs with the biggest amount of movies.
        }
    }
    fclose(p1); // We close the file.


    db->nbFilmsDuRealisateurAvecPlusDeFilms = biggestRealisateurMovies; // We put the biggest realisateurs in the database.
    db->realisateurAvecPlusDeFilms = biggestRealisateur;

    for (int i = 0; i < DUREE_MAX; i++) { // We put the entire list in the DB, at triParDuree.
        db->triParDuree[i] = list[i];
    }

    db->triParRealisateurs = trie; // We place the trie in the DB at triParRealisateurs.

    printf("Database built!\n"); // We print to show the DB is done building.

    return db; // We return the database.
}

// Export the realisateurs with the biggest amount of movies, as well as their number of movies.
void exportMostMovies(struct Database* db, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w"); // We open the exportFile specified (or create it if it doesn't exist.).
    fprintf(p1, "%s", db->realisateurAvecPlusDeFilms); // We add the realisateurs with the most movies to the file.
    fprintf(p1, ";"); // We add a semicolon to separate the two values.
    fprintf(p1, "%d", db->nbFilmsDuRealisateurAvecPlusDeFilms); // We add the amount of movies.
    fclose(p1); // Finally, we close the file.
}

// Export the whole database to a file.
void exportWholeDB(struct Database* db, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w"); // We create the file specified by exportFile
    struct List* l = createEmptyList(); // We create an empty list
    struct timespec start; // Start a timer
    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < DUREE_MAX; i++) {
        l = addFromList(l, db->triParDuree[i]); // We add each movie to the list.
    }
    struct timespec end; // We stop the timer.
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // We determine the time taken by the function.
    fprintf(p1, "%fs\n", time_taken); // Shows the time taken in the file.
    unsigned int size = listSize(l); // We take the size of the list.

    char duree[5];

    for (int i = 0; i < size; i++) { // For each element (thanks to the size of the list)...
        fprintf(p1, l->head->movie->titre); // We add each movie to the text file.
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->realisateur);
        fprintf(p1, ";");
        sprintf(duree, "%d", l->head->movie->duree);
        fprintf(p1, duree);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->genre);
        fprintf(p1, "\n");

        l->head = l->head->next; // Then go to the next element.
    }
    fclose(p1); // We close the file.
}

// Export the movies with the selected duration to a file.
void exportFromDuration(struct Database* db, int duration, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w"); // We open the exportFile specified (or create it if it doesn't exist.).
    struct List* l = createEmptyList(); // We create an empty list.
    struct timespec start; // Initialize the start of the timer.
    clock_gettime(CLOCK_MONOTONIC, &start);
    l = addFromList(l, db->triParDuree[duration]); // We add each element with the good duration to the list l.
    struct timespec end; // We stop the timer.
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // Used to calculate the time taken.
    unsigned int size = listSize(l); // We take the size of the list l.
    fprintf(p1, "%fs\n", time_taken); // We add the time taken to the file.

    char duree[5];

    for (int i = 0; i < size; i++) { // We go through the whole list...
        fprintf(p1, l->head->movie->titre); // And add the movie details to the file.
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->realisateur);
        fprintf(p1, ";");
        sprintf(duree, "%d", l->head->movie->duree);
        fprintf(p1, duree);
        fprintf(p1, ";");
        fprintf(p1, l->head->movie->genre);
        fprintf(p1, "\n");

        l->head = l->head->next; // Then, we go to the next element.
    }

    fclose(p1); // And we close the file.
}

// Used to add a movie to the database.
void addMovie(struct Database* db, char* titre, char* realisateur, int duree, char* genre, char* addDB) {
    struct Movie* m = createMovie(realisateur, titre, duree, genre); // We create a movie with the given details...

    addFirst(db->triParDuree[duree], m); // We add the movie at the right place in the tri by duration.
    int compareBiggestRealisateurMovies = insertMovie(db->triParRealisateurs, m); // We insert it to the trie (tri by realisateurs)

    if (compareBiggestRealisateurMovies > db->nbFilmsDuRealisateurAvecPlusDeFilms) { // If the new realisateur has more movies than the one kept by the data base...
        db->nbFilmsDuRealisateurAvecPlusDeFilms = compareBiggestRealisateurMovies; // We update it in the DB.
        strcpy(db->realisateurAvecPlusDeFilms, realisateur);
    }

    int compare = strcmp(addDB, "Y"); // If the attributes state to add it to the database...
    if (compare == 0) {
        FILE *p1;
        p1 = fopen(db->dbTxt, "a"); // We append to the file...
        fprintf(p1, "%s;%s;%d;%s\n", realisateur, titre, duree, genre); // The new movie at the end.
        printf("[Added to the txt database file.]\n");

        fclose(p1); //Then we close the file.
    }
    else {
        printf("[Temporary added!]\n");
    }
}

// Used to export from a specific interval of time.
void exportFromInterval(struct Database* db, int durationMin, int durationMax, char* exportFile) {
    FILE *p1;
    p1 = fopen(exportFile, "w"); // We open (or create) the file specified by exportFile.
    struct List* l = createEmptyList(); // We create an empty list.
    struct timespec start; // Initialize the start of the timer.
    clock_gettime(CLOCK_MONOTONIC, &start);

    if (durationMin > durationMax) { // If the min is shorter than the max...
        return; // We return without anything.
    }

    if (durationMin == durationMax) { // If both the min and the max are equal...
        exportFromDuration(db, durationMin, exportFile); // We use the function exportFromDuration.
        struct timespec end; // We stop the timer.
        clock_gettime(CLOCK_MONOTONIC, &end);
        double time_taken = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // Used to calculate the time taken.
        fprintf(p1, "%fs\n", time_taken); // We add the time taken to the file.
        return;
}

    for (int i = durationMin; i < durationMax+1; i++) { // We take each duration, from the minimum to the maximum...
        l = addFromList(l, db->triParDuree[i]); // We add each element to a list.
    }
    struct timespec end; // We stop the timer.
    clock_gettime(CLOCK_MONOTONIC, &end);
    double time_taken = difftime(end.tv_sec, start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // Used to calculate the time taken.
    fprintf(p1, "%fs\n", time_taken); // We add the time taken to the file.
    unsigned int size = listSize(l); // We take the size of the list...
    char duree[5];

    for (int i = 0; i < size; i++) { // We loop for the size of the list...
        fprintf(p1, l->head->movie->titre); // We add each movie to the file.
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

// Used to delete the whole database with free.
void deleteDataBase(struct Database* db) {
    free(db->realisateurAvecPlusDeFilms); // We free the char* that used malloc.
    db->realisateurAvecPlusDeFilms = NULL; // We set it to null.
    db->nbFilmsDuRealisateurAvecPlusDeFilms = 0; // We set an int to 0
    for (int i = 0; i < DUREE_MAX; i++) { // We delete each list of the tri by duration.
        deleteList(&db->triParDuree[i]);
    }

    deleteNodeTrie(&(db->triParRealisateurs)); // We delete the whole trie.

    free(db); // Finally, we free the database.
}