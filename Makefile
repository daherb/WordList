all: unify intersect complement

unify: unify.cpp
	g++ -o unify unify.cpp

intersect: intersect.cpp
	g++ -o intersect intersect.cpp

complement: complement.cpp
	g++ -o complement complement.cpp

approx: approx.cpp
	g++ -std=c++0x -o approx approx.cpp
