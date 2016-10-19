project: grepfn.o
	cc grepfn.o -o project
grepfn.o: grepfn.c
	cc -Wall -c grepfn.c
clean: 
	rm *.o
