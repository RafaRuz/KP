
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include "Blind_search.h"

using namespace std;


// Breadth-First searching algorithm
bool BreadthFirst( const Environment environment, Path &path ){

  queue<Path> frontier;
  Path currentPath;

  if( environment.isValidPosition(environment.getStartPosition().first,environment.getStartPosition().second+1) )
    currentPath.addMovement(North);
  else if( environment.isValidPosition(environment.getStartPosition().first+1,environment.getStartPosition().second) )
    currentPath.addMovement(East);
  else if( environment.isValidPosition(environment.getStartPosition().first,environment.getStartPosition().second-1) )
    currentPath.addMovement(South);
  else if( environment.isValidPosition(environment.getStartPosition().first-1,environment.getStartPosition().second) )
    currentPath.addMovement(West);

  while( !frontier.empty() ){
    currentPath = frontier.pop();

    if( environment.isValidPosition(currentPath.getEndPosition().first,currentPath.getEndPosition().second+1) )
      currentPath.addMovement(North);
    else if( environment.isValidPosition(currentPath.getEndPosition().first+1,currentPath.getEndPosition().second) )
      currentPath.addMovement(East);
    else if( environment.isValidPosition(currentPath.getEndPosition().first,currentPath.getEndPosition().second-1) )
      currentPath.addMovement(South);
    else if( environment.isValidPosition(currentPath.getEndPosition().first-1,currentPath.getEndPosition().second) )
      currentPath.addMovement(West);

    if( currentPath.getEndPosition() == environment.getGoalPosition() ){
      path = currentPath;
      return(true);
    }
  }
  return(false);

}

//
void DepthFirst( const char** environment, pair<int,int> initialPosition, list<Orientation> &path ){


}



int main(int argc, char const *argv[]) {
  char **Environment;
  int rows,columns;

  ReadEnvironment(Environment,"blatt3_environment.txt",rows,columns);

  cout << "Environment:" << endl;
  PrintEnvironment(Environment,rows,columns);

  Path path(environment.getStartPosition());
  BreadthFirst(Environment,path);

  cout << "Breadth-First algorithm:" << endl;
  environment.Print(path);
  return(0);

}
