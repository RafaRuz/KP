
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include "Blind_search.h"

using namespace std;



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
