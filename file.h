#include<bits/stdc++.h>
#include<string>
#include"autocomplete.h"
using namespace std;

void serialize(TrieNode *root,ofstream &fp)
{
    if(root == NULL)
        return;
    for(int i=0;i<26;i++)
    {
        if(root->children[i])
        {
            char k = i+97;
            fp<<k;
            serialize(root->children[i],fp);
            fp<<'(';
        }
    }
}
void traverse(TrieNode *root,string str,int level)
{

    if(root->isWordEnd)
    {
        str.push_back('\0');
        cout<<str<<endl;
    }
    int i,k=0;
    for(i=0;i<26;i++)
    {
        if(root->children[i])
        {
            k++;
            char c=i+97;
            str.push_back(c);
            traverse(root->children[i],str,level+1);
            if(k>0)
            {
                int k=str.size()-1;
                str.resize(k);
            }
        }
    }
}
/*
int deserialize(TrieNode *root,ifstream &fp)
{
    char val;
    if(!fp>>val || val == '(')
    {
        root->isWordEnd = true;
        return 1;
    }
     int k = int(val) - 97;
     for(int i=0;i<26;i++)
     {
         if(i == k)
         {
             root->children[i]=getNode();
             if(deserialize(root->children[i],fp))
                return 0;
         }
     }
}*/
int deserialize(TrieNode *root,ifstream &fp)
{
    char c;
    string str;
    int a=0,b=0;
    while(!fp.eof())
    {
        fp>>c;
        if(c == '(')
        {
            if(a == 0)
            {
                //cout<<str<<endl;
                insert(root , str);
                a++;
                b++;
            }
            int k=str.size()-1;
            if(k >= 0)
                str.resize(k);
        }
        else
        {
            str.push_back(c);
            a=0;
        }
    }
    cout<<"insertion completed:"<<b<<endl;
    return 0;
}
