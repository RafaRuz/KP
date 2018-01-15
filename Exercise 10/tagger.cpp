#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <set>
#include <sstream>

using namespace std;


int main(int argc, char const *argv[]) {

  if( argc != 2 ){
    cout << "Error. Usage: " << argv[0] << " [file] ." << endl;
    return(1);
  }

  ifstream input(argv[1]);

  if( !input.is_open() ){
    cout << "Error reading the file." << endl;
    return(1);
  }

  string actual_word, last_word, actual_tag;
  map<pair<string, string>,map<string,double> >  dictionary;
  map<string,double> aux;

  getline(input,actual_word, '\t');
  getline(input,actual_tag);
  pair <string,string> actual_pair = pair <string,string>(actual_word, actual_tag);
  pair <string,string> last_pair;

  while( !input.eof() ){
    last_pair = actual_pair;
    getline(input,actual_word, '\t');
    getline(input,actual_tag);
    actual_pair =  pair <string,string> (actual_word, actual_tag);


    map<pair<string, string>,map<string,double> > ::iterator pos = dictionary.find(last_pair);

    if( pos == dictionary.end() ){
      dictionary.insert(pair<pair<string,string>,map<string,double> >(last_pair,aux));
    }
    else{
      map<string,double>::iterator pos2 = pos->second.find(actual_word);

      if( pos2 == pos->second.end() ){
        pos->second.insert(pair<string,double>(actual_word,1));
      }
      else{
        pos2->second++;
      }
    }
  }

  double count = 0;
  for( map<pair<string, string>,map<string,double> > ::iterator it = dictionary.begin(); it != dictionary.end(); ++it ){
    count = 0;

    for( map<string,double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2 ){
      count += it2->second;
    }

    for( map<string,double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2 ){
      it2->second = it2->second/count;
    }
  }

  input.close();
  return 0;
}
