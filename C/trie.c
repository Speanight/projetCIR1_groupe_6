#include "trie.h"

int charToInt(char c) {
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
    char* realisateur;
    char* titre;
    int duree;
    char* genre;

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


        printf("%s ; %s ; %d ; %s\n", realisateur, titre, duree, genre);
    }
    fclose(p1);

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

void insertWord(struct NodeTrie* trie, char* word) {
    int i = 0;

    while (word[i] >= 97 && word[i] <= 123) {
        if (trie->children[word[i] - 97] == NULL) {
            trie->children[word[i] - 97] = createEmptyNodeTrie();
        }
        trie = trie->children[word[i] - 97];
        i++;
    }
    trie->isRealisateur = true;
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

bool findWord(struct NodeTrie* trie, char* word) {
    int i = 0;

    while (word[i] >= 97 && word[i] <= 123) {
        if (trie->children[word[i]-97] == NULL) {
            return false;
        }
        trie = trie->children[word[i] - 97];
        i++;
    }

    return trie->isRealisateur;
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