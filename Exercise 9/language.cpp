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

  string actual_word, last_word;
  map<string,map<string,double> > dictionary;
  map<string,double> aux;
  actual_word = "<start>";

  string tokens[] = {".","!","!!!!!!","!!!!!","!!!!","!!!","!!","!","?",";",""};
  set<string> sentence_endings(tokens,tokens+11);

  while( !input.eof() ){
    last_word = actual_word;
    getline(input,actual_word);

    map<string,map<string,double> >::iterator pos = dictionary.find(last_word);

    if( pos == dictionary.end() ){
      dictionary.insert(pair<string,map<string,double> >(last_word,aux));
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
  for( map<string,map<string,double> >::iterator it = dictionary.begin(); it != dictionary.end(); ++it ){
    count = 0;

    for( map<string,double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2 ){
      count += it2->second;
    }

    for( map<string,double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2 ){
      it2->second = it2->second/count;
    }
  }


  string final_sentence;
  int length = 0;

  cout << "Tell me the length of the sentence you want me to build." << endl;
  cin >> length;
  cin.ignore();
  cout << "\nTell me the initial part of the sentence (write # to end the program)." << endl;
  getline(cin,final_sentence);

  while( final_sentence != "#" ){
    string token;
    istringstream( { final_sentence.rbegin(), final_sentence.rend() } ) >> token; // #include <sstream>
    final_sentence = { token.rbegin(), token.rend() };
    cout << "ASDASDSA    ("<< final_sentence << ")  werwerwer" << endl;

    map<string,map<string,double> >::iterator pos = dictionary.find(final_sentence);

    if( pos != dictionary.end() ){
      for( int i=0; i<length ; i++){
        double r = r = ((double) rand() / (RAND_MAX));
        double sums_of_probs = 0;
        string selected_word;
        bool selected = false;

        for( map<string,double>::iterator it2 = pos->second.begin(); it2 != pos->second.end() && !selected; ++it2 ){
          sums_of_probs += it2->second;

          if( sums_of_probs >= r ){
            selected_word = it2->first;
            selected = true;
          }
        }

        //if( sentence_endings.count(selected_word) && i != length-1 ){
        //  i--;
        //}
        //else{
          final_sentence += (" " + selected_word);
        //}
      }
    }
    else{
      cout << "Oops, I didn't even know that word existed!." << endl;
    }

    cout << "Tell me the length of the sentence you want me to build." << endl;
    cin >> length;
    cout << "Tell me the initial part of the sentence (write # to end the program)." << endl;
    getline(cin,final_sentence);
  }
  input.close();
  return 0;
}
