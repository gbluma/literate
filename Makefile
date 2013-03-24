
build:
	gcc -Wall -pedantic -std=iso9899:1999 -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion -o literate literate.c  

test:
	$(MAKE) build
	valgrind ./literate -s example.lc
	valgrind ./literate -d example.lc

run:
	./literate -s example.lc
