#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <cstdio>

using namespace std;


// Enumeration representing the possible directions, needed to define a path
enum Direction { North, East, South, West };

// Class representing a path between 2 positions
class Path{
  private:
    pair<unsigned int,unsigned int> start,end;
    list<Direction> movements;
    unsigned int length;

  public:
    // Constructor for an empty Path
    Path():length(0){}

    // Constructor for an empty path with a start defined
    Path( const pair<unsigned int,unsigned int> s ):length(0), start(s), end(s){}

    // Start getter
    inline pair<unsigned int,unsigned int> getStart() const{
      return(start);
    }

    // End getter
    inline pair<unsigned int,unsigned int> getEnd() const{
      return(end);
    }

    // Movements getter
    inline list<Direction> getMovements() const{
      return(movements);
    }

    // Length getter
    inline unsigned int getLength() const{
      return(length);
    }

    // Add a movement to the path
    void addMovement( const Direction dir ){
      movements.push_back(dir);
      length++;

      if( dir == North )
        end = pair<unsigned int,unsigned int>(end.first-1,end.second);
      else if( dir == East )
        end = pair<unsigned int,unsigned int>(end.first,end.second+1);
      else if( dir == South )
        end = pair<unsigned int,unsigned int>(end.first+1,end.second);
      else
        end = pair<unsigned int,unsigned int>(end.first,end.second-1);
    }

    // Check if a position is already in the path or not
    bool containsPosition( pair<unsigned int, unsigned int> position ){
      return(containsPosition(position.first,position.second));
    }

    // Check if a position is already in the path or not
    bool containsPosition( unsigned int x, unsigned int y ){
      unsigned int currentX = start.first;
      unsigned int currentY = start.second;
      list<Direction>::iterator it = movements.begin();

      while( currentX != end.first || currentY != end.second ){
        if( currentX == x && currentY == y ){
          return(true);
        }

        if( *it == North )
          currentX--;
        else if( *it == East )
          currentY++;
        else if( *it == South )
          currentX++;
        else
          currentY--;

        ++it;
      }
      if( currentX == x && currentY == y ){
        return(true);
      }
      else
        return(false);
    }
};  // End of class Path

// Class representing and environment
class Environment{
  private:
    char** matrix;
    unsigned int rows,columns;
    pair<unsigned int,unsigned int> start,goal;

  public:
    // Constructor for an empty environment with dimensions r and c
    Environment( const unsigned int r, const unsigned int c){
      rows = r;
      columns = c;

      matrix = new char*[rows];
      for (unsigned  int i = 0; i < rows; ++i)
        matrix[i] = new char[columns];
    }

    // Constructor for an environment from a file
    Environment( const char* nameFile ){
      this->ReadFile(nameFile);
    }

    // Copy constructor
    Environment(const Environment& env ){
      this->rows = env.getRows();
      this->columns = env.getColumns();
      this->start = env.getStart();
      this->goal = env.getGoal();
      char **envMatrix = env.getMatrix();

      matrix = new char*[rows];
      for (unsigned  int i = 0; i < rows; ++i)
        matrix[i] = new char[columns];

      for( unsigned int i=0; i<rows; ++i )
        for( unsigned int j=0; j<columns; ++j )
          matrix[i][j] = envMatrix[i][j];
    }

    // Destructor
    ~Environment(){
      for (unsigned int i = 0; i < rows; ++i)
        delete [] matrix[i];
      delete [] matrix;
    }

    // Getter for Rows
    inline unsigned int getRows() const{
      return rows;
    }

    // Getter for Columns
    inline unsigned int getColumns() const{
      return columns;
    }

    // Getter for matrix
    inline char** getMatrix() const{
      return matrix;
    }

    // Getter for start
    inline pair<unsigned int,unsigned int> getStart() const{
      return start;
    }
    //Getter for goal
    inline pair<unsigned int,unsigned int> getGoal() const{
      return goal;
    }


    // Load an environment from a file
    bool ReadFile( const char* nameFile ){
      FILE* file = fopen(nameFile,"r");
      rows = columns = 0;
      bool countColumns = true;
      char c = fgetc(file);

      while( c != EOF ){
        if( c == '\n' ){
          rows++;
          countColumns = false;
        }
        if( countColumns ){
          columns++;
        }
        c = fgetc(file);
      }

      rewind(file);
      matrix = new char*[rows];
      matrix[0] = new char[columns];
      int currentRow = 0;
      int currentColumn = 0;
      c = fgetc(file);

      while( c != EOF ){
        if( c == '\n' ){
          currentRow++;
          matrix[currentRow] = new char[columns];
          currentColumn = 0;
        }
        else{
          if( c == 's' )
            start = pair<unsigned int,unsigned int>(currentRow,currentColumn);
          else if( c == 'g' )
            goal = pair<unsigned int,unsigned int>(currentRow,currentColumn);

          matrix[currentRow][currentColumn] = c;
          currentColumn++;
        }
        c = fgetc(file);
      }
      return true;
    }

      // Check if a position is suitable for going thru it
    bool isValidPosition( const pair<int,int> position ) const{
      return(isValidPosition(position.first,position.second));
    }

    // Check if a position is suitable for going thru it
    bool isValidPosition( const unsigned int x, const unsigned int y ) const{
      if( x < rows && y < columns ){
        if( matrix[x][y] != 'x' ){
          return(true);
        }
      }
      return(false);
    }

    // Prints the environment in ASCII code
    void Print() const{
      for(unsigned int i=0; i<rows; i++){
        for(unsigned int j=0; j<columns; j++){
          cout << matrix[i][j];
        }
        cout << endl;
      }
    }

    // Prints the environment and a path in ASCII code
    void Print ( const Path path ) const{
      Environment aux(*this);

      list<Direction> pathMovements = path.getMovements();
      unsigned int x = path.getStart().first;
      unsigned int y = path.getStart().second;
      list<Direction>::iterator it = pathMovements.begin();
      Direction last = *it;

      if( *it == North )
        x--;
      else if( *it == East )
        y++;
      else if( *it == South )
        x++;
      else
        y--;

      ++it;   // We don't want to overwritte the start position

      for( ; it != pathMovements.end(); ++it){
        if( *it == North ){
          if( last == East )
            aux.modifyPosition(x,y,'*');
          else if( last == West )
            aux.modifyPosition(x,y,'*');
          else if( last == North )
            aux.modifyPosition(x,y,'*');

          last = North;
          x--;
        }
        else if( *it == East ){
          if( last == North )
            aux.modifyPosition(x,y,'*');
          else if( last == South )
            aux.modifyPosition(x,y,'*');
          else if( last == East )
            aux.modifyPosition(x,y,'*');

          last = East ;
          y++;
        }
        else if( *it == South ){
          if( last == East )
            aux.modifyPosition(x,y,'*');
          else if( last == West )
            aux.modifyPosition(x,y,'*');
          else if( last == South )
            aux.modifyPosition(x,y,'*');

          last = South;
          x++;
        }
        else{
          if( last == North )
            aux.modifyPosition(x,y,'*');
          else if( last == South )
            aux.modifyPosition(x,y,'*');
          else if( last == West )
            aux.modifyPosition(x,y,'*');

          last = West;
          y--;
        }
      }

      aux.Print();
    }

    // Modifies a position in the environment
    void modifyPosition( const unsigned int x, const unsigned int y, const char c ){
      if( x < rows && y < columns ){
        if( matrix[x][y] != 'x' ){
          matrix[x][y] = c;
        }
      }
    }
};
