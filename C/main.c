#include "trie.h"
#include "movie.h"
#include "database.h"
#include <unistd.h>

int main() {

    // Change the following according to your preferences:
    char* dbTxt = "../DB/BD_medium.txt"; // The database you want to open.
    char* exportTxt = "../../htmlweb/result.txt"; // The file where the result will be sent (read by the web page, put that in the same directory folder as the html!)
    char* readyTxt = "../../htmlweb/ready.txt"; // The file stating the result is ready (read by the web page, put that in the same directory folder as the html!)
    char* requestTxt = "../../htmlweb/request.txt"; // The file read by the C program, having the request (read by the C program, but downloaded from the web page!)

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

        request = fopen(requestTxt, "r"); // We read the file request.txt

        if (request != NULL) { // If it exists...
            fgets(line, sizeof(line), request);
            remove(requestTxt);
            token = strtok(line, ";"); // We separate the command from the arguments
            command = token;

            compare = strcmp(command, "exportAllFromRealisateurs"); // We compare to know which command is being executed
            if (compare == 0) {
                printf("export from realisateurs!\n"); // We show in the console what we're doing
                argumentStr = strtok(NULL, ";"); // We get the following arguments with strtok
                printf("Argument : %s\n", argumentStr);
                if (argumentStr != NULL) {
                    exportAllFromRealisateurs(db->triParRealisateurs, argumentStr, exportTxt);
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
                        exportFromDuration(db, argumentInt, exportTxt);
                    }
                    else {
                        compare = strcmp(command, "realisateurPlusDeFilms");
                        if (compare == 0) {
                            printf("export realisateur avec le plus de films !\n");
                            exportMostMovies(db, exportTxt);
                        }
                        else {
                            compare = strcmp(command, "exportWholeDB");
                            if (compare == 0) {
                                printf("export de toute la database !\n");
                                exportWholeDB(db, exportTxt);
                                printf("done\n");
                            }
                            else {
                                compare = strcmp(command, "exportFromInterval");
                                if (compare == 0) {
                                    printf("export from interval!\n");
                                    argumentInt = atoi(strtok(NULL, ";"));
                                    int argumentInt2 = atoi(strtok(NULL, ";"));
                                    exportFromInterval(db, argumentInt, argumentInt2, exportTxt);
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
            ready = fopen(readyTxt, "w"); // We create the file "ready.txt"
            printf("Created ready!\n\n");
            fclose(ready);
            sleep(1); // We add a small delay for the JS
            remove(readyTxt); // Then we remove ready and loop again
        }
    }

    deleteDataBase(db); // When we ask to end the server, we free the whole database.
    printf("Deleted the data base!\n");
}