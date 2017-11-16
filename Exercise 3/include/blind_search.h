#include <iostream>
#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue
#include <vector>           // std::vector
#include <cstdio>

using namespace std;


// Enumeration representing the possible directions, needed to define a path
enum Direction { North, East, South, West };

// Class representing a path between 2 positions
class Path{
  private:
    vector<pair<unsigned int,unsigned int> > positions;
    unsigned int length;

  public:
    // Constructor for an empty Path
    Path():length(0){}

    // Constructor for an empty path with a start defined
    Path( const pair<unsigned int,unsigned int> s ):length(1){
      positions.push_back(s);
    }

    // Start getter
    inline pair<unsigned int,unsigned int> getStart() const{
      return(positions.front());
    }

    // End getter
    inline pair<unsigned int,unsigned int> getEnd() const{
      return(positions.back());
    }

    // Length getter
    inline unsigned int getLength() const{
      return(length);
    }

    // Positions getter
    inline vector<pair<unsigned int,unsigned int> > getPositions() const{
      return(positions);
    }

    // Adds a position at the end of the path
    bool addPosition( const unsigned int x, const unsigned int y ){
      return(addPosition(pair<unsigned int,unsigned int>(x,y)));
    }

    // Adds a position at the end of the path
    bool addPosition( const pair<unsigned int,unsigned int> &pos ){
      int difX = pos.first-positions.back().first;
      int difY = pos.second-positions.back().second;

      if( (difX == -1 || difX == 0 || difX == 1) && (difY == -1 || difY == 0 || difY == 1) && (difX != difY) ){
        positions.push_back(pos);
        length++;
        return(true);
      }
      else return(false);
    }

    // Check if a position is already in the path or not
    bool containsPosition( const pair<unsigned int, unsigned int> position ) const{
      for(vector<pair<unsigned int, unsigned int> >::const_iterator it=positions.begin(); it != positions.end(); ++it)
        if( *it == position )
          return(true);

      return(false);
    }

    // Check if a position is already in the path or not
    bool containsPosition( const unsigned int x, const unsigned int y ) const{
      return(containsPosition(pair<unsigned int,unsigned int>(x,y)));
    }
};  // End of class Path

// Class representing and environment
class Environment{
  private:
    char** matrix;
    unsigned int rows,columns;
    pair<unsigned int,unsigned int> start,goal;
    vector<pair<unsigned int,unsigned int> > portals;

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
      this->portals = env.getPortals();
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

    // Getter for getPortals
    inline vector<pair<unsigned int,unsigned int> > getPortals() const{
      return portals;
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
        /*  else if( c == '1' ){
            if( portals[0] == pair<unsigned int,unsigned int>(0,0) )
              portals[0] = pair<unsigned int,unsigned int>(currentRow,currentColumn);
            else
              portals[1] = pair<unsigned int,unsigned int>(currentRow,currentColumn);
          }
          else if( c == '2' ){
            if( portals[2] == pair<unsigned int,unsigned int>(0,0) )
              portals[2] = pair<unsigned int,unsigned int>(currentRow,currentColumn);
            else
              portals[3] = pair<unsigned int,unsigned int>(currentRow,currentColumn);
          }*/


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
    void Print ( const Path &path ) const{
      Environment aux(*this);

      vector<pair<unsigned int,unsigned int> > positionsPath = path.getPositions();
      vector<pair<unsigned int,unsigned int> >::const_iterator it=positionsPath.begin();
      ++it;
      vector<pair<unsigned int,unsigned int> >::const_iterator it_end=positionsPath.end();
      --it_end;

      for( ; it != it_end; ++it)
        aux.modifyPosition(it->first, it->second, '*');

      aux.Print();
    }

    // Modifies a position in the environment
    void modifyPosition( const unsigned int x, const unsigned int y, const char c ){
      if( x < rows && y < columns ){
          matrix[x][y] = c;
      }
    }
};
