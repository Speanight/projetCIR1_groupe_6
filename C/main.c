//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"
#include "trie.h"
#include "movie.h"
#include "database.h"
#include "dictionary.h"
#include <time.h>
#include <unistd.h>

int main() {

    struct Database* db = buildDataBase("../DB/BD_small.txt");

    bool endServer = true;

    FILE* ready;
    FILE* request;
    char line[64];
    char* command;
    char* argumentStr;
    int argumentInt;
    int compare;


    while(!endServer) {

        request = fopen("../../request.txt", "r");

        if (request != NULL) {
            fgets(line, sizeof(line), request);
            remove("../../request.txt");
            command = strtok(line, ";");

            compare = strcmp(command, "exportAllFromRealisateurs");
            if (compare == 0) {
                printf("export from realisateurs!\n");
                argumentStr = strtok(NULL, ";");
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
            fclose(request);
            ready = fopen("../../ready.txt", "w");
            fclose(ready);
            sleep(1);
            remove("../../ready.txt");
        }
    }

    deleteDataBase(db);
}




//    exportFromDuration(db, 115, "../test.txt");

//    struct Dictionary* d = createEmptyDictionary();
//    updateDictionary("../DB/BD_small.txt", d);
//    findAllMovies(db->triParRealisateurs, "l", l);

//    exportAllFromRealisateurs(db->triParRealisateurs, "l", "../test.txt");





//    clock_t end = clock(); //Fin du temps d'execution
//    timeSpent = timeSpent + (float)(end - begin) / CLOCKS_PER_SEC; // on calcule le temps d'execution en faisant la difference entre le début et la fin de l'execution
//    // puis on divise par CLOCKS_PER_SEC pour avoir le temps en secondes
//    return 0;
//}