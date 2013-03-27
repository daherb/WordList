#include <unordered_map>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
int max_dist=0;

// Compare Levenshtein Distance
// Vgl. http://en.wikibooks.org/wiki/Algorithm_implementation/Strings/Levenshtein_distance#C.2B.2B
template <class T> struct levenshtein_equal_to : binary_function <T,T,bool> {
  bool operator() (const T& x, const T& y) const
    {
      const size_t len1 = x.size(), len2 = y.size();
      vector<unsigned int> col(len2+1), prevCol(len2+1);
      for (unsigned int i = 0; i < prevCol.size(); i++)
	prevCol[i] = i;
      for (unsigned int i = 0; i < len1; i++) {
	col[0] = i+1;
	for (unsigned int j = 0; j < len2; j++)
	  col[j+1] = min( min( 1 + col[j], 1 + prevCol[1 + j]),
			  prevCol[j] + (x[i]==y[j] ? 0 : 1) );
	col.swap(prevCol);
      }
      return prevCol[len2]<=max_dist;
    }
};

template <class T> struct by_val : binary_function <T,T,bool> {
  bool operator() (const T& lhs, const T& rhs) const
  {
    return lhs.second > rhs.second;
  }
};

int levenshtein_insert(vector<pair<string,int> > *list, pair<string,int> value)
{
  levenshtein_equal_to<string> leq;
  for (vector<pair<string,int> >::iterator it = (*list).begin(); it != (*list).end(); ++it)
    if (leq((*it).first, value.first))
      {
	(*it).second+=value.second;
	sort((*list).begin(),it,by_val<pair<string, int> >());
	return 0;
      }
  (*list).push_back(value);
  return (*list).size();
}
int main(int argc, char **argv)
{
  vector<pair<string,int> > freq;
  vector<pair<string,int> > stop;
  if (argc<2)
    {
      cout << "Usage: " << argv[0] << " <file1> [<number> [<file2>]]" << endl;
      cout << "Prints a approximate frequency list of words in file1" << endl;
      cout << "The optional number is the maximum Levenshtein distance for which words are seen as equal" << endl;
      cout << "The optional second file can be a stop word list of words to ignore" << endl;
    }
  else
    {
      string word;
      ifstream *f1=new ifstream((const char *) argv[1] , ifstream::in );
      if (argc>=3)
	{
	  max_dist=atoi(argv[2]);
	}
      if (argc==4)
	{
	  ifstream *f2=new ifstream((const char *) argv[3] , ifstream::in );
	  while (*f2 >> word)
	    {
	      levenshtein_insert(&stop,make_pair(word,0));
	    }
	  delete(f2);
	}
      while (*f1 >> word)
	{
	  levenshtein_insert(&freq,make_pair(word,1));
	}
      delete(f1);
      for (vector<pair<string,int> >::iterator it = freq.begin(); it != freq.end(); ++it)
	cout << (*it).second << "\t" << (*it).first << endl;
    }
}
