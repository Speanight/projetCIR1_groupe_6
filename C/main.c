//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"
#include "trie.h"
#include "movie.h"
#include "database.h"
#include "dictionary.h"

int main() {
    struct List* l = createEmptyList();

//    struct Movie* m = createMovie("rea", "titre", 64, "genre");

//    struct NodeTrie* t = buildTrieFromFile("../DB/BD_small-maisEnMieux.txt");

    struct Database* db = createDataBase("../DB/BD_small.txt");

    exportFromDuration(db, 115, "../test.txt");

//    struct Dictionary* d = createEmptyDictionary();
//    updateDictionary("../DB/BD_small.txt", d);

    findAllMovies(db->triParRealisateurs, "lee", l);

    exportAllFromRealisateurs(db->triParRealisateurs, "lee", "../test.txt");

    return 0;
}