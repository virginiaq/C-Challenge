CC= clang
CFLAGS= -Werror -Wno-pragma-pack -I SDL2/include
LDFLAGS= -lSDL2 -L SDL2/lib/x64
BINARY = challenge
BINARY_TESTS = challenge_tests

ifeq ($(OS),Windows_NT)
	BINARY:=$(BINARY).exe
	BINARY_TESTS:=$(BINARY_TESTS).exe
endif

challenge.exe: main.o
	$(CC) $(LDFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@  $^

tests.o: tests.challenge
	$(CC) $(CFLAGS) -c -o $@  $^
	$(CPPCHECK) $^

tests.exe: tests.o main.o
	$(CC) -o $(BINARY_TESTS) $(LDFLAGS) $^
	./$(BINARY_TESTS)
