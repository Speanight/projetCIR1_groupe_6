//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"
#include "trie.h"
#include "movie.h"
#include "database.h"
#include <time.h>
#include <unistd.h>

int main() {

    char* dbTxt = "../DB/BD_big.txt";
    char* exportTxt = "";

    struct Database* db = buildDataBase(dbTxt); // Creation of the database

    bool endServer = false; // Set to true to avoid the whole loop.
    FILE* ready;
    FILE* request;
    char line[64];
    char* command;
    char* argumentStr;
    int argumentInt;
    int compare;
    char* token;


    while(!endServer) { // Loops while we don't ask to close the server

        request = fopen("../../request.txt", "r"); // We read the file request.txt

        if (request != NULL) { // If it exists...
            fgets(line, sizeof(line), request);
            remove("../../request.txt");
            token = strtok(line, ";"); // We separate the command from the arguments
            command = token;

            compare = strcmp(command, "exportAllFromRealisateurs"); // We compare to know which command is being executed
            if (compare == 0) {
                printf("export from realisateurs!\n"); // We show in the console what we're doing
                argumentStr = strtok(NULL, ";"); // We get the following arguments with strtok
                printf("Argument : %s\n", argumentStr);
                if (argumentStr != NULL) {
                    exportAllFromRealisateurs(db->triParRealisateurs, argumentStr, "../../result.txt");
                }
            }
            else {
                compare = strcmp(command, "endServer");
                if (compare == 0) {
                    endServer = true;
                }
                else {
                    compare = strcmp(command, "exportFromDuration");
                    if (compare == 0) {
                        printf("export from duration!\n");
                        argumentInt = atoi(strtok(NULL, ";"));
                        printf("argumentInt = %d\n", argumentInt);
                        exportFromDuration(db, argumentInt, "../../result.txt");
                    }
                    else {
                        compare = strcmp(command, "realisateurPlusDeFilms");
                        if (compare == 0) {
                            printf("export realisateur avec le plus de films !\n");
                            exportMostMovies(db, "../../result.txt");
                        }
                        else {
                            compare = strcmp(command, "exportWholeDB");
                            if (compare == 0) {
                                printf("export de toute la database !\n");
                                exportWholeDB(db, "../../result.txt");
                                printf("done\n");
                            }
                            else {
                                compare = strcmp(command, "exportFromInterval");
                                if (compare == 0) {
                                    printf("export from interval!\n");
                                    argumentInt = atoi(strtok(NULL, ";"));
                                    int argumentInt2 = atoi(strtok(NULL, ";"));
                                    exportFromInterval(db, argumentInt, argumentInt2, "../../result.txt");
                                }
                                else {
                                    compare = strcmp(command, "addMovie");
                                    if (compare == 0) {
                                        printf("add a movie!\n");
                                        char* titre = strtok(NULL, ";");
                                        char* realisateur = strtok(NULL, ";");
                                        int duree = atoi(strtok(NULL, ";"));
                                        char* genre = strtok(NULL, ";");
                                        char* addDB = strtok(NULL, ";");
                                        addMovie(db, titre, realisateur, duree, genre, addDB);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            fclose(request); // We close the request
            ready = fopen("../../ready.txt", "w"); // We create the file "ready.txt"
            printf("Created ready!\n");
            fclose(ready);
            sleep(1); // We add a small delay for the JS
            remove("../../ready.txt"); // Then we remove ready and loop again
        }
    }

    deleteDataBase(db); // When we ask to end the server, we free the whole database.
}