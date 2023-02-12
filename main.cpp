#include<fstream>
#include<conio.h>
#include"file.h"
#include <stdlib.h>
#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60
using namespace std;

void printProgress (double percentage)
{
    int val = (int) (percentage * 100);
    int lpad = (int) (percentage * PBWIDTH);
    int rpad = PBWIDTH - lpad;
    printf ("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
    fflush (stdout);
}
using namespace std;
int main()
{
    cout<<"\n\n\n\n\n\n\n\n\t\t\t\tWELCOME TO THE WORD AUTOCOMPLETE PROGRAM\n\n\t\t\t\t\t\t\tby:\n\t\t\t\t\t\t\t\tSELVA K (19PD31)\n\t\t\t\t\t\t\t\tRAMBABU S (19PD26)";
    cout<<"\n\n\n(press enter to continue)";
    if(cin.get())
        system("cls");
    cout<<"\n\n\n\nPLEASE WAIT FOR THE WORD DATABASE TO LOAD.THIS MAY TAKE A FEW MINUTES. APOLOGIES FOR THE DELAY\n\n";
    _sleep(5000);

    double perc;
    struct TrieNode* root = getNode();
    string str;
    int level=0;

//    ifstream fin("text2.txt",ios::in);
//    string k;
//    int i=0;
//    while(!fin.eof())
//    {
//        fin>>k;
//        insert(root,k);
//        i++;
//        perc=i/float(100);
//	  printProgress(perc);
//        system("cls");
//    }
//    fin.close();
//
//    cout<<"trie imsertion completed:";
//
//    cout<<"trie imsertion completed:";
//    ofstream fon("file1.txt",ios::out);
//    serialize(root,fon);
//    fon.close();


    ifstream fin("file1.txt",ios::in);
    deserialize(root,fin);
    fin.close();

    char c;
    string s;
    _sleep(3000);
    system("cls");
    cout<<"\n\n\nstart typing:\n";
    do
    {
        c=getche();
        if(c==13)
            break;
        if(c=='\b')
        {   
            if (s.length()>0){
            int k=s.size()-1;
            s.resize(k);
            }
        }
        else
            s.push_back(c);
        system("cls");
        if (s.length()>=2){
        cout<<s<<"\nword suggestions\n\n";
        int comp = printAutoSuggestions(root, s);

        if (comp == -1)
            cout << "No other strings found with this prefix\n";

        else if (comp == 0)
            cout << "No string found with this prefix\n";
        }
    }while(c!='\n');

    //display(root,str,level);
}
