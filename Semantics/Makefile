#CPPFLAGS = -g -std=c++11
#CPPFLAGS = -g -std=c++14
PARSERDIR = /shared/teaching/CSLL/2CSLL3/CFG_Parsers
INCPATH = -I$(PARSERDIR) -I.
PARSEROBJ = $(PARSERDIR)/BUPARSE.o $(PARSERDIR)/BUPARSE_BT_TREE.o $(PARSERDIR)/PDA.o $(PARSERDIR)/rules.o $(PARSERDIR)/trees.o

Relation.o: Relation.cpp Relation.h
	g++ $(CPPFLAGS) $(INCPATH) -c Relation.cpp

tester.o: tester.cpp Relation.h eval.h $(PARSERDIR)/trees.h $(PARSERDIR)/rules.h
	g++ $(CPPFLAGS) $(INCPATH) -c tester.cpp

gram_tester.o: gram_tester.cpp Relation.h eval.h $(PARSERDIR)/trees.h $(PARSERDIR)/rules.h
	g++ $(CPPFLAGS) $(INCPATH) -c gram_tester.cpp

util.o: util.cpp util.h
	g++ $(CPPFLAGS) $(INCPATH) -c util.cpp

eval.o: eval.cpp eval.h Relation.h $(PARSERDIR)/trees.h $(PARSERDIR)/rules.h
	g++ $(CPPFLAGS) $(INCPATH) -c eval.cpp

tester: Relation.o util.o eval.o tester.o $(PARSERDIR)/rules.o $(PARSERDIR)/trees.o
	g++ $(CPPFLAGS) $(INCPATH) Relation.o util.o eval.o tester.o $(PARSERDIR)/rules.o $(PARSERDIR)/trees.o -o tester

gram_tester: Relation.o util.o eval.o gram_tester.o $(PARSEROBJ)
	g++ $(CPPFLAGS) $(INCPATH) Relation.o util.o eval.o gram_tester.o $(PARSEROBJ) -o gram_tester

clean:
	rm Relation.o util.o eval.o tester.o gram_tester.o
