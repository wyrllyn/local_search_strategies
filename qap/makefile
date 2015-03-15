program: main.o ls.o methods.o parser.o climbn.o climbnun.o climblarge.o
	g++ main.o ls.o climbnun.o climblarge.o climbn.o methods.o parser.o -O3 -o program -std=c++11

main.o: main.cpp ls.h parser.h
	g++ -c main.cpp -O3 -o main.o -std=c++11

ls.o: ls.cpp methods.h
	g++ -c ls.cpp -O3 -o ls.o -std=c++11

climbnun.o: climbnun.cpp methods.h
	g++ -c climbnun.cpp -O3 -o climbnun.o -std=c++11

climblarge.o: climblarge.cpp methods.h
	g++ -c climblarge.cpp -O3 -o climblarge.o -std=c++11

climbn.o: climbn.cpp methods.h
	g++ -c climbn.cpp -O3 -o climbn.o -std=c++11

methods.o: methods.cpp 
	g++ -c methods.cpp -O3 -o methods.o -std=c++11

parser.o: parser.cpp
	g++ -c parser.cpp -O3 -o parser.o -std=c++11

clean:
	rm -rf *.o *~ program