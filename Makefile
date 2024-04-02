output: src/mypython.o src/interpreter.o src/token.o src/scanner.o src/enum.o
	g++ -std=c++11 src/*.o -o mypython

mypython.o: src/mypython.cpp src/interpreter.cpp src/token.cpp src/scanner.cpp src/enum.cpp
	g++ -std=c++11 -c src/*.cpp

clean:
	rm src/*.o mypython