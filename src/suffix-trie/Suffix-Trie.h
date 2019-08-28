#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

struct SuffixTrieNode {
    char data;
    struct SuffixTrieNode** children;
    bool isEndOfWord;
} SuffixTrieNode;

struct SuffixTrie {
    struct SuffixTrieNode* root;
    void (*insert)(struct SuffixTrieNode*, char*);
    bool (*search)(struct SuffixTrieNode*, char*);
};

struct SuffixTrieNode *getNode(char d);
void SuffixTrieInsert(struct SuffixTrieNode* r, char* s);
bool SuffixTrieSearch(struct SuffixTrieNode* r, char* s, uint iter);