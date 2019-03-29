#include "Relation.h"
#include "eval.h"
#include "util.h"
#include <fstream>
#include "BUPARSE_BT.h"
#include "BUPARSE_BT_TREE.h"

#include <iostream>
using namespace std;

/*

can enter a sentence, checks grammatical status, responding with yep/no and a tree
and then evaluates the truth of the sentence, responding with 0/1
the 'situation' being referred to is defined by the files  
likes_rel    : 2-place
student_rel  : 1-place
lecturer_rel : 1-place
subject_rel  : 1-place

intended grammar: university_gram

inputs to try with expected outcomes:

Martin likes maths: true
Martin likes history: false
Hermione likes history: true
Hermione is a student: true
geometry is a student: false
geometry is a subject: true
a lecturer likes maths: true
a lecturer likes history: false
every lecturer likes geometry: true
every lecturer likes maths: false
every student who likes maths likes geometry: true
every student who likes geometry likes maths: false
Plato is a lecturer who likes geometry: true

*/

main(int argc, char *argv[]) {
  string gname,s;
  if(argc != 2) {
    cout << "usage: gram_tester GRAMMAR\n";
    cout << "where GRAMMAR is the filename of a grammar\n";
  }

  // this set up some global 'Rel' or relation objects
  // which evaluation functions will refer to
  likes = Rel(2,"likes_rel");
  owes = Rel(3,"owes_rel");
  //likes.show();

  student = Rel(1,"student_rel");
  //student.show();

  lecturer = Rel(1,"lecturer_rel");
  //lecturer.show();
  
  subject = Rel(1,"subject_rel");
  //subject.show();

   male = Rel(1,"male_rel");

  female = Rel(1,"female_rel");

  big = Rel(1,"big_rel");

  green = Rel(1,"green_rel");

  unicorn = Rel(1);

  gname = string(argv[1]);


  BUPARSE_BT_TREE parser(gname);

  parser.g.print();
  //parser.stack_debug=1;
  //parser.backtrack_debug=1;

  vector<string> words;

  while(cout << "enter the string to be checked "
 	&& getline(cin,s)) {
    words = tokenize(s); 
    cout << "input is " << s << endl;

    //parser.use_dot = 1;
    if(parser.parse_all(words,0)) {   
      cout << "yep\n";
      int v; 
      v = compute_s_value(parser.tree_ptr);
      cout << "value is: " << v << endl;
    }
    else {
      cout << "nope\n";
    }
  }

}

