CMD = ch03_main
DIR = cmd
LIB = ch03_recursion
INC = -I include

bin/main: bin/main.o bin/$(LIB).o
	gcc -o $@ $^

bin/main.o: $(DIR)/$(CMD).c
	gcc -o $@ $(INC) -c $^

bin/$(LIB).o: src/$(LIB).c
	gcc -o $@ $(INC) -c $^

clean:
	rm bin/*
