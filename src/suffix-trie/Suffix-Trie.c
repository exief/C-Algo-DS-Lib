struct SuffixTrieNode *getNode(char d) { 
    struct SuffixTrieNode *pNode =  (SuffixTrieNode*)malloc(sizeof(SuffixTrieNode)); 
  
    if(pNode) {
        pNode->isEndOfWord = false; 
  
        pNode->children = (SuffixTrieNode*)calloc(256, sizeof(SuffixTrieNode));
        pNode->data = d;
    } else {
        perror("Error creating node");
    }
    return pNode; 
}

void SuffixTrieInsert(SuffixTrieNode* r, const char* s) {
    char** sfx = (char**)malloc((strlen(s)+1) * sizeof(char*));
    char* tmp = s;
    SuffixTrieNode* crawler = r;
    for(int i = 0; i < strlen(s); i++){
        sfx[i] = (char*) malloc (strlen(tmp) * sizeof(char));
        for(int j = 0; j < strlen(tmp); j++){
            sfx[i][j] = tmp[j];
        }
    }
    for(int i = 0; i < strlen(s); i++) {
        for(int j = 0; j < strlen(sfx[i]); j++) {
            if(!crawler->children[sfx[i][j]]) {
                crawler->children[sfx[i][j]] = getNode(sfx[i][j]);
            }
            crawler = crawler->children[sfx[i][j]];
        }
        crawler->isEndOfWord = true;
    }
}

bool SuffixTrieSearch(SuffixTrieNode* r, const char* s) {
    SuffixTrieNode* crawler = r;
    if(!strlen(key)) {
        return (crawler != NULL && crawler->isEndOfWord)
    }

    SuffixTrieSearch(crawler->children[*s], ++s);
}