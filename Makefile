all: libgol.so gameoflife.o
	gcc -Wall -Wextra -pedantic -std=c11 -o gameoflife ./libgol.so gameoflife.o

gol.o: gol.c
	gcc -fPIC -c gol.c -o gol.o -Wall -Wextra -pedantic -std=c11 

gameoflife.o: gameoflife.c
	gcc -Wall -Wextra -pedantic -std=c11 -c gameoflife.c -o gameoflife.o

libgol.so: gol.o
	gcc gol.o -Wall -Wextra -pedantic -std=c11 -shared -o libgol.so

clean:
	rm -rf *.o gameoflife libgol.so