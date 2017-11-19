
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <stack>            // std::stack
#include <vector>           // std::vector

#include "blind_search.h"

using namespace std;

// Expands a Path checking the four adjacent positions
vector<Path> ExpandPath( const Path &currentPath, const Environment &environment, bool** &unreachedPositions ){
  Path auxPath(environment.getStart());
  vector<Path> paths;
  unsigned int currentX = currentPath.getEnd().first;
  unsigned int currentY = currentPath.getEnd().second;

  if( environment.isValidPosition(currentX+1,currentY) &&
      !currentPath.containsPosition(currentX+1,currentY) &&
      unreachedPositions[currentX+1][currentY] ){
        auxPath = currentPath;

        if( currentX+1 == environment.getPortal(0).first && currentY == environment.getPortal(0).second )
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        else if((currentX+1 == environment.getPortal(1).first) && (currentY == environment.getPortal(1).second))
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        else if(currentX+1 == environment.getPortal(2).first && currentY == environment.getPortal(2).second)
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        else if((currentX+1 == environment.getPortal(3).first) && (currentY == environment.getPortal(3).second))
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        else
          auxPath.addPosition(currentX+1,currentY);

        unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY+1) &&
      !currentPath.containsPosition(currentX,currentY+1) &&
      unreachedPositions[currentX][currentY+1]){
        auxPath = currentPath;

        if(currentX == environment.getPortal(0).first && currentY+1 == environment.getPortal(0).second)
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        else if((currentX == environment.getPortal(1).first) && (currentY+1 == environment.getPortal(1).second))
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        else if(currentX == environment.getPortal(2).first && currentY+1 == environment.getPortal(2).second)
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        else if((currentX == environment.getPortal(3).first) && (currentY+1 == environment.getPortal(3).second))
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        else
          auxPath.addPosition(currentX,currentY+1);

        unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX-1,currentY) &&
      !currentPath.containsPosition(currentX-1,currentY) &&
      unreachedPositions[currentX-1][currentY]){
        auxPath = currentPath;

        if(currentX-1 == environment.getPortal(0).first && currentY == environment.getPortal(0).second)
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        else if((currentX-1 == environment.getPortal(1).first) && (currentY == environment.getPortal(1).second))
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        else if(currentX-1 == environment.getPortal(2).first && currentY == environment.getPortal(2).second)
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        else if((currentX-1 == environment.getPortal(3).first) && (currentY == environment.getPortal(3).second))
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        else
         auxPath.addPosition(currentX-1,currentY);

       unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
       paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY-1) &&
      !currentPath.containsPosition(currentX,currentY-1) &&
      unreachedPositions[currentX][currentY-1]){
        auxPath = currentPath;

        if(currentX == environment.getPortal(0).first && currentY-1 == environment.getPortal(0).second)
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        else if((currentX == environment.getPortal(1).first) && (currentY-1 == environment.getPortal(1).second))
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        else if(currentX == environment.getPortal(2).first && currentY-1 == environment.getPortal(2).second)
            auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        else if((currentX == environment.getPortal(3).first) && (currentY-1 == environment.getPortal(3).second))
            auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        else
         auxPath.addPosition(currentX,currentY-1);

       unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
       paths.push_back(auxPath);
  }
  return(paths);
}

// Breadth-First searching algorithm
bool BreadthFirst( const Environment &environment, Path &path ){

  queue<Path> frontier;
  Path currentPath(environment.getStart());
  bool** unreachedPositions = new bool*[environment.getRows()];

  for (size_t i = 0; i < environment.getRows(); i++)
    unreachedPositions[i] = new bool[environment.getColumns()];

  for (size_t i = 0; i < environment.getRows(); i++)
    for (size_t j = 0; j < environment.getColumns(); j++)
      unreachedPositions[i][j] = true;

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
        for (size_t i = 0; i < environment.getRows(); i++)
          delete[] unreachedPositions[i];
        delete[] unreachedPositions;
        return(true);
      }
      else
        frontier.push(*it);
    }
    //environment.Print(currentPath);
  }while( !frontier.empty() );

  for (size_t i = 0; i < environment.getRows(); i++)
    delete[] unreachedPositions[i];
  delete[] unreachedPositions;

  return(false);
}

// Depth-First searching algorithm
bool DepthFirst( const Environment &environment, Path &path ){

  stack<Path> frontier;
  Path currentPath(environment.getStart());
  bool** unreachedPositions = new bool*[environment.getRows()];

  for (size_t i = 0; i < environment.getRows(); i++)
    unreachedPositions[i] = new bool[environment.getColumns()];

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
        for (size_t i = 0; i < environment.getRows(); i++)
          delete[] unreachedPositions[i];
        delete[] unreachedPositions;
        return(true);
      }
      else
        frontier.push(*it);
    }
    //environment.Print(currentPath);
  }while( !frontier.empty() );

  for (size_t i = 0; i < environment.getRows(); i++)
    delete[] unreachedPositions[i];
  delete[] unreachedPositions;

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
