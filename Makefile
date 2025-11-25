guesser: main.o guesser.o tree.o
	$(CC) -o $@ $^

test: test.o tree.o guesser.o
	$(CC) -o $@ $^

clean:
	rm *.o guesser test

%.o: %.c
	$(CC) -c -o $@ $^

