CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror
CFLAGS+= -Wextra
CFLAGS+= -pedantic -g

CXXFLAGS = $(CFLAGS)
CXXFLAGS += -std=c++17

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

# flags for preprocessor
CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

OBJECTS = utest.o
TARGET = utest

all: $(TARGET)

$(TARGET) : $(OBJECTS)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) $(TARGET) $(OBJECTS)

.PHONY: make clean check all

# dependencies
utest.o: $(INCLUDES_DIR)/smart_ptr.hpp
