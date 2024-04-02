output: src/mypython.o
	g++ -std=c++11 src/*.o -o mypython

mypython.o: src/mypython.cpp
	g++ -std=c++11 -c src/*.cpp

clean:
	rm src/*.o mypython