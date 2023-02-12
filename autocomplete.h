#include<bits/stdc++.h>
#include<vector>
using namespace std;

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

string st[26][6];
void sets()
{
    for(int i=0;i<26;i++)
        st[i][0]=char(97+i);
    ifstream ifile("string.txt",ios::in);
    string a;
    for(int j=0;j<26;j++)
    {
        for(int i=1;i<6;i++)
        {
            getline(ifile,a);
            st[j][i]=a;
        }
    }
    ifile.close();
}
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];

    // isWordEnd is true if the node represents
    // end of a word
    bool isWordEnd;
};

// Returns new trie node (initialized to NULLs)
TrieNode *getNode(void)
{
    struct TrieNode *pNode = new TrieNode;
    pNode->isWordEnd = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

// If not present, inserts key into trie.  If the
// key is prefix of trie node, just marks leaf node
void insert(struct TrieNode *root,  const string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }

    // mark last node as leaf
    pCrawl->isWordEnd = true;
}

// Returns true if key presents in trie, else false
bool search(struct TrieNode *root, const string key)
{
    int length = key.length();
    struct TrieNode *pCrawl = root;
    for (int level = 0; level < length; level++)
    {
        int index = CHAR_TO_INDEX(key[level]);

        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    return (pCrawl != NULL && pCrawl->isWordEnd);
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}

// Recursive function to print auto-suggestions for given
// node.
void suggestionsRec(struct TrieNode* root, string currPrefix)
{
    // found a string in Trie with the given prefix
    //vector<string> myvector{}
    if (root->isWordEnd)
    {
        cout << currPrefix;
        cout << endl;
    }

    // All children struct node pointers are NULL
    if (isLastNode(root))
        return;

    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            // append current character to currPrefix string
            currPrefix.push_back(97 + i);

            // recur over the rest
            suggestionsRec(root->children[i], currPrefix);
            // remove last character

            int k=currPrefix.size()-1;
            currPrefix.resize(k);
        }
    }
}

// print suggestions for given query prefix.
int printAutoSuggestions(TrieNode* root, const string query)
{
    struct TrieNode* pCrawl = root;

    // Check if prefix is present and find the
    // the node (of last level) with last character
    // of given string.
    int level;
    int n = query.length();
    if(n==1)
    {
        sets();
        for(int j=0;j<26;j++)
        {
            for(int i=0;i<6;i++)
            {
                if(st[j][0] != query)
                    break;
                cout<<st[j][i]<<endl;
            }
        }
    }
    else
    {
        for (level = 0; level < n; level++)
        {
            int index = CHAR_TO_INDEX(query[level]);

            // no string in the Trie has this prefix
            if (!pCrawl->children[index])
                return 0;

            pCrawl = pCrawl->children[index];
        }

        // If prefix is present as a word.
        bool isWord = (pCrawl->isWordEnd == true);

        // If prefix is last node of tree (has no
        // children)
        bool isLast = isLastNode(pCrawl);

        // If prefix is present as a word, but
        // there is no subtree below the last
        // matching node.
        if (isWord && isLast)
        {
            cout << query << endl;
            return -1;
        }

        // If there are are nodes below last
        // matching character.
        if (!isLast)
        {
            string prefix = query;
            suggestionsRec(pCrawl, prefix);
            return 1;
        }
    }
}

