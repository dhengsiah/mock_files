main: main.o multitap.o
	g++ -Wall -g main.o multitap.o -o main

main.o: main.cpp multitap.h
	g++ -Wall -g -c main.cpp

multitap.o: multitap.cpp multitap.h
	g++ -Wall -g -c multitap.cpp
