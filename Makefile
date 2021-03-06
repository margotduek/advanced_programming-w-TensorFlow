# Simple example of a Makefile

### Variables for this project ###
# These should be the only ones that need to be modified
# The files that must be compiled, with a .o extension
#OBJECTS = slot.o
# The header files
#DEPENDS = 
# The executable programs to be created
MAIN = index
### Variables for the compilation rules ###
# These should work for most projects, but can be modified when necessary
# The compiler program to use
CC = gcc
# Options to use when compiling object files
# NOTE the use of gnu99, because otherwise the socket structures are not included
#  http://stackoverflow.com/questions/12024703/why-cant-getaddrinfo-be-found-when-compiling-with-gcc-and-std-c99
CFLAGS = -Wall -g -std=gnu99 -pedantic # -O2
# Options to use for the final linking process
# This one links the math library
LDFLAGS = -lpthread
MPFLAGS = -fopenmp 

### The rules ###
# These should work for most projects without change

# Default rule
all: $(MAIN)

# Rule to make the client program
$(MAIN): $(MAIN).o $(OBJECTS)
	$(CC) $^ -o $@ $(LDFLAGS) #$(MPFLAGS)

# Rule to make the object files
%.o: %.c $(DEPENDS)
	$(CC) $< -c -o $@ $(CFLAGS)

# Clear the compiled files
clean:
	rm -rf *.o $(MAIN) $(CLIENT) $(SERVER)
	
# Indicate the rules that do not refer to a file
.PHONY: clean all
