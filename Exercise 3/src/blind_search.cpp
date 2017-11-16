
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <stack>            // std::stack
#include <vector>           // std::vector

#include "blind_search.h"

using namespace std;

// Expands a Path checking the four adjacent positions
vector<Path> ExpandPath( const Path &currentPath, const Environment &environment){
  Path auxPath(environment.getStart());
  vector<Path> paths;

  if( environment.isValidPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) &&
      !currentPath.containsPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) ){
    auxPath = currentPath;
    auxPath.addPosition(currentPath.getEnd().first+1,currentPath.getEnd().second);
    paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) &&
      !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) ){
     auxPath = currentPath;
     auxPath.addPosition(currentPath.getEnd().first,currentPath.getEnd().second+1);
     paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) &&
      !currentPath.containsPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) ){
    auxPath = currentPath;
    auxPath.addPosition(currentPath.getEnd().first-1,currentPath.getEnd().second);
    paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) &&
      !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) ){
     auxPath = currentPath;
     auxPath.addPosition(currentPath.getEnd().first,currentPath.getEnd().second-1);
     paths.push_back(auxPath);
  }
  return(paths);
}

// Breadth-First searching algorithm
bool BreadthFirst( const Environment &environment, Path &path ){

  queue<Path> frontier;
  Path currentPath(environment.getStart());

  do{
    if( !frontier.empty() ){
      currentPath = frontier.front();
      frontier.pop();
    }

    vector<Path> extendedPaths;
    extendedPaths = ExpandPath(currentPath,environment);

    for (vector<Path>::iterator it = extendedPaths.begin(); it != extendedPaths.end(); it++) {
      if( it->getEnd() == environment.getGoal() ){
        path = *it;
        return(true);
      }
      else
        frontier.push(*it);
    }
    //environment.Print(currentPath);
  }while( !frontier.empty() );

  return(false);
}

// Depth-First searching algorithm
bool DepthFirst( const Environment &environment, Path &path ){

  stack<Path> frontier;
  Path currentPath(environment.getStart());

  do{
    if( !frontier.empty() ){
      currentPath = frontier.top();
      frontier.pop();
    }

    vector<Path> extendedPaths;
    extendedPaths = ExpandPath(currentPath,environment);

    for (vector<Path>::iterator it = extendedPaths.begin(); it != extendedPaths.end(); it++) {
      if( it->getEnd() == environment.getGoal() ){
        path = *it;
        return(true);
      }
      else
        frontier.push(*it);
    }
    //environment.Print(currentPath);
  }while( !frontier.empty() );

  return(false);
}

int main(int argc, char const *argv[]) {
  Environment environment(argv[1]);
  cout << "Nodo INICIAL: <" << environment.getStart().first << "," << environment.getStart().second  << ">"<<  endl;
  environment.Print();
  cout << endl;
  Path path_b(environment.getStart());
  Path path_d(environment.getStart());


  cout << "Breadth-First algorithm:" << endl;
  BreadthFirst(environment,path_b);
  cout << "Path length --> " << path_b.getLength() << endl;
  environment.Print(path_b);

  cout << "Depth-First algorithm:" << endl;
  DepthFirst(environment,path_d);
  cout << "Path length --> " << path_d.getLength() << endl;
  environment.Print(path_d);

  return(0);

}
