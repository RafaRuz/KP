#include "pathComparison.h"
#include "environment.h"
#include "path.h"

#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <stack>            // std::stack
#include <vector>           // std::vector
#include <ctime>            //time


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

        if( environment.getElement(currentX+1,currentY) > '0' && environment.getElement(currentX+1,currentY) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX+1,currentY) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX+1,currentY) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            unreachedPositions[environment.getPortal(2*numPortal-2).first][environment.getPortal(2*numPortal-2).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            unreachedPositions[environment.getPortal(2*numPortal-1).first][environment.getPortal(2*numPortal-1).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
          auxPath.addPosition(currentX+1,currentY);

        unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY+1) &&
      !currentPath.containsPosition(currentX,currentY+1) &&
      unreachedPositions[currentX][currentY+1]){
        auxPath = currentPath;

        if( environment.getElement(currentX,currentY+1) > '0' && environment.getElement(currentX,currentY+1) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX,currentY+1) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX,currentY+1) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            unreachedPositions[environment.getPortal(2*numPortal-2).first][environment.getPortal(2*numPortal-2).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            unreachedPositions[environment.getPortal(2*numPortal-1).first][environment.getPortal(2*numPortal-1).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
          auxPath.addPosition(currentX,currentY+1);

        unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX-1,currentY) &&
      !currentPath.containsPosition(currentX-1,currentY) &&
      unreachedPositions[currentX-1][currentY]){
        auxPath = currentPath;

        if( environment.getElement(currentX-1,currentY) >= '0' && environment.getElement(currentX-1,currentY) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX-1,currentY) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX-1,currentY) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            unreachedPositions[environment.getPortal(2*numPortal-2).first][environment.getPortal(2*numPortal-2).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            unreachedPositions[environment.getPortal(2*numPortal-1).first][environment.getPortal(2*numPortal-1).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
         auxPath.addPosition(currentX-1,currentY);

       unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
       paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY-1) &&
      !currentPath.containsPosition(currentX,currentY-1) &&
      unreachedPositions[currentX][currentY-1]){
        auxPath = currentPath;

        if( environment.getElement(currentX,currentY-1) >= '0' && environment.getElement(currentX,currentY-1) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX,currentY-1) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX,currentY-1) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            unreachedPositions[environment.getPortal(2*numPortal-2).first][environment.getPortal(2*numPortal-2).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            unreachedPositions[environment.getPortal(2*numPortal-1).first][environment.getPortal(2*numPortal-1).second] = false;
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
         auxPath.addPosition(currentX,currentY-1);

       unreachedPositions[auxPath.getEnd().first][auxPath.getEnd().second] = false;
       paths.push_back(auxPath);
  }
  return(paths);
}

// Expands a Path checking the four adjacent positions (Without multi-path pruning)
vector<Path> ExpandPath( const Path &currentPath, const Environment &environment ){
  Path auxPath(environment.getStart());
  vector<Path> paths;
  unsigned int currentX = currentPath.getEnd().first;
  unsigned int currentY = currentPath.getEnd().second;

  if( environment.isValidPosition(currentX+1,currentY) &&
      !currentPath.containsPosition(currentX+1,currentY) ){
        auxPath = currentPath;

        if( environment.getElement(currentX+1,currentY) > '0' && environment.getElement(currentX+1,currentY) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX+1,currentY) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX+1,currentY) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
          auxPath.addPosition(currentX+1,currentY);

        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY+1) &&
      !currentPath.containsPosition(currentX,currentY+1) ){
        auxPath = currentPath;

        if( environment.getElement(currentX,currentY+1) > '0' && environment.getElement(currentX,currentY+1) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX,currentY+1) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX,currentY+1) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
          auxPath.addPosition(currentX,currentY+1);

        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX-1,currentY) &&
      !currentPath.containsPosition(currentX-1,currentY) ){
        auxPath = currentPath;

        if( environment.getElement(currentX-1,currentY) >= '0' && environment.getElement(currentX-1,currentY) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX-1,currentY) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX-1,currentY) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
         auxPath.addPosition(currentX-1,currentY);

       paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY-1) &&
      !currentPath.containsPosition(currentX,currentY-1) ){
        auxPath = currentPath;

        if( environment.getElement(currentX,currentY-1) >= '0' && environment.getElement(currentX,currentY-1) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX,currentY-1) - '0';
          if( environment.getPortal(2*numPortal-2) == std::make_pair(currentX,currentY-1) ){
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(2*numPortal-1).first,environment.getPortal(2*numPortal-1).second);
            auxPath.addPosition(environment.getPortal(2*numPortal-2).first,environment.getPortal(2*numPortal-2).second);
          }
        }
        else
         auxPath.addPosition(currentX,currentY-1);

       paths.push_back(auxPath);
  }
  return(paths);
}

// Breadth-First searching algorithm
bool BreadthFirst( const Environment &environment, Path &path ){

  queue<Path> frontier;
  Path currentPath(environment.getStart());
  bool** unreachedPositions = new bool*[environment.getRows()];
  unsigned int maxNodes = 0;

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
    //environment.Print(currentPath);

    vector<Path> extendedPaths;
    extendedPaths = ExpandPath(currentPath,environment,unreachedPositions);

    for (vector<Path>::iterator it = extendedPaths.begin(); it != extendedPaths.end(); it++) {
      if( it->getEnd() == environment.getGoal() ){
        path = *it;
        for (size_t i = 0; i < environment.getRows(); i++)
          delete[] unreachedPositions[i];
        delete[] unreachedPositions;
        cout << "Maximum number of paths in the frontier: " << maxNodes << endl;
        return(true);
      }
      else
        frontier.push(*it);

      if( frontier.size() > maxNodes ) maxNodes = frontier.size();
    }
  }while( !frontier.empty() );

  for (size_t i = 0; i < environment.getRows(); i++)
    delete[] unreachedPositions[i];
  delete[] unreachedPositions;

  cout << "Maximum number of paths in the frontier: " << maxNodes << endl;
  return(false);
}

// Depth-First searching algorithm
bool DepthFirst( const Environment &environment, Path &path ){

  stack<Path> frontier;
  Path currentPath(environment.getStart());
  bool** unreachedPositions = new bool*[environment.getRows()];
  unsigned int maxNodes = 0;

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
    //environment.Print(currentPath);

    vector<Path> extendedPaths;
    extendedPaths = ExpandPath(currentPath,environment,unreachedPositions);

    for (vector<Path>::iterator it = extendedPaths.begin(); it != extendedPaths.end(); it++) {
      if( it->getEnd() == environment.getGoal() ){
        path = *it;
        for (size_t i = 0; i < environment.getRows(); i++)
          delete[] unreachedPositions[i];
        delete[] unreachedPositions;
        cout << "Maximum number of paths in the frontier: " << maxNodes << endl;
        return(true);
      }
      else
        frontier.push(*it);

      if( maxNodes < frontier.size() ) maxNodes = frontier.size();
    }
  }while( !frontier.empty() );

  for (size_t i = 0; i < environment.getRows(); i++)
    delete[] unreachedPositions[i];
  delete[] unreachedPositions;

  cout << "Maximum number of paths in the frontier: " << maxNodes << endl;
  return(false);
}

// A* algorithm
bool AStar( const Environment &environment, Path &path ){
  priority_queue<Path,vector<Path>,PathComparison> frontier(PathComparison(environment.getGoal(),&environment,true));
  Path currentPath(environment.getStart());
  bool** unreachedPositions = new bool*[environment.getRows()];
  unsigned int maxNodes = 0;

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
    //environment.Print(currentPath);

    vector<Path> extendedPaths;
    extendedPaths = ExpandPath(currentPath,environment,unreachedPositions);

    for (vector<Path>::iterator it = extendedPaths.begin(); it != extendedPaths.end(); it++) {
      if( it->getEnd() == environment.getGoal() ){
        path = *it;
        for (size_t i = 0; i < environment.getRows(); i++)
          delete[] unreachedPositions[i];
        delete[] unreachedPositions;
        cout << "Maximum number of paths in the frontier: " << maxNodes << endl;
        return(true);
      }
      else
        frontier.push(*it);

      if( maxNodes < frontier.size() ) maxNodes = frontier.size();
    }
  }while( !frontier.empty() );

  for (size_t i = 0; i < environment.getRows(); i++)
    delete[] unreachedPositions[i];
  delete[] unreachedPositions;

  cout << "Maximum number of paths in the frontier: " << maxNodes << endl;
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
  Path path_b;
  Path path_d;
  Path path_a;

double t1, t2;


  cout << endl << "Breadth-First algorithm:" << endl;
  t1 = clock();
  if( BreadthFirst(environment,path_b) ){
    t2 = clock();
    cout << "Path length --> " << path_b.getLength() << endl;
    environment.Print(path_b);
    cout << "Ejecution time: " << (t2-t1)/CLOCKS_PER_SEC << endl;
  }
  else cout << "Path not found using Breadth-First algorithm." << endl;



  cout << endl << "Depth-First algorithm:" << endl;
  t1 = clock();
  if( DepthFirst(environment,path_d) ){
    t2 = clock();
    cout << "Path length --> " << path_d.getLength() << endl;
    environment.Print(path_d);
    cout << "Ejecution time: " << (t2-t1)/CLOCKS_PER_SEC << endl;
  }
  else cout << "Path not found using Depth-First algorithm." << endl;

  cout << endl << "A* algorithm:" << endl;
  t1 = clock();
  if( AStar(environment,path_d) ){
    t2 = clock();
    cout << "Path length --> " << path_d.getLength() << endl;
    environment.Print(path_d);
    cout << "Ejecution time: " << (t2-t1)/CLOCKS_PER_SEC << endl;
  }
  else cout << "Path not found using A* algorithm." << endl;

  return(0);

}
