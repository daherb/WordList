#include <set>
#include <string>
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;
int main(int argc, char **argv)
{
  set<string> s,complement;
  if (argc!=3)
  {
    cout << "Usage: " << argv[0] << " <file1|-> <file2|->" << endl;
    cout << "Prints all words in file2 but not in file1" << endl;
    cout << "- as parameter reads from stdin" << endl;
  }
  else
  {
    istream *f1,*f2;
    if (strcmp(argv[1],"-")!=0)
      f1=(istream *) new ifstream((const char *) argv[1] , ifstream::in );
    else
      f1=&cin;
    if (strcmp(argv[2],"-")!=0)
      f2=(istream *) new ifstream((const char *) argv[2] , ifstream::in );
    else
      f2=&cin;
    string word;
    while (*f1 >> word)
    {
      s.insert(word);
    }
    while (*f2 >> word)
    {
      if(s.count(word)==0)
       complement.insert(word);
    }
    for (std::set<string>::iterator it=complement.begin(); it!=complement.end(); ++it)
      cout << *it << endl;
  }
}