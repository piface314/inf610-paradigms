TARGET := structures
CC := g++
CCFLAGS := -O2 -Wall -g -std=c++17
LDFLAGS := -Wall -lpthread -lm -ldl -lz -rdynamic
PARADIGMS := brute-force exhaustive-search backtracking divide-conquer dynamic-programming
OBJS := $(addprefix obj/,$(addsuffix .o,$(PARADIGMS)))

.PHONY: all clean

all: obj bin bin/$(TARGET)

obj:
	mkdir -p obj

bin:
	mkdir -p bin

bin/$(TARGET): obj/main.o obj/utils.o $(OBJS)
	$(CC) -o bin/$(TARGET) obj/main.o obj/utils.o $(OBJS) $(LDFLAGS)

obj/main.o: src/main.cpp src/*.hpp
	$(CC) -c $(CCFLAGS) src/main.cpp -o obj/main.o

.SECONDEXPANSION:
obj/%.o: src/$$*.cpp src/$$*.hpp src/utils.hpp src/data.hpp
	$(CC) -c $(CCFLAGS) src/$*.cpp -o obj/$*.o

obj/utils.o: src/utils.cpp src/utils.hpp
	$(CC) -c $(CCFLAGS) src/utils.cpp -o obj/utils.o

clean:
	rm -vf obj/* bin/*
