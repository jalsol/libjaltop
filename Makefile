CC=g++
CFLAGS=-std=c++20 -Wall -Wextra -g -O2 -Iinclude

all:
	$(CC) $(CFLAGS) -o build/libjaltop.so -fPIC -shared src/cpu.cpp src/ram.cpp
	$(CC) $(CFLAGS) -o build/main examples/main.cpp -Lbuild -ljaltop

run:
	LD_LIBRARY_PATH=./build ./build/main

clean:
	rm build/*.so
