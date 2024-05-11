DEFAULT_TARGET = main
OBJECTS = ../src-gen/assignment3.c ../src-gen/assignment3.h ../src/sc_types.h ./main.c

CFLAGS = -g -Wall -O3 

# -pthread replaces -D_REENTRANT and -lpthreads
# from gcc manual "sets flags for both the preprocessor and linker"
CLFLAGS = -pthread

LDLIBS =
CC = gcc

INC = -I../src-gen -I../src

.PHONY : clean
.PHONY : run

# Generate application
$(DEFAULT_TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(DEFAULT_TARGET) $(CLFLAGS)
	
# Generate object files
%.o: %.c %.h
	$(CC) $(CFLAGS) $(CLFLAGS) $(INC) -c $< -o $@ 

# for  c files without .h
%.o: %.c
	$(CC) $(CFLAGS) $(CLFLAGS) $(INC) -c $< -o $@ 
	
clean:
	rm -f *.o $(DEFAULT_TARGET)

run: $(DEFAULT_TARGET)
	./$(DEFAULT_TARGET)
