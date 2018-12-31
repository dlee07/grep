CXX = clang++
CXXFLAGS = -g3 -Wall -Wextra -std=c++11
LDFLAGS = -g3

all: gerp, testhash. testquery 

gerp: main.o Query.o Hash.o 
	${CXX} ${LDFLAGS} -o gerp main.o Query.o Hash.o \
							FSTree.o DirNode.o 

testhash: testhash.o Hash.o
	${CXX} ${LDFLAGS} -o testhash testhash.o Hash.o 

testquery: testquery.o Query.o Hash.o 
	${CXX} ${LDFLAGS} -o testquery testquery.o Query.o Hash.o \
									FSTree.o DirNode.o 

main.o: main.cpp Query.cpp Hash.cpp 

testquery.o: testquery.cpp Query.cpp Hash.cpp

Query.o: Query.cpp Query.h FSTree.h DirNode.h

testhash.o: testhash.cpp Hash.cpp

Hash.o: Hash.cpp Hash.h 

clean: 
	rm -rf gerp *.o *.dSYM
provide:
	provide comp15 proj2part3 main.cpp Query.cpp Query.h \
								Hash.cpp Hash.h testhash.cpp \
								testquery.cpp README Makefile