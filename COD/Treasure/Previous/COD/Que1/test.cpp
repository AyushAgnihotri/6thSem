#include <bits/stdc++.h>
using namespace std;
#define ARRAY_SIZE(a) sizeof(a)/sizeof(a[0])
 
#define ALPHABET_SIZE (26)

#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
 
    
    
    bool isLeaf;
};
 
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode = NULL;
 
    pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
 
    if (pNode)
    {
        int i;
 
        pNode->isLeaf = false;
 
        for (i = 0; i < ALPHABET_SIZE; i++)
            pNode->children[i] = NULL;
    }
 
    return pNode;
}

void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
 
    struct TrieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();
 
        pCrawl = pCrawl->children[index];
    }
 
    
    pCrawl->isLeaf = true;
}

bool search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *pCrawl = root;
 
    for (level = 0; level < length; level++)
    {
        index = CHAR_TO_INDEX(key[level]);
 
        if (!pCrawl->children[index])
            return false;
 
        pCrawl = pCrawl->children[index];
    }
 
    return (pCrawl != NULL && pCrawl->isLeaf);
}

 /*
 1. return
 2. int
 3. float
 4. double
 5. do
 6. char
 7. goto
 8. auto
 9. continue
 10. const
 */

int main()
{
    
    char keys[][10] = {"return", "int", "float", "double", "do",
                     "char", "goto", "auto", "continue", "const"};
 
    char output[][32] = {"Not a keyword", "Keyword"};
 
 
    struct TrieNode *root = getNode();
 
    
    int i;
    for (i = 0; i < ARRAY_SIZE(keys); i++)
        insert(root, keys[i]);
	char ch='y';
while (ch=='y' || ch=='Y')
{
    char input[100];
    cin>>input;
    printf("%s --- %s\n", input, output[search(root, input)] );
	cout<<"want to enter more (y/n)? : ";
cin>>ch;
}
    return 0;
}
