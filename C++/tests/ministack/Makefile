CXX= g++
CC = $(CXX)

CXXFLAGS  = -pedantic -Wall -Werror -Wextra
CXXFLAGS += -g3
CXXFLAGS += -std=c++17

CPPFLAGS = -DDEBUG
CPPFLAGS = -I$(INCLUDES_DIR)

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

OBJS = utest.o $(SOURCES_DIR)/minimum_stack.o
TARGET = utest

all: $(TARGET)

$(TARGET) : $(OBJS)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

clean:
	@$(RM) ./$(TARGET) $(OBJS)

$(SOURCES_DIR)/minimum_stack.o : $(INCLUDES_DIR)/minimum_stack.hpp
utest.o : $(INCLUDES_DIR)/minimum_stack.hpp $(INCLUDES_DIR)/mu_test.h

.PHONY : make clean check

make:
	@echo 'Attend a maker faire next year! now back to coding...'
	@${TRUE}
