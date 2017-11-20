#include <utility>          // std::pair
#include "environment.h"
#include "path.h"


// Class to compare 2 Paths
class PathComparison{
  private:
    pair<unsigned int,unsigned int> goal;
    const Environment* environment;
    bool reverse;
  public:
    PathComparison( const pair<unsigned int,unsigned int> &g, const Environment* env,
                    const bool& revparam=false):reverse(revparam),goal(g),environment(env);

    PathComparison(const unsigned int &x, const unsigned int &y, const Environment* env,
                    const bool& revparam=false):reverse(revparam),environment(env);

    bool operator() (const Path &p, const Path &q) const;
};
