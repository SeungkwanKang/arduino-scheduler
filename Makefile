CC := g++
CFLAGS := -DDEBUG
CFLAGS_MAIN := -O2
CFLAGS_DEBUG := -O0 -g

LIB_FILES := scheduler.o
TEST_FILE := test/main.cpp

.PHONY: all
all: main debug

%.o: src/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(TEST_FILE) $(LIB_FILES)
	$(CC) $(CFLAGS) $(CFLAGS_MAIN) -o $@ $^

debug: $(TEST_FILE) $(LIB_FILES)
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -o $@ $^

.PHONY: clean
clean:
	rm main debug *.o