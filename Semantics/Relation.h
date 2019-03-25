#include <vector>
#include <string>
using namespace std;

#if !(defined REL_H) 
#define REL_H

//typedef vector<int> Tuple;
typedef vector<string> Tuple; 
typedef string Thing;

class Rel {
 public:
  Rel();
  Rel(int n);
  Rel(int n, string filename);
  int arity;
  bool has(Tuple t);
  bool add_tuple(Tuple t);

  vector<Tuple> tuples;
  void show();
  bool opened_ok;

};

// fix some position to reduce arity
Rel reduce(Rel RelIn, int which, Thing val);
Tuple erase(Tuple t, int which); // helper function for above

// check whether tuple <o> is in the 'relation' Pred ie. in the set
bool true_of(Rel Pred, Thing o);

bool gen_quant(string gq, Rel p, Rel q);
bool some(Rel p, Rel q);
bool every(Rel p, Rel q);


Rel meet(Rel p, Rel q);




#endif
  
