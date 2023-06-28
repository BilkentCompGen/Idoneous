all: build run_test

build:
	g++ -std=c++2a main.cpp factorize.cpp coord.cpp bitpack.cpp comparison.cpp minimizer.cpp swa.cpp edlib/src/edlib.cpp -o fact -I edlib/include -g

run_test:
	./fact ../data/new/c22_38.fasta ../data/new/c22_t2.fasta 200000 2 3 200 30 10

clean:
	rm -f fact
