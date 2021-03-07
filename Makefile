.PHONY: all run compile clean
IDIR=HeaderFiles
SRC=SourceFiles/cMain.cpp SourceFiles/Pathfinding.cpp
CC=g++
CFLAGS=$(SRC) -I$(IDIR) `wx-config --libs` `wx-config --cxxflags` -Wall -g

BDIR=BinaryFiles

LIBS=-lm

all: clean compile run

run: 
	./$(BDIR)/Pathfinding

compile: $(OBJ)
	$(CC) $(CFLAGS) -o $(BDIR)/Pathfinding

clean:
	rm -f $(BDIR)/Pathfinding
