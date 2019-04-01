# Semantics
NLP project on Semantics

Implementing some concepts from formal semantics using C++ (Generalised quantifiers, relations).
This project is for the college module 'Intermediate programming & Natural Language processing'.
Most code written by Dr. Martin Emms (https://www.scss.tcd.ie/Martin.Emms/), 
added to by myself and Benno Krojer (https://github.com/BennoKrojer).

### Functionality
- Sentence parsing, based on 'university_gram' file which outlines a context free grammar.
- Visual representation of syntactic structure in tree form generated.
- Truth value derived from relations stored as files containing the things for which
those relations hold.

### Additions made to code
- Number quantification, "5 students like maths", as well as the quantifier most: "Most students like maths"
- Ditransitive verbs, "Ron owes Hermione cake"
- Adjectival relations, "Every green student likes maths"


### Possible additions:
- Passive constructions
- Assigning different types of relations, (i.e reflexive, symmetric, transitive) allowing truth values of more sentences to be inferred based on certain relations.
- Quantifying the object e.g. "Harry likes every subject"
- noun-specific adjectives, e.g. "Every lazy student likes msths"
