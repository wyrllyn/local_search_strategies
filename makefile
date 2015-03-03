program: main.o ls.o methods.o parser.o
	g++ main.o ls.o methods.o parser.o -O3 -o program -std=c++11

main.o: main.cpp ls.h parser.h
	g++ -c main.cpp -O3 -o main.o -std=c++11

ls.o: ls.cpp methods.h
	g++ -c ls.cpp -O3 -o ls.o -std=c++11

methods.o: methods.cpp 
	g++ -c methods.cpp -O3 -o methods.o -std=c++11

parser.o: parser.cpp
	g++ -c parser.cpp -O3 -o parser.o -std=c++11

clean:
	rm -rf *.o *~ program