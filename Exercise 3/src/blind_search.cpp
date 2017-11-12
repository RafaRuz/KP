
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include "blind_search.h"

using namespace std;


// Breadth-First searching algorithm
bool BreadthFirst( const Environment environment, Path &path ){

  queue<Path> frontier;
  Path currentPath;
  pair<unsigned int,unsigned int> start = environment.getStart();
  if( environment.isValidPosition(start.first,start.second+1 ))
    currentPath.addMovement(North);
  else if( environment.isValidPosition(start.first+1,start.second))
    currentPath.addMovement(East);
  else if( environment.isValidPosition(start.first,start.second-1))
    currentPath.addMovement(South);
  else if( environment.isValidPosition(start.first-1,start.second))
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
    Environment environment("./txt/blatt3_environment.txt")
    environment.Print();

  Path path(start);
  BreadthFirst(Environment,path);

  cout << "Breadth-First algorithm:" << endl;
  environment.Print(path);
  return(0);

}
