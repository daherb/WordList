#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int main(int argc, char **argv)
{
  set<string> unify;
  if (argc!=3)
  {
    cout << "Usage: " << argv[0] << " <file1> <file2|->" << endl;
    cout << "Prints all words in file1 OR file2" << endl;
    cout << "- as second parameter reads from stdin" << endl;
  }
  else
  {
    istream *f1,*f2;
    f1=(istream *) new ifstream((const char *) argv[1] , ifstream::in );
    if (strcmp(argv[2],"-")!=0)
      f2=(istream *) new ifstream((const char *) argv[2] , ifstream::in );
    else
      f2=&cin;
    string word;
    while (*f1 >> word)
    {
      unify.insert(word);
    }
    while (*f2 >> word)
    {
      unify.insert(word);
    }
    for (std::set<string>::iterator it=unify.begin(); it!=unify.end(); ++it)
      cout << *it << endl;
  }
}