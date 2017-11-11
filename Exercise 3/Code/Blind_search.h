#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue

using namespace std;


// Enumeration representing the orientation, needed to define a path
enum Orientation { North, East, South, West };

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
      for (int i = 0; i < rows; ++i)
        matrix[i] = new char[cols];
    }

    // Constructor for an environment from a file
    Environment( const char* nameFile ){
      this.ReadFile(nameFile);
    }

    // Destructor
    ~Environment(){
      for (int i = 0; i < rows; ++i)
        delete [] matrix[i];
      delete [] matrix;
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
      environment = new char*[rows];
      environment[0] = new char[columns];
      int currentRow = 0;
      int currentColumn = 0;
      c = fgetc(file);

      while( c != EOF ){
        if( c == '\n' ){
          currentRow++;
          environment[currentRow] = new char[columns];
          currentColumn = 0;
        }
        else{
          environment[currentRow][currentColumn] = c;
          currentColumn++;
        }
        c = fgetc(file);
      }
    }

    // Start position getter
    inline pair<unsigned int,unsigned int> getStartPosition(){
      return start;
    }

    // Goal position getter
    inline pair<unsigned int,unsigned int> getGoalPosition(){
      return goal;
    }

    // Prints the environment in ASCII code
    void Print( char** environment, const int rows, const int cols ){
      for(int i=0; i<=rows; i++){
        for(int j=0; j<=cols; j++){
          cout << environment[i][j];
        }
        cout << endl;
      }
    }


}
