#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <set>

using namespace std;




#define row0 0
#define row1 1
#define row2 2
#define col0 3
#define col1 4
#define col2 5


/*
struct Constraint{
    char X,Y;
    bool (*comp)(const T &v1, const T &v2);

    Constraint( const char &x, const char &y, bool (*c)(const T &v1, const T &v2) ):X(x),Y(y),comp(c){}

    bool check( const T &v1, const T &v2){
      return comp(v1,v2);
    }
};
*/

void GraphArcConsistency( vector< vector<string> > &variables ){
  list<int> to_do;

  to_do.push_back(row0);
  to_do.push_back(row1);
  to_do.push_back(row2);
  to_do.push_back(col0);
  to_do.push_back(col1);
  to_do.push_back(col2);

  while( !to_do.empty() ){
    int actualVariable = to_do.front();
    to_do.pop_front();

    bool deleteWord = true;
    bool deleteWordFinal = false;
    bool insertedDependencies = false;

    if( actualVariable < 3 ){     // If we are checking a row
      for( std::vector<string>::iterator it = variables[actualVariable].begin() ; it != variables[actualVariable].end() ; ){
        deleteWordFinal = false;
        for (size_t i = col0; i <= col2; i++) {    // We check the 3 columns
          deleteWord = true;
          for( vector<string>::iterator it2 = variables[i].begin() ; it2 != variables[i].end() ; it2++ ){
            if( (*it)[i-3] == (*it2)[actualVariable] ){
              deleteWord = false;
            }
          }
          if( deleteWord )
            deleteWordFinal = true;
        }
        if( deleteWordFinal ){
          it = variables[actualVariable].erase(it);
          if( !insertedDependencies ){
            to_do.push_back(col0);
            to_do.push_back(col1);
            to_do.push_back(col2);
            to_do.sort();
            to_do.unique();
            insertedDependencies = true;
          }
        }
        else it++;
      }
    }
    else{               // If we are checking a column
      for( vector<string>::iterator it = variables[actualVariable].begin() ; it != variables[actualVariable].end() ; ){
        deleteWordFinal = false;
        for (size_t i = row0; i <= row2; i++) {    // We check the 3 rows
          deleteWord = true;
          for( vector<string>::iterator it2 = variables[i].begin() ; it2 != variables[i].end() ; it2++ ){
            if( (*it)[i] == (*it2)[actualVariable-3] ){
              deleteWord = false;
            }
          }
          if( deleteWord )
            deleteWordFinal = true;
        }
        if( deleteWordFinal ){
          it = variables[actualVariable].erase(it);
          if( !insertedDependencies ){
            to_do.push_back(row0);
            to_do.push_back(row1);
            to_do.push_back(row2);
            to_do.sort();
            to_do.unique();
            insertedDependencies = true;
          }
        }
        else it++;
      }
    }
  }
}

int main(int argc, char const *argv[]) {

  vector<string> words;
  words.push_back("add");  words.push_back("ado");  words.push_back("age");  words.push_back("ago");
  words.push_back("aid");  words.push_back("air");  words.push_back("ail");  words.push_back("aim");
  words.push_back("and");  words.push_back("any");  words.push_back("ape");  words.push_back("apt");
  words.push_back("arc");  words.push_back("are");  words.push_back("ark");  words.push_back("arm");
  words.push_back("art");  words.push_back("ash");  words.push_back("ask");  words.push_back("auk");
  words.push_back("awe");  words.push_back("awl");  words.push_back("aye");  words.push_back("bad");
  words.push_back("bag");  words.push_back("ban");  words.push_back("bat");  words.push_back("bee");
  words.push_back("boa");  words.push_back("ear");  words.push_back("eel");  words.push_back("eft");
  words.push_back("far");  words.push_back("fat");  words.push_back("fit");  words.push_back("lee");
  words.push_back("oaf");  words.push_back("rat");  words.push_back("tar");  words.push_back("tie");


  vector< vector<string> > variables;

  for (size_t i = 0; i < 6; i++) {
    variables.push_back(words);
  }

  GraphArcConsistency(variables);

  for (size_t i = 0; i < variables.size(); i++) {
    cout << "Posicion " << i << "-->";
    for (size_t j = 0; j < variables[i].size(); j++) {
      cout << variables[i][j] << ", ";
    }
    cout << endl;
  }


  return 0;
}
