#include <stdlib.h>

struct SuffixTrieNode {
    char data = NULL;
    SuffixTrieNode* children = (SuffixTrieNode*)calloc(256, sizeof(SuffixTrieNode));
    bool isEndOfWord = false;;
} SuffixTrieNode;

struct SuffixTrie {
    SuffixTrieNode* root;
    void (*insert)(SuffixTrieNode*, const char*) = &SuffixTrieInsert;
    bool (*search)(SuffixTrieNode*, const char*) = &SuffixTrieSearch;
}

struct SuffixTrieNode *getNode(char d);
void SuffixTrieInsert(SuffixTrieNode* r, const char* s);
bool SuffixTrieSearch((SuffixTrieNode* r, const char* s);