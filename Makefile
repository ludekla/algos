LIB = ch05_list
INC = -I include

bin/main: bin/main.o bin/$(LIB).o
	gcc -o $@ $^

bin/main.o: src/main.c
	gcc -o $@ $(INC) -c $^

bin/$(LIB).o: src/$(LIB).c
	gcc -o $@ $(INC) -c $^
