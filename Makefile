CC=gcc
FLAGS= -Wall -g

all: frequency

frequency:  trie.o
	 $(CC) $(FLAGS) -o frequency trie.o

trie.o: trie.c 
	 $(CC) $(FLAGS) -c trie.c 
	 
clean:
	 rm -f *.o frequency

.PHONY: all clean