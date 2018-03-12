#include<bits/stdc++.h>
#define ALPHABETS 26
#define char_to_index(c) (int(c)-(int)'a')
using namespace std;
struct TrieNode
{
	struct TrieNode *children[ALPHABETS];
	bool isLeaf;
};
struct TrieNode *getNode()
{
	struct TrieNode *pNode = NULL;
	pNode = (struct TrieNode *)malloc(sizeof(struct TrieNode));
	if (pNode)
	{
		pNode->isLeaf=false;
		for (int i=0; i<ALPHABETS; i++)
			pNode->children[i]=NULL;
	}
	return pNode;
}
void insert(struct TrieNode *root, char *key)
{
	int level, index, length;
	length = strlen(key);
	struct TrieNode *pCrawl = root;
	for (level=0; level<length; level++)
	{
		index = char_to_index(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index]=getNode();
		pCrawl = pCrawl->children[index];
	}
	pCrawl->isLeaf=true;
}
bool search(struct TrieNode *root, char *key)
{
	int level, index, length;
	length = strlen(key);
	struct TrieNode *pCrawl = root;
	for (level=0; level<length; level++)
	{
		index = char_to_index(key[level]);
		if (!pCrawl->children[index])
			return false;
		pCrawl = pCrawl->children[index];
	}
	if (pCrawl!=NULL && pCrawl->isLeaf)
		return true;
	else
		return false;
}
int main()
{
	char keywords[][10] = {"auto", "return", "while", "xor", "int", "float", "double", "do", "char", "for"};
    char output[][32] = {"Not a Keyword", "Keyword"};
    struct TrieNode *root = getNode();
    // Construct trie
    int i;
    for (i = 0; i < 10; i++)
        insert(root, keywords[i]);
 
    // Search for input keys
    for (int i=0; i<15; i++)
    {
	    char str[10];
	    scanf("%s",str);
	    printf("%s\n", output[search(root,str)] );
	}
    return 0;
}


