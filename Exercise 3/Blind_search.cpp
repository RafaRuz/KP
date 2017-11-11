
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include "Blind_search.h"

using namespace std;

// Enumeration representing the orientation, needed to define a path
enum Orientation { North, East, South, West };

//Read the environment called "nameFile" and saves the dimensions of it in "rows" and "columns"
void ReadEnvironment( char ** &environment, const char* nameFile, int &rows, int &columns ){

    FILE* file = fopen(nameFile,"r");

    rows=0;
    columns=0;
    bool countColumns = true;
    char c = fgetc(file);

    while( c != EOF ){
      if( c == '\n' ){
        rows++;
        countColumns = false;
      }
      if( countColumns ){
        columns++;
      }
      c = fgetc(file);
    }

    rewind(file);
    environment = new char*[rows];
    environment[0] = new char[columns];
    int currentRow = 0;
    int currentColumn = 0;
    c = fgetc(file);

    while( c != EOF ){
      if( c == '\n' ){
        currentRow++;
        environment[currentRow] = new char[columns];
        currentColumn = 0;
      }
      else{
        environment[currentRow][currentColumn] = c;
        currentColumn++;
      }
      c = fgetc(file);
    }
}

// Prints the environment in ASCII code
void PrintEnvironment( char** environment, const int rows, const int cols ){

  for(int i=0; i<=rows; i++){
    for(int j=0; j<=cols; j++){
      cout << environment[i][j];
    }
    cout << endl;
  }
}


// Check if a position is suitable for going thru it
bool ValidPosition( pair<int,int> position , char** environment ){
  if( environment[position.first][position.second] == 'x' )
    return(false);
  return(true);
}

//
void BreadthFirst( const char** environment, pair<int,int> initialPosition, list<Orientation> &path ){

  queue<list<Orientation>> frontier;
  pair<int,int>

  frontier.push(North);

}

//
void DepthFirst( const char** environment, pair<int,int> initialPosition, list<Orientation> &path ){


}



int main(int argc, char const *argv[]) {
  char **Environment;
  int rows,columns;

  ReadEnvironment(Environment,"blatt3_environment.txt",rows,columns);
  PrintEnvironment(Environment,rows,columns);
  return(0);

}
