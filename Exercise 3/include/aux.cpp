void DepthFirst( Environment environment, Path &path ){

  // Toma linea guapa pa ti
  // Toma segunda linea guapa pa ti
  // Ola q ase
    stack<Path> frontier;
    Path currentPath(environment.getStart());
    pair<unsigned int,unsigned int> start = environment.getStart();
    if( environment.isValidPosition(start.first,start.second+1))
      currentPath.addMovement(North);
    else if( environment.isValidPosition(start.first+1,start.second))
      currentPath.addMovement(East);
    else if( environment.isValidPosition(start.first,start.second-1))
      currentPath.addMovement(South);
    else if( environment.isValidPosition(start.first-1,start.second))
      currentPath.addMovement(West);

    frontier.push(currentPath);
    Path auxPath(environment.getStart());

    while( !frontier.empty() ){
      currentPath = frontier.top();
      frontier.pop();

      if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) &&
          !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second+1) ){
        auxPath = currentPath;
        auxPath.addMovement(North);

        if( auxPath.getEnd() == environment.getGoal() ){
          path = auxPath;
          return(true);
        }

        frontier.push(auxPath);
      }
      else if( environment.isValidPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) &&
               !currentPath.containsPosition(currentPath.getEnd().first+1,currentPath.getEnd().second) ){
         auxPath = currentPath;
         auxPath.addMovement(East);

         if( auxPath.getEnd() == environment.getGoal() ){
           path = auxPath;
           return(true);
         }

         frontier.push(auxPath);
      }
      else if( environment.isValidPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) &&
               !currentPath.containsPosition(currentPath.getEnd().first,currentPath.getEnd().second-1) ){
         auxPath = currentPath;
         auxPath.addMovement(South);

         if( auxPath.getEnd() == environment.getGoal() ){
           path = auxPath;
           return(true);
         }

         frontier.push(auxPath);
      }
      else if( environment.isValidPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) &&
               !currentPath.containsPosition(currentPath.getEnd().first-1,currentPath.getEnd().second) ){
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
