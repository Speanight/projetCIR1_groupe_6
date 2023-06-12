//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"
#include "trie.h"
#include "movie.h"
#include "database.h"
#include "dictionary.h"

int main() {
//    struct List* l = createEmptyList();
//    struct Movie* m = createMovie("rea", "titre", 64, "genre");
//    struct NodeTrie* t = buildTrieFromFile("../DB/BD_small.txt");

    struct Database* db = createDataBase("../DB/BD_small.txt");

    bool endServer = false;
    FILE* request;

//    exportFromDuration(db, 115, "../test.txt");
//    exportFromDuration(db, 115, "../test.txt");

    while(!endServer) {
        char line[64];
        char* command;
        char* argumentStr;
        int argumentInt;
        int compare;

        request = fopen("../../request.txt", "r");
        if (request != NULL) {
            fgets(line, sizeof(line), request);
            command = strtok(line, ";");

            compare = strcmp(command, "exportFromDuration");
            if (compare == 0) {
                printf("export from duration!\n");
                argumentInt = atoi(strtok(NULL, ";"));
                printf("argumentInt = %d\n", argumentInt);
                exportFromDuration(db, argumentInt, "../../result.txt");
            }
            else {
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
                }
            }
            fclose(request);
            FILE* ready;
            ready = fopen("../../ready.txt", "w");
            fclose(ready);
            remove("../../request.txt");
        }
    }

//    exportFromDuration(db, 115, "../test.txt");

//    struct Dictionary* d = createEmptyDictionary();
//    updateDictionary("../DB/BD_small.txt", d);
//    findAllMovies(db->triParRealisateurs, "l", l);

//    exportAllFromRealisateurs(db->triParRealisateurs, "l", "../test.txt");

    return 0;
}