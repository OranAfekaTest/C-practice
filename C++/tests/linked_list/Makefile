CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o
TARGET = utest

all: $(TARGET)

$(TARGET) : $(OBJS)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) ./$(TARGET) $(OBJS)

utest.o : $(INCLUDES_DIR)/linked_list.hpp $(INCLUDES_DIR)/mu_test.h

valgrind: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

.PHONY : make clean check valgrind

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}
