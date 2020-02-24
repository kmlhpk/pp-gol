output: libgol.so gameoflife.o
	gcc libgol.so gameoflife.o -o gameoflife -Wall -Wextra -pedantic -std=c11

libgol.so: gol.o
	gcc -c gol.c -Wall -Wextra -pedantic -std=c11 -shared

gol.o: gol.c
	gcc -c gol.c -Wall -Wextra -pedantic -std=c11 -fPIC

gameoflife.o: gameoflife.c
	gcc -c gameoflife.c -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf *.o gameoflife