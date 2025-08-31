test: list.o test.c
	cc -o test src/test.c src/list.o -lcunit

list.o: list.c
	cc -o src/list.o -c src/list.c
