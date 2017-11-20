#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <stack>            // std::stack
#include <vector>           // std::vector

#include "blind_search.h"

using namespace std;

class PathComparison{
  private:
    pair<unsigned int,unsigned int> goal;
    const Environment* environment;
    bool reverse;
  public:
    PathComparison( const pair<unsigned int,unsigned int> &g, const Environment* env,
                    const bool& revparam=false):reverse(revparam),goal(g),environment(env){}

    PathComparison(const unsigned int &x, const unsigned int &y, const Environment* env,
                    const bool& revparam=false):reverse(revparam),environment(env){
      goal = std::make_pair(x,y);
    }

    bool operator() (const Path &p, const Path &q) const{
      if (reverse) return (p.estimation(goal,environment->getPortals())>q.estimation(goal,environment->getPortals()));
      else return (p.estimation(goal,environment->getPortals())<q.estimation(goal,environment->getPortals()));
    }
};

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

        if( environment.getElement(currentX+1,currentY) >= '0' && environment.getElement(currentX+1,currentY) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX+1,currentY) - '0';
          if( numPortal%2 ){
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal-1).first,environment.getPortal(numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal+1).first,environment.getPortal(numPortal+1).second);
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

        if( environment.getElement(currentX,currentY+1) >= '0' && environment.getElement(currentX,currentY+1) <= '9' ){
          unsigned int numPortal = environment.getElement(currentX,currentY+1) - '0';
          if( numPortal%2 ){
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal-1).first,environment.getPortal(numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal+1).first,environment.getPortal(numPortal+1).second);
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
          if( numPortal%2 ){
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal-1).first,environment.getPortal(numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal+1).first,environment.getPortal(numPortal+1).second);
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
          if( numPortal%2 ){
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal-1).first,environment.getPortal(numPortal-1).second);
          }
          else{
            auxPath.addPosition(environment.getPortal(numPortal).first,environment.getPortal(numPortal).second);
            unreachedPositions[environment.getPortal(numPortal).first][environment.getPortal(numPortal).second] = false;
            auxPath.addPosition(environment.getPortal(numPortal+1).first,environment.getPortal(numPortal+1).second);
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

        if( currentX+1 == environment.getPortal(0).first && currentY == environment.getPortal(0).second ){
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        }
        else if((currentX+1 == environment.getPortal(1).first) && (currentY == environment.getPortal(1).second)){
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        }
        else if(currentX+1 == environment.getPortal(2).first && currentY == environment.getPortal(2).second){
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        }
        else if((currentX+1 == environment.getPortal(3).first) && (currentY == environment.getPortal(3).second)){
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        }
        else
          auxPath.addPosition(currentX+1,currentY);

        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY+1) &&
      !currentPath.containsPosition(currentX,currentY+1) ){
        auxPath = currentPath;

        if( currentX == environment.getPortal(0).first && currentY+1 == environment.getPortal(0).second ){
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        }
        else if((currentX == environment.getPortal(1).first) && (currentY+1 == environment.getPortal(1).second)){
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        }
        else if(currentX == environment.getPortal(2).first && currentY+1 == environment.getPortal(2).second){
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        }
        else if((currentX == environment.getPortal(3).first) && (currentY+1 == environment.getPortal(3).second)){
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        }
        else
          auxPath.addPosition(currentX,currentY+1);

        paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX-1,currentY) &&
      !currentPath.containsPosition(currentX-1,currentY) ){
        auxPath = currentPath;

        if( currentX-1 == environment.getPortal(0).first && currentY == environment.getPortal(0).second ){
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        }
        else if((currentX-1 == environment.getPortal(1).first) && (currentY == environment.getPortal(1).second)){
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        }
        else if(currentX-1 == environment.getPortal(2).first && currentY == environment.getPortal(2).second){
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        }
        else if((currentX-1 == environment.getPortal(3).first) && (currentY == environment.getPortal(3).second)){
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
        }
        else
         auxPath.addPosition(currentX-1,currentY);

       paths.push_back(auxPath);
  }
  if( environment.isValidPosition(currentX,currentY-1) &&
      !currentPath.containsPosition(currentX,currentY-1) ){
        auxPath = currentPath;

        if( currentX == environment.getPortal(0).first && currentY-1 == environment.getPortal(0).second ){
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
        }
        else if((currentX == environment.getPortal(1).first) && (currentY-1 == environment.getPortal(1).second)){
          auxPath.addPosition(environment.getPortal(1).first,environment.getPortal(1).second);
          auxPath.addPosition(environment.getPortal(0).first,environment.getPortal(0).second);
        }
        else if(currentX == environment.getPortal(2).first && currentY-1 == environment.getPortal(2).second){
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
        }
        else if((currentX == environment.getPortal(3).first) && (currentY-1 == environment.getPortal(3).second)){
          auxPath.addPosition(environment.getPortal(3).first,environment.getPortal(3).second);
          auxPath.addPosition(environment.getPortal(2).first,environment.getPortal(2).second);
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
    extendedPaths = ExpandPath(currentPath,environment);

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

// A* algorithm
bool AStar( const Environment &environment, Path &path ){
  priority_queue<Path,vector<Path>,PathComparison> frontier(PathComparison(environment.getGoal(),&environment,true));
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
    if(currentPath.getLength()>1)environment.Print(currentPath);

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
  Path path_b;
  Path path_d;
  Path path_a;


  cout << "Breadth-First algorithm:" << endl;
  if( BreadthFirst(environment,path_b) ){
    cout << "Path length --> " << path_b.getLength() << endl;
    environment.Print(path_b);
  }
  else cout << "Path not found using Breadth-First algorithm." << endl;

  cout << "Depth-First algorithm:" << endl;
  if( DepthFirst(environment,path_d) ){
    cout << "Path length --> " << path_d.getLength() << endl;
    environment.Print(path_d);
  }
  else cout << "Path not found using Depth-First algorithm." << endl;

  cout << "A* algorithm:" << endl;
  if( AStar(environment,path_d) ){
    cout << "Path length --> " << path_d.getLength() << endl;
    environment.Print(path_d);
  }
  else cout << "Path not found using A* algorithm." << endl;

  return(0);

}
