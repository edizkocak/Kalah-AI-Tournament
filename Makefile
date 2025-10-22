.PHONY: all
all: kalah

kalah: kalah.cpp kalah.hpp minmax.hpp alphabeta.hpp heuristics.hpp
	g++ -std=c++17 -o kalah kalah.cpp -pthread

.PHONY: run
run: kalah
	python3 cppkgp.py

.PHONY: test
test: kalah
	./kalah "<8,32,31,0,3,0,0,2,17,1,1,1,18,1,19,1,0,1,0>"

.PHONY: clean
clean:
	rm kalah