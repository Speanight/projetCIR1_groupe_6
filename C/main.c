//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"
#include "trie.h"
#include "movie.h"
#include "database.h"
#include "dictionary.h"
#include <time.h>
#include<unistd.h>

int main() {
//    Importation time.h pour calculer le temps d'execution de nos fonctions

//    float timeSpent = 0.0; //On initialise le temps d'execution à 0
//    clock_t begin = clock(); //On commence à compter le temps d'execution




//    struct List* l = createEmptyList();
//    struct Movie* m = createMovie("rea", "titre", 64, "genre");
//    struct NodeTrie* t = buildTrieFromFile("../DB/BD_small.txt");

    struct Database* db = createDataBase("../DB/small.txt");

    bool endServer = false;

//    exportFromDuration(db, 115, "../test.txt");
//    exportFromDuration(db, 115, "../test.txt");

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
                }
            }
            fclose(request);
            ready = fopen("../../ready.txt", "w");
            printf("Created ready!\n");
            fclose(ready);
            sleep(1);
            remove("../../ready.txt");
            printf("Removed ready!\n");
        }

    }
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