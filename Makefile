CMD = main
DIR = src
LDIR = src/p02_data
LIB_A = ch05_list
LIB_B = ch08_chtable
LF = -lm # library flag for math.h
INC = -I include/p02_data

bin/main: bin/main.o bin/$(LIB_A).o bin/$(LIB_B).o
	gcc -o $@ $^ $(LF) 

bin/main.o: $(DIR)/$(CMD).c
	gcc -o $@ $(INC) -c $^ 

bin/$(LIB_A).o: $(LDIR)/$(LIB_A).c
	gcc -o $@ $(INC) -c $^

bin/$(LIB_B).o: $(LDIR)/$(LIB_B).c
	gcc -o $@ $(INC) -c $^

clean:
	rm bin/*
