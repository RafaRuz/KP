#include "PathComparison.h"

using namespace std;

  PathComparison::PathComparison( const pair<unsigned int,unsigned int> &g, const Environment* env,
                  const bool& revparam=false):reverse(revparam),goal(g),environment(env){}

  PathComparison::PathComparison(const unsigned int &x, const unsigned int &y, const Environment* env,
                  const bool& revparam=false):reverse(revparam),environment(env){
    goal = std::make_pair(x,y);
  }

  bool PathComparison::operator() (const Path &p, const Path &q) const{
    if (reverse) return (p.estimation(goal,environment->getPortals())>q.estimation(goal,environment->getPortals()));
    else return (p.estimation(goal,environment->getPortals())<q.estimation(goal,environment->getPortals()));
  }
