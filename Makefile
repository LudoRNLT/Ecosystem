CC=g++

all: Ecosystem

Ecosystem: main.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f Ecosystem