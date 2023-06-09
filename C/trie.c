#include "trie.h"

int charToInt(char c) {
    if (c == '-') {
        return 26;
    }
    return c-'a';
}

bool lastLetter(struct NodeTrie* trie) {
    for (int i = 0; i < ALPHABET; i++) {
        if (trie->children[i] != NULL) {
            return false;
        }
    }
    return true;
}

char* toLower(char* str) {
    int i = 0;
    while (i < strlen(str)) {
        if (str[i] <= 'Z' && str[i] >= 'A') {
            str[i] = str[i] + 32;
        }
        i++;
    }
    return str;
}


bool getIsWord(struct NodeTrie* trie) {
    return trie->isRealisateur;
}

struct NodeTrie* buildTrieFromFile(char* nameFile) {
    FILE* p1;
    p1 = fopen(nameFile, "r");

    if (p1 == NULL) {
        printf("error in opening file.\n");
        return NULL;
    }

    struct NodeTrie* trie = createEmptyNodeTrie();
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

        insertMovie(trie, m);


    }
    fclose(p1);

    return trie;
//    return movie;
}


struct NodeTrie* createEmptyNodeTrie() {
    struct NodeTrie* trie = malloc(sizeof(struct NodeTrie));

    if (trie == NULL) {
        printf("error malloc");
        return NULL;
    }

    for (int i = 0; i < ALPHABET; i++) {
        trie->children[i] = NULL;
    }

    trie->isRealisateur = false;
    trie->movies = createEmptyList();
    return trie;
}

#include <stdio.h>


void insertMovie(struct NodeTrie* trie, struct Movie* m) {
    int i = 0;
    char* realisateur = toLower(m->realisateur);

    while (realisateur[i] >= 97 && realisateur[i] <= 123 || realisateur[i] == '-') {
        int position;
        if (realisateur[i] - 97 >= 0 && realisateur[i] - 97 <= 26) {
            position = realisateur[i]-97;
        }
        else {
            position = 26;
        }
        if (trie->children[position] == NULL) {
            trie->children[position] = createEmptyNodeTrie();
        }
        trie = trie->children[position];
        i++;
    }
    trie->isRealisateur = true;
    addFirst(trie->movies, m);
}

void deleteWord(struct NodeTrie* trie, char* word) {
    int i = 0;

    while (word[i] >= 97 && word[i] <= 123) {
        if (trie->children[word[i]-97] == NULL) {
            return;
        }
        trie = trie->children[word[i]-97];
        i++;
    }
    trie->isRealisateur = false;
}

struct List* findMovies(struct NodeTrie* trie, char* realisateur) {
    int i = 0;
    struct NodeTrie* temp = trie;
    int pos = 0;

    while (i < strlen(realisateur)) {
        pos = charToInt(realisateur[i]);
        if (temp->children[pos] == NULL) {
            return NULL;
        }
        temp = temp->children[pos];
        i++;
    }
    return temp->movies;
}

unsigned int numberOfWords(struct NodeTrie* trie) {
    unsigned int sum = 0;
    for (int i = 0; i < ALPHABET; i++) {
        if (trie->children[i] != NULL) {
            sum += getIsWord(trie->children[i]) + numberOfWords(trie->children[i]);
        }
    }
    return sum;
}

void exportFromRealisateurs(struct NodeTrie* trie, char* realisateur, char* textFile) {
    struct List* l = findMovies(trie, realisateur);
    char* line;
    char duree[5];

    FILE *p1;
    p1 = fopen(textFile, "w");

    if (listSize(l) == 0) {
        fprintf(p1, "NULL");
        return;
    }
    unsigned int size = listSize(l);
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
//        strcat(line, l->head->movie->titre);
//        strcat(line, ";");
//        strcat(line, l->head->movie->realisateur);
//        strcat(line, ";");
//        strcat(line, l->head->movie->duree);
//        strcat(line, ";");
//        strcat(line, l->head->movie->genre);
//
//        fprintf(p1, line);
//        line = "";
    }
    fclose(p1);
}

void displayDict(struct NodeTrie* trie, char* actualWord, int index) {
    if (trie->isRealisateur) {
        actualWord[index] = '\0';
        printf("%s\n", actualWord);
    }

    for (int i = 0; i < ALPHABET; i++) {
        if (trie->children[i] != NULL) {
            actualWord[index] = 'a' + i;
            displayDict(trie->children[i], actualWord, index+1);
        }
    }
}

void deleteNodeTrie(struct NodeTrie** trie) {
    for (int i = 0; i < ALPHABET; i++) {
        if ((*trie)->children[i] != NULL) {
            deleteNodeTrie(&(*trie)->children[i]);
        }
    }

    free(*trie);
    *trie = NULL;
}


void writeWord(struct NodeTrie* trie) {
    printf("Enter a letter: ");
    char entry[MAX_REALISATEUR_SIZE];
    scanf("%s", entry);

    struct NodeTrie *select = trie;
    char buildWord[MAX_REALISATEUR_SIZE];
    char actualWord[MAX_REALISATEUR_SIZE];

    printf("%d\n", entry[0] - 'a');
    if (trie->children[entry[0] - 'a'] == NULL) {
        printf("Aucun mot n'existe dans la base de données !");
    } else {
        select = trie->children[entry[0] - 'a'];

        displayDict(select, actualWord, 0);
    }
}