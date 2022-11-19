CC = gcc # compiler
CFLAGS = -Wall -Werror -Wmissing-prototypes # compiler flags
OBJS = main.o classfile.o # object files

# make all
all: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS)

# make main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# make REPL.o
classfile.o: ReadFile/classfile.c
	$(CC) $(CFLAGS) -c ReadFile/classfile.c

# make clean
clean:
	rm -f *.o

# rebuild
.PHONY: rebuild
rebuild:
	$(MAKE) all
	$(MAKE) clean