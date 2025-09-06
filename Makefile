test: src/list.o
	cc -o test src/test.c list.o -lcunit -g

src/list.o: src/list.c
	cc -o list.o -c src/list.c -g
