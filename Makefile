CMD = main
DIR = src
LIB_A = ch05_list
LIB_B = ch07_set
INC = -I include

bin/main: bin/main.o bin/$(LIB_A).o bin/$(LIB_B).o
	gcc -o $@ $^

bin/main.o: $(DIR)/$(CMD).c
	gcc -o $@ $(INC) -c $^

bin/$(LIB_A).o: src/$(LIB_A).c
	gcc -o $@ $(INC) -c $^

bin/$(LIB_B).o: src/$(LIB_B).c
	gcc -o $@ $(INC) -c $^

clean:
	rm bin/*
