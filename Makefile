all : main

main : main.cpp
	g++ -Wall -std=c++11 -o main main.cpp

clean:
	-rm -f *.exe *.o