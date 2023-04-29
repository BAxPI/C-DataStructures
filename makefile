# Compilation macros
CC = gcc
CFLAGS = -Wall -pedantic -g -lm# Flags
EXE_DEPS = DLList_test.o DLList.o stack.o
# Executable 
tester: $(EXE_DEPS)
	$(CC) -g $(EXE_DEPS) $(CFLAGS) -o $@

DLList_test.o: ./tests/DLList_test.c
	$(CC) -c ./tests/DLList_test.c $(CFLAGS) -o $@
DLList.o: DLList.c
	$(CC) -c DLList.c $(CFLAGS) -o $@

stack.o: stack.c
	$(CC) -c stack.c $(CFLAGS) -o $@



make clean:
	rm -f *.o
