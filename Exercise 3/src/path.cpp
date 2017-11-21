#include "path.h"

using namespace std;

  // Constructor for an empty Path
  Path::Path():length(0),cost(0){}

  // Constructor for an empty path with a start defined
  Path::Path( const pair<unsigned int,unsigned int> s ):length(1),cost(1){
    positions.push_back(s);
  }

      // Heuristic function for the distance to a position (used fot A* search)
    double Path::heuristic( const int &x, const int &y, const vector<pair<unsigned int,unsigned int> > &portals ) const{
      vector<pair<unsigned int,unsigned int> >::const_iterator it = portals.begin();
      unsigned int min = abs(x-(int)positions.back().first) + abs(y-(int)positions.back().second);

      for (size_t i = 0; i < portals.size(); i++) {
        if( i%2 ){
          if( ( abs((int)positions.back().first - (int)portals[i].first) + abs((int)positions.back().second - (int)portals[i].second) + abs((int)portals[i-1].first - x) + abs((int)portals[i-1].second - y) ) < min ){
            min = ( abs((int)positions.back().first - (int)portals[i].first) + abs((int)positions.back().second - (int)portals[i].second) + ((int)portals[i-1].first - x) + abs((int)portals[i-1].second - y) );
          }
        }
        else{
          if( (abs((int)positions.back().first - (int)portals[i].first) + abs((int)positions.back().second - (int)portals[i].second) + abs((int)portals[i+1].first - x) + abs((int)portals[i+1].second - y)) < min ){
            min = abs((int)positions.back().first - (int)portals[i].first) + abs((int)positions.back().second - (int)portals[i].second) + abs((int)portals[i+1].first - x) + abs((int)portals[i+1].second - y);
          }
        }
      }

      return(min);
    }

    // Heuristic function for the distance to a position (used fot A* search)
     double Path::heuristic( const pair<unsigned int,unsigned int> &goal, const vector<pair<unsigned int,unsigned int> > &portals ) const{
      return(heuristic(goal.first,goal.second,portals));
    }

    // Estimated cost for the extension of the actual Path to a position
     double Path::estimation( const unsigned int &x, const unsigned int &y, const vector<pair<unsigned int,unsigned int> > &portals ) const{
      return(cost+heuristic(x,y,portals));
    }

    // Estimated cost for the extension of the actual Path to a position
      double Path::estimation( const pair<unsigned int,unsigned int> &goal, const vector<pair<unsigned int,unsigned int> > &portals ) const{
      return(cost+heuristic(goal,portals));
    }

    // Start getter
    pair<unsigned int,unsigned int> Path::getStart() const{
      return(positions.front());
    }

    // End getter
     pair<unsigned int,unsigned int> Path::getEnd() const{
      return(positions.back());
    }

    // Length getter
     unsigned int Path::getLength() const{
      return(length);
    }

    // Cost getter
     unsigned int Path::getCost() const{
      return(cost);
    }

    // Positions getter
     vector<pair<unsigned int,unsigned int> > Path::getPositions() const{
      return(positions);
    }

    // Adds a position at the end of the path
     void Path::addPosition( const unsigned int x, const unsigned int y ){
      addPosition(pair<unsigned int,unsigned int>(x,y));
    }

    // Adds a position at the end of the path
    void Path::addPosition( const pair<unsigned int,unsigned int> &pos ){
        positions.push_back(pos);
        length++;
        cost++;
    }

    // Check if a position is already in the path or not
    bool Path::containsPosition( const pair<unsigned int, unsigned int> position ) const{
      for(vector<pair<unsigned int, unsigned int> >::const_iterator it=positions.begin(); it != positions.end(); ++it)
        if( *it == position )
          return(true);

      return(false);
    }

    bool Path::containsPosition( const unsigned int x, const unsigned int y ) const{
      return(containsPosition(pair<unsigned int,unsigned int>(x,y)));

    }
