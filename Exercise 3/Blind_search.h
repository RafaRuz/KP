#include <utility>          // std::pair
#include <list>             // std::list
#include <queue>            // std::queue

using namespace std;

class Environment{
  private:
    char** matrix;
    unsigned int rows,columns;
    pair<unsigned int,unsigned int> start,goal;

  public:
    Environment( const unsigned int r, const unsigned int c){
      rows = r;
      columns = c;

      matrix = new char*[rows];
      for (int i = 0; i < rows; ++i)
        matrix[i] = new char[cols];
    }

    Environment( const char* nameFile ){
      this.ReadEnvironment
    }

    ~Environment(){
      for (int i = 0; i < rows; ++i)
        delete [] matrix[i];
      delete [] matrix;
    }

    inline pair<unsigned int,unsigned int> getStartPosition(){
      return start;
    }

    inline pair<unsigned int,unsigned int> getGoalPosition(){
      return goal;
    }


}
