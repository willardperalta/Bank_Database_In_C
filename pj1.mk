pj1: pj1.o db.o
	gcc pj1.o db.o -o pj1

pj1.o: pj1.c
	gcc -ansi -pedantic-errors -Wall -c pj1.c

db.o: db.c db.h
	gcc -ansi -pedantic-errors -Wall -c db.c

clean:
	rm *.o pj1
