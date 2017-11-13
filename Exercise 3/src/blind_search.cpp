
#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
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
void DepthFirst( Environment environment, Path &path ){


}



int main(int argc, char const *argv[]) {
  Environment environment("./txt/blatt3_environment.txt");
  cout << "Nodo INICIAL: <" << environment.getStart().first << "," << environment.getStart().second  << ">"<<  endl;
  environment.Print();
  cout << endl;/*
  cout << "Pruebas PATH" << endl;

  Path p(environment.getStart());

  p.addMovement(North);
  p.addMovement(East);
  p.addMovement(South);
  cout << p.containsPosition(environment.getStart().first,environment.getStart().second-1) << endl;
  cout << p.containsPosition(environment.getStart().first+1,environment.getStart().second-1) << endl;
  cout << p.containsPosition(environment.getStart().first+1,environment.getStart().second) << endl;
  cout << p.containsPosition(environment.getStart().first,environment.getStart().second) << endl;



  cout << "Pruebas ENVIRONMENT" << endl;
  for (unsigned int i = 0; i < 18; i++) {
    cout << environment.isValidPosition(environment.getStart().first,environment.getStart().second+i) << endl;

  }*/



  Path path(environment.getStart());
  //BreadthFirst(environment,path);
  path.addMovement(North);

  cout << "Path length --> " << path.getLength() << endl;

  cout << "Breadth-First algorithm:" << endl;
  environment.Print(path);
  return(0);

}
