#include "Suffix-Trie.h"

struct SuffixTrieNode *getNode(char d) { 
    struct SuffixTrieNode *pNode =  (struct SuffixTrieNode*)malloc(sizeof(struct SuffixTrieNode)); 
  
    if(pNode) {
        pNode->isEndOfWord = false; 
  
        pNode->children = (struct SuffixTrieNode**)calloc(256, sizeof(struct SuffixTrieNode));
        pNode->data = d;
    } else {
        perror("Error creating node");
    }
    return pNode; 
}

void SuffixTrieInsert(struct SuffixTrieNode* r, char* s) {
    char** sfx = (char**)malloc((strlen(s)+1) * sizeof(char*));
    char* tmp = s;
    struct SuffixTrieNode* crawler = r;
    for(uint i = 0; i < strlen(s); i++){
        sfx[i] = (char*) malloc (strlen(tmp) * sizeof(char));
        for(uint j = 0; j < strlen(tmp); j++){
            sfx[i][j] = tmp[j];
        }
    }
    for(uint i = 0; i < strlen(s); i++) {
        for(uint j = 0; j < strlen(sfx[i]); j++) {
            if(!crawler->children[(int)sfx[i][j]]) {
                crawler->children[(int)sfx[i][j]] = getNode((int)sfx[i][j]);
            }
            crawler = crawler->children[(int)sfx[i][j]];
        }
        crawler->isEndOfWord = true;
    }
}

bool SuffixTrieSearch(struct SuffixTrieNode* r, char* s, uint iter) {
    struct SuffixTrieNode* crawler = r;
    if(strlen(s) == iter) {
        return (crawler != NULL && crawler->isEndOfWord);
    }

    SuffixTrieSearch(crawler->children[(int) *(s + iter)], s, ++iter);
}