#include "Relation.h"

#include "trees.h"

extern Rel likes;
extern Rel owes;
extern Rel student;
extern Rel lecturer;
extern Rel subject;
extern Rel unicorn;
extern Rel male;
extern Rel female;
extern Rel big;
extern Rel green;

bool compute_s_value(Tree *t);
Thing compute_np_value(Tree *t);
Rel compute_vp_value(Tree *t);
Rel compute_n_value(Tree *t);
Rel compute_tv_value(Tree *t);

bool match(Tree *t, Rule r);
