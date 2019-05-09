CC=g++
CXXFLAGS=-g -std=c++14
IDIR=include
ODIR=src

_OBJ=Estado.o NFA.o main.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

all: NFA

$(ODIR)/Estado.o: $(ODIR)/Estado.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/NFA.O: $(ODIR)/NFA.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)
 
$(ODIR)/main.o: $(ODIR)/main.cpp $(IDIR)/NFA.h $(IDIR)/Estado.h
	$(CC) -c -o $@ $< $(CXXFLAGS)

NFA: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS) -lm

.PHONY:clean
clean:
	rm -rf *.o DFA
