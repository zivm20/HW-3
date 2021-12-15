CC=gcc
FLAGS=-Wall -g
OBJECTS_MAIN=main.o
LIB_OBJECTS=stringFunctions.o
LIB_so=stringFunctions.so


all: $(LIB_so) stringProg


#create main program

stringProg: $(OBJECTS_MAIN) $(LIB_so)
	$(CC) $(FLAGS) -o stringProg $(OBJECTS_MAIN) ./$(LIB_so) -lm



#clean
clean:
	rm *.o *.so stringProg

.PHONY: clean all


#compile dependencies
%.so: %.o
	$(CC) -shared -o $@ $<

%.a: %.o
	ar -rcs -o $@ $<

#compile objects
stringFunctions.o: stringFunctions.h stringFunctions.c
	$(CC) $(FLAGS) -c stringFunctions.c


main.o: main.c stringFunctions.h
	$(CC) $(FLAGS) -c main.c
