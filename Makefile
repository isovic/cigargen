all: cigar

cigar: cigargen_main.o cigargen.o
	g++ cigargen_main.o cigargen.o -o cigargen

cigargen_main.o: cigargen_main.cc
	g++ -c cigargen_main.cc

cigargen.o: cigargen.cc
	g++ -c cigargen.cc

clean:
	rm -rf *o cigargen
