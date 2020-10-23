# Compile under Linux desktop
CC = gcc
CXX = g++
INC = ./
INC_PARAMS=$(INC:%=-I%) 
INC_PARAMS=$(INC:%=-I%) $(shell pkg-config --cflags Qt5Core Qt5Widgets Qt5Gui)
CXXFLAGS += -c -std=c++11 -Wall -O2 -fPIC
CFLAGS += -c -Wall -O2
LDLIBS = $(shell pkg-config --libs Qt5Core Qt5Widgets Qt5Gui)

BASE_OBJECTS 	=			pacmanwindow.o \
							jeu.o \
							main.o

TARGET 	=			main

.PHONY: all all_
all_: $(TARGET) ; $(info Compiling with ${CXX})

all:
	make -j $(shell grep -c "^processor" /proc/cpuinfo) all_

$(TARGET): $(TARGET).o $(BASE_OBJECTS)
	$(CXX) $^ -Llib -o $(TARGET) $(LDLIBS)


%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INC_PARAMS) $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INC_PARAMS) $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET).o $(TARGET)
	rm -f $(BASE_OBJECTS)

run: all;
	./$(TARGET)