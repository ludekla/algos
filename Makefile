
here:
	gcc -o bin/rec.o -I include -c src/ch03_recursion.c
	gcc -o bin/main.o -I include -c src/main.c
	gcc -o bin/main bin/*.o
