CC=g++
CFLAGS=--std=c++23 -g
LDFLAGS=

.PHONY: clean

all: bin

bin: build/deut.o build/lexer.o build/parser.o build/token.o
	$(CC) -o deut $^ $(CFLAGS) $(LDFLAGS)

build/deut.o: src/deut.cpp
	@mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

build/lexer.o: src/lexer.cpp src/lexer.h
	@mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

build/parser.o: src/parser.cpp src/parser.h
	@mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

build/token.o: src/token.cpp src/token.h
	@mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	@rm -R build/
