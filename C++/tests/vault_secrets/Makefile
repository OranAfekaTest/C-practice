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
#$(SOURCES_DIR)/file_parser.o: $(INCLUDES_DIR)/file_parser.hpp $(INCLUDES_DIR)/singleton.hpp
utest.o: $(INCLUDES_DIR)/file_parser.hpp $(INCLUDES_DIR)/vault_secrets.hpp $(INCLUDES_DIR)/singleton.hpp
