
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <stack>            // std::stack
#include <vector>           // std::vector

#include "blind_search.h"

using namespace std;

// Expands a Path checking the four adjacent positions
vector<Path> ExpandPath( const Path &currentPath, const Environment &environment, bool[][] &unreachedPositions ){
  Path auxPath(environment.getStart());
  vector<Path> paths;

  if( environment.isValidPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) &&
      !currentPath.containsPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) ){
        if(currentPath.getEnd().first+1 == environment.getPortal(0).first && currentPath.getEnd().second == environment.getPortal(0).second){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
          paths.push_back(auxPath);
        }
        else if((currentPath.getEnd().first+1 == environment.getPortal(1).first) && (currentPath.getEnd().second == environment.getPortal(1).second)){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
          paths.push_back(auxPath);
        }
        else if(currentPath.getEnd().first+1 == environment.getPortal(2).first && currentPath.getEnd().second == environment.getPortal(2).second){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
          paths.push_back(auxPath);
        }
        else if((currentPath.getEnd().first+1 == environment.getPortal(3).first) && (currentPath.getEnd().second == environment.getPortal(3).second)){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
          paths.push_back(auxPath);
        }
        else{
          auxPath = currentPath;
          auxPath.addPosition(currentPath.getEnd().first+1,currentPath.getEnd().second);
          paths.push_back(auxPath);
        }
  }
  if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) &&
      !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) ){
        if(currentPath.getEnd().first == environment.getPortal(0).first && currentPath.getEnd().second+1 == environment.getPortal(0).second){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
          paths.push_back(auxPath);
        }
        else if((currentPath.getEnd().first == environment.getPortal(1).first) && (currentPath.getEnd().second+1 == environment.getPortal(1).second)){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
          paths.push_back(auxPath);
        }
        else if(currentPath.getEnd().first == environment.getPortal(2).first && currentPath.getEnd().second+1 == environment.getPortal(2).second){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
          paths.push_back(auxPath);
        }
        else if((currentPath.getEnd().first == environment.getPortal(3).first) && (currentPath.getEnd().second+1 == environment.getPortal(3).second)){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
          paths.push_back(auxPath);
        }
        else{
     auxPath = currentPath;
     auxPath.addPosition(currentPath.getEnd().first,currentPath.getEnd().second+1);
     paths.push_back(auxPath);
   }
  }
  if( environment.isValidPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) &&
      !currentPath.containsPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) ){
        if(currentPath.getEnd().first-1 == environment.getPortal(0).first && currentPath.getEnd().second == environment.getPortal(0).second){
        auxPath = currentPath;
        auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        paths.push_back(auxPath);
      }
      else if((currentPath.getEnd().first-1 == environment.getPortal(1).first) && (currentPath.getEnd().second == environment.getPortal(1).second)){
        auxPath = currentPath;
        auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        paths.push_back(auxPath);
      }
      else if(currentPath.getEnd().first-1 == environment.getPortal(2).first && currentPath.getEnd().second == environment.getPortal(2).second){
        auxPath = currentPath;
        auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        paths.push_back(auxPath);
      }
      else if((currentPath.getEnd().first-1 == environment.getPortal(3).first) && (currentPath.getEnd().second == environment.getPortal(3).second)){
        auxPath = currentPath;
        auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        paths.push_back(auxPath);
      }
      else{
       auxPath = currentPath;
       auxPath.addPosition(currentPath.getEnd().first-1,currentPath.getEnd().second);
       paths.push_back(auxPath);
     }
  }
  if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) &&
      !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) ){
        if(currentPath.getEnd().first == environment.getPortal(0).first && currentPath.getEnd().second-1 == environment.getPortal(0).second){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
          paths.push_back(auxPath);
        }
        else if((currentPath.getEnd().first == environment.getPortal(1).first) && (currentPath.getEnd().second-1 == environment.getPortal(1).second)){
          auxPath = currentPath;
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
          paths.push_back(auxPath);
        }
        else if(currentPath.getEnd().first == environment.getPortal(2).first && currentPath.getEnd().second-1 == environment.getPortal(2).second){
            auxPath = currentPath;
            auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
            paths.push_back(auxPath);
          }
        else if((currentPath.getEnd().first == environment.getPortal(3).first) && (currentPath.getEnd().second-1 == environment.getPortal(3).second)){
            auxPath = currentPath;
            auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
            paths.push_back(auxPath);
          }
        else{
         auxPath = currentPath;
         auxPath.addPosition(currentPath.getEnd().first,currentPath.getEnd().second-1);
         paths.push_back(auxPath);
       }
  }
  return(paths);
}

// Breadth-First searching algorithm
bool BreadthFirst( const Environment &environment, Path &path ){

  queue<Path> frontier;
  Path currentPath(environment.getStart());
  bool unreachedPositions[environment.getRows()][environment.getColumns()];

  for (size_t i = 0; i < environment.getRows(); i++)
    for (size_t j = 0; j < environment.getColumns(); j++)
      unreachedPositions[i][j] = true;

  for (size_t i = 0; i < environment.getRows(); i++){
    for (size_t j = 0; j < environment.getColumns(); j++){
      cout << unreachedPositions[i][j];
    }
    cout << endl;
  }

  do{
    if( !frontier.empty() ){
      currentPath = frontier.front();
      frontier.pop();
    }

    vector<Path> extendedPaths;
    extendedPaths = ExpandPath(currentPath,environment,unreachedPositions);

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
  bool unreachedPositions[environment.getRows()][environment.getColumns()];

  for (size_t i = 0; i < environment.getRows(); i++)
    for (size_t j = 0; j < environment.getColumns(); j++)
      unreachedPositions[i][j] = true;

  do{
    if( !frontier.empty() ){
      currentPath = frontier.top();
      frontier.pop();
    }

    vector<Path> extendedPaths;
    extendedPaths = ExpandPath(currentPath,environment,unreachedPositions);

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

  if(argc != 2){
    cerr << "ERROR:Missing txt file" << endl;
    return (1);
  }
  Environment environment(argv[1]);
  cout << "INITIAL NODE: <" << environment.getStart().first << "," << environment.getStart().second  << ">"<<  endl;
  cout << "GOAL NODE: <" << environment.getGoal().first << "," << environment.getGoal().second  << ">"<<  endl;

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
