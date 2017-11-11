
#include <iostream>

using namespace std;

//Read the environment called "nameFile" and saves the dimensions of it in "rows" and "columns"
void ReadEnvironment( char ** &environment, const char* nameFile, int &rows, int &columns ){

    FILE* file = fopen(nameFile,"r");

    rows=0;
    columns=0;
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

// Prints the environment in ASCII code
void PrintEnvironment( char** environment, const int rows, const int cols ){

  for(int i=0; i<=rows; i++){
    for(int j=0; j<=cols; j++){
      cout << environment[i][j];
    }
    cout << endl;
  }
}

//
void BreadthFirst( char** environment ){

}

//
void DepthFirst( char** environment){

}



int main(int argc, char const *argv[]) {
  char **Environment;
  int rows,columns;

  ReadEnvironment(Environment,"blatt3_environment_b.txt",rows,columns);
  PrintEnvironment(Environment,rows,columns);
  return(0);

}
