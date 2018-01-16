#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <utility>
#include <set>
#include <list>
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

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

  srand(time(NULL));

  string actual_word, last_word, actual_tag, last_tag;
  map<string,map<string,double> >  tag_dictionary;
  map<string,double> aux;
  map<string,string> word_tag_dictionary;

  getline(input,actual_word, '\t');
  getline(input,actual_tag);
  word_tag_dictionary.insert(pair<string,string>(actual_word, actual_tag));  // If it already exists, the insert does nothing so we don't have to check it

  while( !input.eof() ){
    last_word = actual_word;
    last_tag = actual_tag;
    getline(input,actual_word, '\t');
    getline(input,actual_tag);
    word_tag_dictionary.insert(pair<string,string> (actual_word, actual_tag));

    map<string,map<string,double> >::iterator pos = tag_dictionary.find(last_tag);

    if( pos == tag_dictionary.end() ){
      tag_dictionary.insert(pair<string,map<string,double> >(last_tag,aux));
    }
    else{
      map<string,double>::iterator pos2 = pos->second.find(actual_tag);

      if( pos2 == pos->second.end() ){
        pos->second.insert(pair<string,double>(actual_word,1));
      }
      else{
        pos2->second++;
      }
    }
  }

  double count = 0;
  for( map<string,map<string,double> >::iterator it = tag_dictionary.begin(); it != tag_dictionary.end(); ++it ){
    count = 0;

    for( map<string,double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2 ){
      count += it2->second;
    }

    for( map<string,double>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2 ){
      it2->second = it2->second/count;
    }
  }



  string output_tags;
  string sentence;

  cout << "Tell me some words." << endl;
  getline(cin,sentence);
  cout << "Tags matching the sentence: " << endl;

  string::const_iterator it_begin = sentence.begin();
  string::const_iterator it_end = sentence.end();

  for( string::const_iterator it = it_begin; it != it_end; ++it){
    if( *it == ' ' ){
      actual_word = string(it_begin,it);
      it_begin = it+1;

      map<string,string>::iterator position = word_tag_dictionary.find(actual_word);
      if( position == word_tag_dictionary.end() ){
        double r = ((double) rand() / (RAND_MAX));
        double sums_of_probs = 0;
        string selected_tag;
        bool selected = false;

        if( output_tags.empty() ){
          last_tag = "<start>";
        }

        map<string,map<string,double> >::iterator tag_pos = tag_dictionary.find(last_tag);

        for( map<string,double>::iterator it2 = tag_pos->second.begin(); it2 != tag_pos->second.end() && !selected; ++it2 ){
          sums_of_probs += it2->second;

          if( sums_of_probs >= r ){
            selected_tag = it2->first;
            selected = true;
          }
        }
      }
      else{
        output_tags += ' ';
        output_tags += position->second;
        last_tag = position->second;
      }
    }
  }

  if( it_begin != it_end )
    actual_word = string(it_begin,it_end);

  map<string,string>::iterator position = word_tag_dictionary.find(actual_word);
  if( position == word_tag_dictionary.end() ){
    double r = ((double) rand() / (RAND_MAX));
    double sums_of_probs = 0;
    string selected_tag;
    bool selected = false;

    if( output_tags.empty() ){
      last_tag = "<start>";
    }

    map<string,map<string,double> >::iterator tag_pos = tag_dictionary.find(last_tag);

    for( map<string,double>::iterator it2 = tag_pos->second.begin(); it2 != tag_pos->second.end() && !selected; ++it2 ){
      sums_of_probs += it2->second;

      if( sums_of_probs >= r ){
        selected_tag = it2->first;
        selected = true;
      }
    }
    output_tags += ' ';
    output_tags += selected_tag;
    last_tag = selected_tag;
  }
  else{
    output_tags += ' ';
    output_tags += position->second;
    last_tag = position->second;
  }

  cout << output_tags << endl;

  input.close();
  return 0;
}
