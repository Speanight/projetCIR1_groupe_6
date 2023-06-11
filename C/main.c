//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"
#include "trie.h"
#include "movie.h"
#include "database.h"

int main() {
    struct List* l = createEmptyList();

    struct Movie* m = createMovie("rea", "titre", 64, "genre");

    struct NodeTrie* t = buildTrieFromFile("../DB/BD_small.txt");

    struct Database* db = createDataBase("../DB/BD_small.txt");

    exportFromDuration(db, 115, "../test.txt");
    printf("fini");

    findAllMovies(db->triParRealisateurs, "", l);

    return 0;
}