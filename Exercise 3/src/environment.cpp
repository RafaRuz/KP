#include "environment.h"
#include "path.h"

using namespace std;

// Constructor for an empty environment with dimensions r and c
Environment::Environment( const unsigned int r, const unsigned int c){
  rows = r;
  columns = c;

  matrix = new char*[rows];
  for (unsigned  int i = 0; i < rows; ++i)
    matrix[i] = new char[columns];
}

// Constructor for an environment from a file
Environment::Environment( const char* nameFile ){
  this->ReadFile(nameFile);
}

// Copy constructor
Environment::Environment( const Environment& env ){
  this->rows = env.getRows();
  this->columns = env.getColumns();
  this->start = env.getStart();
  this->goal = env.getGoal();
  this->portals = env.getPortals();

  matrix = new char*[rows];
  for (unsigned  int i = 0; i < rows; ++i)
    matrix[i] = new char[columns];

  for( unsigned int i=0; i<rows; ++i )
    for( unsigned int j=0; j<columns; ++j )
      matrix[i][j] = env.getElement(i,j);
}

// Destructor
Environment::~Environment(){
  for (unsigned int i = 0; i < rows; ++i)
    delete [] matrix[i];
  delete [] matrix;
  //delete [] portals;
}

// Getter for getPortals
vector<pair<unsigned int,unsigned int> > Environment::getPortals() const{
  return portals;
}

// Getter for Rows
unsigned int Environment::getRows() const{
  return rows;
}

// Getter for Columns
unsigned int Environment::getColumns() const{
  return columns;
}

//Getter for an element
char Environment::getElement(const unsigned int x, const unsigned int y) const{
  if( x < rows && y < columns ){
    return matrix[x][y];
  }
  return('x');
}

//Getter for a element of a Portal
pair<unsigned int,unsigned int> Environment::getPortal(unsigned int pos) const{
  return portals[pos];
}

// Getter for matrix
char** Environment::getMatrix() const{
  return matrix;
}

// Getter for start
pair<unsigned int,unsigned int> Environment::getStart() const{
  return start;
}

//Getter for goal
pair<unsigned int,unsigned int> Environment::getGoal() const{
  return goal;
}

// Load an environment from a file
bool Environment::ReadFile( const char* nameFile ){
  FILE* file = fopen(nameFile,"r");
  rows = columns = 0;

  portals = vector<pair<unsigned int,unsigned int> >  (18, std::make_pair(0, 0));


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
      else if( c >'0' && c <= '9' ){
        if( portals[2*(c-'0')-2] == pair<unsigned int,unsigned int>(0,0) )
          portals[2*(c-'0')-2] = pair<unsigned int,unsigned int>(currentRow,currentColumn);
        else
          portals[2*(c-'0')-1] = pair<unsigned int,unsigned int>(currentRow,currentColumn);
      }
      matrix[currentRow][currentColumn] = c;
      currentColumn++;
    }
    c = fgetc(file);
  }
  return true;
}

// Check if a position is suitable for going thru it
bool Environment::isValidPosition( const unsigned int x, const unsigned int y ) const{
  if( x < rows && y < columns ){
    if( matrix[x][y] != 'x' ){
      return(true);
    }
  }
  return(false);
}

// Check if a position is suitable for going thru it
bool Environment::isValidPosition( const pair<int,int> position ) const{
  return(isValidPosition(position.first,position.second));
}


// Prints the environment in ASCII code
void Environment::Print() const{
  for(unsigned int i=0; i<rows; i++){
    for(unsigned int j=0; j<columns; j++){
      cout << matrix[i][j];
    }
    cout << endl;
  }
}

// Prints the environment and a path in ASCII code
void Environment::Print ( const Path &path ) const{
  Environment aux(*this);

  vector<pair<unsigned int,unsigned int> > positionsPath = path.getPositions();
  vector<pair<unsigned int,unsigned int> >::const_iterator it=positionsPath.begin();
  // ++it;
  // vector<pair<unsigned int,unsigned int> >::const_iterator it_end=positionsPath.end();
  // --it_end;

  for( ; it != positionsPath.end(); ++it)
    if( (matrix[it->first][it->second] < '0' || matrix[it->first][it->second] > '9') &&
         matrix[it->first][it->second] != 's' && matrix[it->first][it->second] != 'g' )
      aux.modifyPosition(it->first, it->second, '*');

  aux.Print();
}

// Modifies a position in the environment
void Environment::modifyPosition( const unsigned int x, const unsigned int y, const char c ){
  if( x < rows && y < columns ){
      matrix[x][y] = c;
  }
}
