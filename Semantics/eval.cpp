#include "eval.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>



Rel likes;
Rel owes;
Rel student;
Rel lecturer;
Rel subject;
Rel unicorn;

// these decs in eval.h
// bool compute_s_value(Tree *t);
// Thing compute_np_value(Tree *t);
// Rel compute_vp_value(Tree *t);
// Rel compute_n_value(Tree *t);
// Rel compute_tv_value(Tree *t);


// bool match(Tree *t, string s);

void sem_error(Tree *t);

bool compute_s_value(Tree *t) {
  bool v;

  // s --> np,vp  where np is a name
  if(match(t,Rule("s --> np,vp"))
     && match(t->dtrs[0],Rule("np --> name"))) {

    Thing v1;
    Rel v2;
    v1 = compute_np_value(t->dtrs[0]);
    v2 = compute_vp_value(t->dtrs[1]);
    v = true_of(v2,v1);
    return v;
  }
  // s --> np,vp where np is det,n
  else if(match(t,Rule("s --> np,vp"))
	  && match(t->dtrs[0],Rule("np --> det,n"))) {
    Rel v1;
    Rel v2;
    string gq;
    Tree *np = t->dtrs[0];
    
    gq = np->dtrs[0]->dtrs[0]->mother.cat; // gets the word in det position

    v1 = compute_n_value(np->dtrs[1]); // get value from n dtr of np
    
    v2 = compute_vp_value(t->dtrs[1]); // get value from vp dtr of s
    
    v = gen_quant(gq,v1,v2);
    
    return v;
  }
  else {
    sem_error(t);
    return false;
  }
}

// np --> name  
Thing compute_np_value(Tree *t) {
  Thing v;

  if(match(t,Rule("np --> name"))) {
    // short cut
    return (t->dtrs[0]->dtrs[0]->mother.cat);
  }
  else {
    sem_error(t);
    return "nothing";
  }

}

// tv --> [w]
Rel compute_tv_value(Tree *t) {
  Rel r(2);
  if(t->dtrs[0]->mother.cat == "likes") {
    return likes;
  }
  else {
    sem_error(t);
    return r;
  }
}

Rel compute_dtv_value(Tree *t) {
  Rel r(3);
  if(t->dtrs[0]->mother.cat == "owes") {
    return owes;
  }
  else {
    sem_error(t);
    return r;
  }
}

Rel compute_vp_value(Tree *t) {
  Rel r_unary(1);

  if(match(t,Rule("vp --> tv,np"))
     && match(t->dtrs[1], Rule("np --> name"))) {
    
    Tree *tv = t->dtrs[0];
    Rel r_binary(2);
    r_binary = compute_tv_value(tv);
    
    Tree *np = t->dtrs[1];
    Thing o;
    o = compute_np_value(np);
    r_unary = reduce(r_binary,1,o);
    return r_unary;
  } // end vp --> tv,np

  else if(match(t,Rule("vp --> [is],[a],n"))) {
    r_unary = compute_n_value(t->dtrs[2]);
    return r_unary;
  }
  //checks if verb is ditransitive
  else if(match(t,Rule("vp --> dtv,np,np")) && match(t->dtrs[1], Rule("np --> name")) && match(t->dtrs[2], Rule("np --> name"))){

    Tree *dtv = t->dtrs[0];
    Rel r_trinary(3);
    r_trinary = compute_dtv_value(dtv);

    Tree *np1 = t->dtrs[1];
    Thing o1;
    o1 = compute_np_value(np1);

    Tree *np2 = t->dtrs[2];
    Thing o2;
    o2 = compute_np_value(np2);

    r_unary = reduce(reduce(r_trinary,2,o2),1,o1);
    return r_unary;
  }
  else {
    sem_error(t);
    return r_unary;
  }
  
}




Rel compute_n_value(Tree *t) {
  //n --> [subject] etc
  Rel r(1);
  if(t->mother.cat == "n" && t->dtrs.size() == 1) {
  
    if(t->dtrs[0]->mother.cat == "subject") {
      return subject;
    }
    else if(t->dtrs[0]->mother.cat == "lecturer") {
      return lecturer;
    }
    else if(t->dtrs[0]->mother.cat == "student") {
      return student;
    }
    else if(t->dtrs[0]->mother.cat == "unicorn") {
      return unicorn;
    }
    else {
      sem_error(t->dtrs[0]);
      return r;
    }
  }
  else if(match(t,Rule("n --> n,[who],vp"))) {
    Rel p(1);
    Rel q(1);
    p = compute_n_value(t->dtrs[0]);
    q = compute_vp_value(t->dtrs[2]);
    r = meet(p,q);
    return r;
  }
  else {
    sem_error(t);
    return r;
  }

}

void sem_error(Tree *t) {
  cout << "unhandled tree type\n";
  t->drawtree();

}



// bool match(Tree *t, string s) {
//   Rule r;
//   r = Rule(s);
  
//   if(!are_equal(t->mother, r.mother)) { return false; }

//   if(t->dtrs.size() != r.dtrs.size()) { return false; }

//   for(int i=0; i < t->dtrs.size(); i++) {
//     if(!are_equal(t->dtrs[i]->mother, r.dtrs[i])) { return false; }
//   }

//   return true;

// }

bool match(Tree *t, Rule r) {

  if(!are_equal(t->mother, r.mother)) { return false; }

  if(t->dtrs.size() != r.dtrs.size()) { return false; }

  for(int i=0; i < t->dtrs.size(); i++) {
    if(!are_equal(t->dtrs[i]->mother, r.dtrs[i])) { return false; }
  }

  return true;

}
