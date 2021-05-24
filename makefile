all : Source

Source : Source.cpp
	g++ -g -Wall -lncurses -o Source Source.cpp

Source.cpp :
