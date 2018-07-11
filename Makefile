code : main.cpp
	g++ -o code main.cpp Memory.cpp predict.cpp -O2 -std=c++14

clean :
	rm -rf code
