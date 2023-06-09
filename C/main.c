//
// Created by ADMIN on 6/9/2023.
//

#include "list.h"
#include "trie.h"
#include "movie.h"

int main() {
    struct List* l = createEmptyList();

    struct Movie* m = createMovie("rea", "titre", 64, "genre");

    struct Trie* t = buildTrieFromFile("../DB/BD_small.txt");
    addFirst(l, m);
}