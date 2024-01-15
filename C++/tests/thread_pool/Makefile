CXX = g++
CC = $(CXX)

CFLAGS = -Wall -Werror -g3
CFLAGS+= -Wextra
CFLAGS+= -pedantic

LDLIBS = -pthread

SOURCE_PATH= ../../src
INLCUDE_PATH= ../../inc

CXXFLAGS = $(CFLAGS) 
CXXFLAGS += -std=c++17 -I$(INLCUDE_PATH)

# flags for preprocessor
CPPFLAGS =

OBJECTS = utest.o $(SOURCE_PATH)/thread_pool.o
TARGET = utest

all: $(TARGET)

check : $(TARGET)
	@./$(TARGET) -v

utest : $(OBJECTS)

hell: $(TARGET)
	valgrind --tool=helgrind -s ./$(TARGET) 2> hell.log

valgrind: $(TARGET)
	valgrind --leak-check=full ./utest

clean:
	@$(RM) utest $(OBJECTS)

.PHONY: clean all


# dependencies
$(SOURCE_PATH)/thread_pool.o : $(INLCUDE_PATH)/blocking_queue.hpp
utest.o: $(INLCUDE_PATH)/mu_test.h $(INLCUDE_PATH)/thread_pool.hpp