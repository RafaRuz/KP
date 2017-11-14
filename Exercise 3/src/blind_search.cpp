
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <stack>            // std::stack

#include "blind_search.h"

using namespace std;


// Breadth-First searching algorithm
bool BreadthFirst( const Environment environment, Path &path ){

  queue<Path> frontier;
  Path currentPath(environment.getStart());
  Path auxPath(environment.getStart());
  pair<unsigned int,unsigned int> start = environment.getStart();

  if( environment.isValidPosition(start.first+1,start.second) ){
    auxPath = currentPath;
    auxPath.addMovement(South);
    frontier.push(auxPath);
  }
  if( environment.isValidPosition(start.first,start.second+1) ){
    auxPath = currentPath;
    auxPath.addMovement(East);
    frontier.push(auxPath);
  }
  if( environment.isValidPosition(start.first-1,start.second) ){
    auxPath = currentPath;
    auxPath.addMovement(North);
    frontier.push(auxPath);
  }
  if( environment.isValidPosition(start.first,start.second-1) ){
    auxPath = currentPath;
    auxPath.addMovement(West);
    frontier.push(auxPath);
  }


  while( !frontier.empty() ){
    currentPath = frontier.front();
    frontier.pop();
    environment.Print(currentPath);

    if( environment.isValidPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) &&
        !currentPath.containsPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) ){
      auxPath = currentPath;
      auxPath.addMovement(South);

      if( auxPath.getEnd() == environment.getGoal() ){
        path = auxPath;
        return(true);
      }

      frontier.push(auxPath);
    }
    if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) &&
             !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) ){
       auxPath = currentPath;
       auxPath.addMovement(East);

       if( auxPath.getEnd() == environment.getGoal() ){
         path = auxPath;
         return(true);
       }

       frontier.push(auxPath);
    }
    if( environment.isValidPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) &&
             !currentPath.containsPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) ){
       auxPath = currentPath;
       auxPath.addMovement(North);

       if( auxPath.getEnd() == environment.getGoal() ){
         path = auxPath;
         return(true);
       }

       frontier.push(auxPath);
    }
    if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) &&
             !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) ){
       auxPath = currentPath;
       auxPath.addMovement(West);

       if( auxPath.getEnd() == environment.getGoal() ){
         path = auxPath;
         return(true);
       }

       frontier.push(auxPath);
    }
  }
  return(false);
}

//
bool DepthFirst( Environment environment, Path &path ){

  stack<Path> frontier;
  Path currentPath(environment.getStart());
  Path auxPath(environment.getStart());
  pair<unsigned int,unsigned int> start = environment.getStart();

  if( environment.isValidPosition(start.first-1,start.second) ){
    auxPath = currentPath;
    auxPath.addMovement(North);
    frontier.push(auxPath);
  }
  if( environment.isValidPosition(start.first,start.second+1) ){
    auxPath = currentPath;
    auxPath.addMovement(East);
    frontier.push(auxPath);
  }
  if( environment.isValidPosition(start.first+1,start.second) ){
    auxPath = currentPath;
    auxPath.addMovement(South);
    frontier.push(auxPath);
  }
  if( environment.isValidPosition(start.first,start.second-1) ){
    auxPath = currentPath;
    auxPath.addMovement(West);
    frontier.push(auxPath);
  }


  while( !frontier.empty() ){
    currentPath = frontier.top();
    frontier.pop();
    environment.Print(currentPath);

    if( environment.isValidPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) &&
        !currentPath.containsPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) ){
      auxPath = currentPath;
      auxPath.addMovement(North);

      if( auxPath.getEnd() == environment.getGoal() ){
        path = auxPath;
        return(true);
      }

      frontier.push(auxPath);
    }
    if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) &&
             !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) ){
       auxPath = currentPath;
       auxPath.addMovement(East);

       if( auxPath.getEnd() == environment.getGoal() ){
         path = auxPath;
         return(true);
       }

       frontier.push(auxPath);
    }
    if( environment.isValidPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) &&
             !currentPath.containsPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) ){
       auxPath = currentPath;
       auxPath.addMovement(South);

       if( auxPath.getEnd() == environment.getGoal() ){
         path = auxPath;
         return(true);
       }

       frontier.push(auxPath);
    }
    if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) &&
             !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) ){
       auxPath = currentPath;
       auxPath.addMovement(West);

       if( auxPath.getEnd() == environment.getGoal() ){
         path = auxPath;
         return(true);
       }

       frontier.push(auxPath);
    }
  }
  return(false);
}

int main(int argc, char const *argv[]) {
  Environment environment("./txt/blatt4_environment_a.txt");
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
