mypython: src/*.cpp
	g++ -std=c++17 src/*.cpp -o mypython

clean:
	rm src/*.o mypython