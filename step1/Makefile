CC = gcc
all: main
clean: 
	rm -f *.o main
%.o: %.c
	$(CC) -c $< 
main: main.o
	$(CC)  $^ -o $@
