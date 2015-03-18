program: main.o methods.o parser.o
	g++ main.o methods.o parser.o -O3 -o program 

main.o: main.cpp parser.h
	g++ -c main.cpp -O3 -o main.o 

methods.o: methods.cpp 
	g++ -c methods.cpp -O3 -o methods.o 

parser.o: parser.cpp
	g++ -c parser.cpp -O3 -o parser.o 

clean:
	rm -rf *.o *~ program