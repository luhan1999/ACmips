code : main.cpp
	g++ -o code Command.cpp main.cpp Memory.cpp parser.cpp predict.cpp process.cpp scanner.cpp -O2 -std=c++14

clean :
	rm -rf code
