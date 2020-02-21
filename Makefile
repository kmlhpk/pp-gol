output: gol.o gameoflife.o
	gcc gol.o gameoflife.o -o gameoflife -Wall -Wextra -pedantic -std=c11

gol.o: gol.c
	gcc -c gol.c -Wall -Wextra -pedantic -std=c11

gameoflife.o: gameoflife.c
	gcc -c gameoflife.c -Wall -Wextra -pedantic -std=c11

clean:
	rm -rf *.o gameoflife