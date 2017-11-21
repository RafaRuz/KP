#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <stack>            // std::stack
#include <vector>           // std::vector
#include <sys/resource.h>   // rusage

#include "pathComparison.h"
#include "environment.h"
#include "path.h"
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

  int who = RUSAGE_SELF;
  struct rusage usage;
  int ret;




  cout << endl << "Breadth-First algorithm:" << endl;
  if( BreadthFirst(environment,path_b) ){
    cout << "Path length --> " << path_b.getLength() << endl;
    environment.Print(path_b);
  }
  else cout << "Path not found using Breadth-First algorithm." << endl;

  cout << endl << "Depth-First algorithm:" << endl;
  if( DepthFirst(environment,path_d) ){
    cout << "Path length --> " << path_d.getLength() << endl;
    environment.Print(path_d);
  }
  else cout << "Path not found using Depth-First algorithm." << endl;

  cout << endl << "A* algorithm:" << endl;
  if( AStar(environment,path_d) ){
    cout << "Path length --> " << path_d.getLength() << endl;
    environment.Print(path_d);
  }
  else cout << "Path not found using A* algorithm." << endl;

   /*ret = getrusage(who, &usage);

   cout <<   usage.ru_utime.tv_usec <<  " --> user CPU microseconds used"  << endl;
   cout <<   usage.ru_stime.tv_usec <<  " --> system CPU microseconds used"  << endl;
   cout <<   usage.ru_maxrss <<  " --> maximum resident set size"  << endl;
   cout <<   usage.ru_ixrss <<  " --> integral shared memory size"  << endl;
   cout <<   usage.ru_idrss <<  " --> integral unshared data size "  << endl;
   cout <<   usage.ru_isrss <<  " --> integral unshared stack size"  << endl;
   cout <<   usage.ru_minflt <<  " --> page reclaims (soft page faults)"  << endl;
   cout <<   usage.ru_majflt <<  " --> page faults (hard page faults)"  << endl;
   cout <<   usage.ru_nswap <<  " --> swaps"  << endl;
   cout <<   usage.ru_inblock <<  " --> block input operations"  << endl;
   cout <<   usage.ru_oublock <<  " --> block output operations"  << endl;
   cout <<   usage.ru_msgsnd << " -->  IPC messages sent"  << endl;
   cout <<   usage.ru_msgrcv <<  " --> IPC messages received"  << endl;
   cout <<   usage.ru_nsignals <<  " --> signals received"  << endl;
   cout <<   usage.ru_nvcsw <<  " --> voluntary context switches"  << endl;
   cout <<   usage.ru_nivcsw <<  " --> involuntary context switches"  << endl;*/

  return(0);

}
