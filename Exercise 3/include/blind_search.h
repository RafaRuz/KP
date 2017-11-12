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
    Path( const pair<unsigned int,unsigned int> s ):length(0), start(s){}

    // Start getter
    inline pair<unsigned int,unsigned int> getStartPosition() const{
      return(start);
    }

    // End getter
    inline pair<unsigned int,unsigned int> getEndPosition() const{
      return(end);
    }

    // Movements getter
    inline list<Direction> getMovements() const{
      return(movements);
    }

    // Add a movement to the path
    void addMovement( const Direction dir ){
      movements.push_back(dir);

      if( dir == North )
        end = pair<unsigned int,unsigned int>(end.first,end.second+1);
      else if( dir == East )
        end = pair<unsigned int,unsigned int>(end.first+1,end.second);
      else if( dir == South )
        end = pair<unsigned int,unsigned int>(end.first,end.second-1);
      else
        end = pair<unsigned int,unsigned int>(end.first-1,end.second);
    }
};

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
      this->matrix = env.getMatrix();
      this->start = env.getStart();
      this->goal = env.getGoal();

    }

    // Destructor
    ~Environment(){
      for (unsigned int i = 0; i < rows; ++i)
        delete [] matrix[i];
      delete [] matrix;
    }
    //Getter from Rows
    inline unsigned int getRows() const{
      return rows;
    }
    //Getter from Columns
    inline unsigned int getColumns() const{
      return columns;
    }

    //Getter for matrix
    inline char** getMatrix() const{
      return matrix;
    }
    //Getter for start
    inline pair<unsigned int,unsigned int> getStart() const{
      return start;
    }
/*
    //Getter for start non constant
    inline pair<unsigned int,unsigned int> getStartNC(){
      return start;
    }*/
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
          matrix[currentRow][currentColumn] = c;
          currentColumn++;
        }
        c = fgetc(file);
      }
      return true;
    }

      // Check if a position is suitable for going thru it
    bool isValidPosition( const pair<int,int> position ){
      if( matrix[position.first][position.second] == 'x' )
        return(false);
      return(true);
    }

    // Check if a position is suitable for going thru it
    bool isValidPosition( const unsigned int x, const unsigned int y ){
      if( matrix[x][y] == 'x' )
        return(false);
      return(true);
    }

    // Prints the environment in ASCII code
    void Print(){
      for(unsigned int i=0; i<=rows; i++){
        for(unsigned int j=0; j<=columns; j++){
          cout << matrix[i][j];
        }
        cout << endl;
      }
    }

    // Prints the environment and a path in ASCII code
    void Print( const Path path ){
      Environment aux(*this);

      list<Direction> pathMovements = path.getMovements();
      unsigned int x = path.getStartPosition().first;
      unsigned int y = path.getStartPosition().second;
      list<Direction>::iterator it = pathMovements.begin();
      Direction last = *it;
      ++it;   // We don't want to overwritte the start position

      for( ; it != pathMovements.end(); ++it){
        if( *it == North ){
          if( last == East )
            aux.modifyPosition(x,y,217);
          else if( last == West )
            aux.modifyPosition(x,y,192);

          last = North;
        }
        else if( *it == East ){
          if( last == North )
            aux.modifyPosition(x,y,192);
          else if( last == South )
            aux.modifyPosition(x,y,218);

          last = East ;
        }
        else if( *it == South ){
          if( last == East )
            aux.modifyPosition(x,y,218);
          else if( last == West )
            aux.modifyPosition(x,y,191);

          last = South;
        }
        else{
          if( last == North )
            aux.modifyPosition(x,y,217);
          else if( last == South )
            aux.modifyPosition(x,y,191);

          last = West;
        }
      }

      aux.Print();
    }

    // Modifies a position in the environment
    void modifyPosition( const unsigned int x, const unsigned int y, const char c ){
      matrix[x][y] = c;
    }
};
