#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <utility>          // std::pair
#include <vector>           // std::vector
#include <stdlib.h>         // abs()
#include <cmath>            // abs()

using namespace std;


  // Class representing a path between 2 positions
  class Path{
    private:
      vector<pair<unsigned int,unsigned int> > positions;
      unsigned int length;
      unsigned int cost;

    public:
      // Constructor for an empty Path
      Path();

      // Constructor for an empty path with a start defined
      Path( const pair<unsigned int,unsigned int> s );

      // Heuristic function for the distance to a position (used fot A* search)
      double heuristic( const int &x, const int &y, const vector<pair<unsigned int,unsigned int> > &portals ) const;

      // Heuristic function for the distance to a position (used fot A* search)
      double heuristic( const pair<unsigned int,unsigned int> &goal, const vector<pair<unsigned int,unsigned int> > &portals ) const;

      // Estimated cost for the extension of the actual Path to a position
      double estimation( const unsigned int &x, const unsigned int &y, const vector<pair<unsigned int,unsigned int> > &portals ) const;

      // Estimated cost for the extension of the actual Path to a position
       double estimation( const pair<unsigned int,unsigned int> &goal, const vector<pair<unsigned int,unsigned int> > &portals ) const;

      // Start getter
      pair<unsigned int,unsigned int> getStart() const;

      // End getter
      pair<unsigned int,unsigned int> getEnd() const;

      // Length getter
      unsigned int getLength() const;

      // Cost getter
      unsigned int getCost() const;

      // Positions getter
      vector<pair<unsigned int,unsigned int> > getPositions() const;

      // Adds a position at the end of the path
      void addPosition( const unsigned int x, const unsigned int y );

      // Adds a position at the end of the path
      void addPosition( const pair<unsigned int,unsigned int> &pos );

      // Check if a position is already in the path or not
      bool containsPosition( const pair<unsigned int, unsigned int> position ) const;

      // Check if a position is already in the path or not
      bool containsPosition( const unsigned int x, const unsigned int y ) const;

  };  // End of class Path

#endif
