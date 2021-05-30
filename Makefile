CC := g++
CFLAGS := -DDEBUG -O0 -g
CCC := avr-gcc
CCFLAGS := -Wall -Os -g -mmcu=atmega328p -I/usr/lib/avr/include

LIB_FILES := scheduler.o
TEST_FILE := test/main.cpp

LIB_FILES_MAIN := $(addprefix ./build/main/,$(LIB_FILES))
LIB_FILES_DEBUG := $(addprefix ./build/debug/,$(LIB_FILES))

.PHONY: all flash compile
all: main debug
flash: all
compile: ./build/main/main.hex debug

./build/main/%.o: src/%.cpp
	mkdir -p build/main
	$(CCC) $(CCFLAGS) -c -o $@ $<

./build/debug/%.o: src/%.cpp
	mkdir -p build/debug
	$(CC) $(CFLAGS) -c -o $@ $<

./build/main/main.bin: $(TEST_FILE) $(LIB_FILES_MAIN)
	$(CCC) $(CCFLAGS) -o ./build/main/main.bin $^

debug: $(TEST_FILE) $(LIB_FILES_DEBUG)
	$(CC) $(CFLAGS) -o ./build/debug/debug.bin $^

./build/main/main.hex: ./build/main/main.bin
	avr-objcopy -j .text -j .data -O ihex $< $@

main: ./build/main/main.hex
	avrdude -p atmega328p -c arduino -P COM1 -U flash:w:$<:i

.PHONY: clean
clean:
	rm -rf build