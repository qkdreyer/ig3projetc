# Compilateur utilisé 
CXX ?= g++
#
# Options du compilateur
CXXFLAGS ?= -Wall -ansi -g
#
# Definition de l'acces aux repertoir des headers (utiles si l'on ne met pas le chemin dans les <#include ... > mais juste le nom du fichier
#
#
all: Lager clean
#
Lager: fbfriends.o AdjList.o AdjMat.o Generator.o Graph.o Summit.o main.o
	$(CXX) $(CXXFLAGS) -o Lager $(CURDIR)/source/os_dependent.c fbfriends.o AdjList.o AdjMat.o Generator.o Graph.o Summit.o main.o
#
fbfriends.o: $(CURDIR)/source/fbfriends.cpp $(CURDIR)/headers/os_dependent.h
	$(CXX) -ansi -g -w -o fbfriends.o -c $(CURDIR)/source/fbfriends.cpp
#
Summit.o: $(CURDIR)/source/Summit.cpp
	$(CXX) $(CXXFLAGS) -o Summit.o -c $(CURDIR)/source/Summit.cpp
#
Generator.o: $(CURDIR)/source/Generator.cpp $(CURDIR)/headers/fbfriends.h
	$(CXX) $(CXXFLAGS) -o Generator.o -c $(CURDIR)/source/Generator.cpp
#
AdjList.o: $(CURDIR)/source/AdjList.cpp $(CURDIR)/headers/Summit.h
	$(CXX) $(CXXFLAGS) -o AdjList.o -c $(CURDIR)/source/AdjList.cpp
#
AdjMat.o: $(CURDIR)/source/AdjMat.cpp $(CURDIR)/headers/Summit.h
	$(CXX) $(CXXFLAGS) -o AdjMat.o -c $(CURDIR)/source/AdjMat.cpp
#
Graph.o: $(CURDIR)/source/Graph.cpp $(CURDIR)/headers/AdjList.h $(CURDIR)/headers/AdjMat.h
	$(CXX) $(CXXFLAGS) -o Graph.o -c $(CURDIR)/source/Graph.cpp
#
main.o: $(CURDIR)/source/main.cpp $(CURDIR)/headers/Generator.h $(CURDIR)/headers/Graph.h
	$(CXX) $(CXXFLAGS) -o main.o -c $(CURDIR)/source/main.cpp
clean:
	@rm -rf *.o

mrproper: clean
	@rm -rf Lager

