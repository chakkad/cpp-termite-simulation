CXX=g++
CXXFLAGS= -Wall -std=c++11
EXEC_FILES= projet-main tests

all: projet-main
# General Rule
%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

projet-main: projet.o coord.o grille.o termite.o
	$(CXX) -o $@ $^ $(LDFLAGS)
tests: test.o coord.o grille.o
	$(CXX) -o $@ $^ $(LDFLAGS)

# Object Files
coord.o: coord.hpp
grille.o: grille.hpp
termite.o: termite.hpp
projet.o: coord.hpp grille.hpp termite.hpp
test.o: coord.hpp

check: tests
	./tests -s

clean:
	rm -f *.o $(EXEC_FILES)