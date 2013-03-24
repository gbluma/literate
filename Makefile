
build:
	gcc -o literate literate.c  

build_strict:
	gcc -Wall -pedantic -std=iso9899:1999 -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wstrict-prototypes -Wmissing-prototypes -Wconversion -o literate literate.c  

test:
	$(MAKE) build_strict
	valgrind ./literate -s example.lc
	valgrind ./literate -d example.lc

run:
	./literate -s example.lc > example.c
	./literate -d example.lc > example.md
