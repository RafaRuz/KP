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

/*

*/

template <class T>
void GraphArcConsistency( map<char,T> &variables, map<char,Constraint> &constraints ){

}

int main(int argc, char const *argv[]) {
  if( argc != 2 ){
    cout << "Error." << endl;
    return 1;
  }

  vector<string> list;
  list.push_back("add");  list.push_back("ado");  list.push_back("age");  list.push_back("ago");
  list.push_back("aid");  list.push_back("air");  list.push_back("ail");  list.push_back("aim");
  list.push_back("and");  list.push_back("any");  list.push_back("ape");  list.push_back("apt");
  list.push_back("arc");  list.push_back("are");  list.push_back("ark");  list.push_back("arm");
  list.push_back("art");  list.push_back("ash");  list.push_back("ask");  list.push_back("auk");
  list.push_back("awe");  list.push_back("awl");  list.push_back("aye");  list.push_back("bad");
  list.push_back("bag");  list.push_back("ban");  list.push_back("bat");  list.push_back("bee");
  list.push_back("boa");  list.push_back("ear");  list.push_back("eel");  list.push_back("eft");
  list.push_back("far");  list.push_back("fat");  list.push_back("fit");  list.push_back("lee");
  list.push_back("oaf");  list.push_back("rat");  list.push_back("tar");  list.push_back("tie");













  return 0;
}
