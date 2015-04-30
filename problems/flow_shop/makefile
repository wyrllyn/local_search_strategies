program: main.o methods.o parser.o ls.o
	g++ main.o ls.o methods.o parser.o -O3 -o program 

main.o: main.cpp parser.h
	g++ -c main.cpp -O3 -o main.o 

ls.o: ls.cpp methods.h
	g++ -c ls.cpp -O3 -o ls.o

methods.o: methods.cpp 
	g++ -c methods.cpp -O3 -o methods.o 

parser.o: parser.cpp
	g++ -c parser.cpp -O3 -o parser.o 

clean:
	rm -rf *.o *~ program