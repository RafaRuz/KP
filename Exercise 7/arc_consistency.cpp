#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;

template <class T> bool lt( const T &t1, const T &t2 ){ return(t1<t2); }
template <class T> bool let( const T &t1, const T &t2 ){ return(t1<=t2); }
template <class T> bool gt( const T &t1, const T &t2 ){ return(t1>t2); }
template <class T> bool get( const T &t1, const T &t2 ){ return(t1>=t2); }
template <class T> bool eq( const T &t1, const T &t2 ){ return(t1==t2); }
template <class T> bool neq( const T &t1, const T &t2 ){ return(t1!=t2); }


template <class T>
struct Constraint{
    char X,Y;
    bool (*comp)(const T &v1, const T &v2);

    Constraint( const char &x, const char &y, bool (*c)(const T &v1, const T &v2) ):X(x),Y(y),comp(c){}

    bool check( const T &v1, const T &v2){
      return comp(v1,v2);
    }
};

template <class T>
void GraphArcConsistency( map<char,T> &variables, map<char,Constraint> &constraints ){

}

int main(int argc, char const *argv[]) {
  if( argc != 2 ){
    cout << "Error." << endl;
    return 1;
  }

  return 0;
}
