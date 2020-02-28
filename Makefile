all: libgol.so gameoflife.o
	gcc -o gameoflife ./libgol.so gameoflife.o -Wall -Wextra -pedantic -std=c11

gol.o: gol.c
	gcc -fPIC -c gol.c -o gol.o -Wall -Wextra -pedantic -std=c11 

gameoflife.o: gameoflife.c
	gcc -c gameoflife.c -o gameoflife.o -Wall -Wextra -pedantic -std=c11

libgol.so: gol.o
	gcc -shared gol.o -o libgol.so -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf *.o gameoflife libgol.so