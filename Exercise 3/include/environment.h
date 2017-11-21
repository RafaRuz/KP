#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <utility>          // std::pair
#include <vector>           // std::vector
#include <cstdio>
#include "path.h"
using namespace std;


// Class representing and environment
class Environment{
  private:
    char** matrix;
    unsigned int rows,columns;
    pair<unsigned int,unsigned int> start,goal;
    vector<pair<unsigned int,unsigned int> > portals;

  public:
    // Constructor for an empty environment with dimensions r and c
    Environment( const unsigned int r, const unsigned int c);

    // Constructor for an environment from a file
    Environment( const char* nameFile );

    // Copy constructor
    Environment( const Environment& env );

    // Destructor
    ~Environment();

    // Getter for getPortals
    vector<pair<unsigned int,unsigned int> > getPortals() const;

    // Getter for Rows
    unsigned int getRows() const;

    // Getter for Columns
    unsigned int getColumns() const;

    //Getter for an element
    char getElement(const unsigned int x, const unsigned int y) const;

    //Getter for a element of a Portal
    pair<unsigned int,unsigned int> getPortal(unsigned int pos) const;

    // Getter for matrix
    char** getMatrix() const;

    // Getter for start
    pair<unsigned int,unsigned int> getStart() const;

    //Getter for goal
    pair<unsigned int,unsigned int> getGoal() const;

    // Load an environment from a file
    bool ReadFile( const char* nameFile );

      // Check if a position is suitable for going thru it
    bool isValidPosition( const pair<int,int> position ) const;

    // Check if a position is suitable for going thru it
    bool isValidPosition( const unsigned int x, const unsigned int y )const;

    // Prints the environment in ASCII code
    void Print() const;

    // Prints the environment and a path in ASCII code
    void Print ( const Path &path ) const;

    // Modifies a position in the environment
    void modifyPosition( const unsigned int x, const unsigned int y, const char c );
};

#endif
