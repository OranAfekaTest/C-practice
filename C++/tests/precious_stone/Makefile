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

OBJECTS = $(SOURCES_DIR)/scytale.o $(SOURCES_DIR)/lisper.o $(SOURCES_DIR)/rot13.o $(SOURCES_DIR)/caesar_encryption.o $(SOURCES_DIR)/leet_code.o $(SOURCES_DIR)/astrix_replacer.o $(SOURCES_DIR)/translator.o $(SOURCES_DIR)/uppercase.o $(SOURCES_DIR)/message.o $(SOURCES_DIR)/text_message.o utest.o
OBJECTS += $(SOURCES_DIR)/stream_source.o $(SOURCES_DIR)/console_source.o $(SOURCES_DIR)/stream_destination.o $(SOURCES_DIR)/console_destination.o $(SOURCES_DIR)/precious_stone.o
TARGET = utest

all: $(TARGET)

$(TARGET) : $(OBJECTS)

check : $(TARGET)
	@./$(TARGET) -v

recheck: clean check

valgrind: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

clean:
	@$(RM) $(TARGET) $(OBJECTS)

.PHONY: make clean check all

# dependencies

# messages
$(SOURCES_DIR)/message.o : $(INCLUDES_DIR)/message.hpp
$(SOURCES_DIR)/text_message.o : $(INCLUDES_DIR)/text_message.hpp $(INCLUDES_DIR)/message.hpp
$(SOURCES_DIR)/stream_destination.o : $(INCLUDES_DIR)/stream_destination.hpp $(INCLUDES_DIR)/message_destination.hpp
$(SOURCES_DIR)/console_destination.o : $(INCLUDES_DIR)/console_destination.hpp $(INCLUDES_DIR)/stream_destination.hpp
$(SOURCES_DIR)/stream_source.o : $(INCLUDES_DIR)/stream_source.hpp $(INCLUDES_DIR)/message_source.hpp
$(SOURCES_DIR)/console_source.o : $(INCLUDES_DIR)/console_source.hpp $(INCLUDES_DIR)/stream_source.hpp
$(SOURCES_DIR)/precious_stone.o : $(INCLUDES_DIR)/message_destination.hpp $(INCLUDES_DIR)/message_source.hpp $(INCLUDES_DIR)/encoder.hpp

# encoders
$(SOURCES_DIR)/translator.o : $(INCLUDES_DIR)/translator.hpp $(INCLUDES_DIR)/message.hpp
$(SOURCES_DIR)/astrix_replacer.o : $(INCLUDES_DIR)/translator.hpp $(INCLUDES_DIR)/astrix_replacer.hpp
$(SOURCES_DIR)/leet_code.o : $(INCLUDES_DIR)/leet_code.hpp $(INCLUDES_DIR)/translator.hpp
$(SOURCES_DIR)/uppercase.o : $(INCLUDES_DIR)/uppercase.hpp $(INCLUDES_DIR)/message.hpp $(INCLUDES_DIR)/encoder.hpp
$(SOURCES_DIR)/caesar_encryption.o : $(INCLUDES_DIR)/caesar_encryption.hpp $(INCLUDES_DIR)/message.hpp $(INCLUDES_DIR)/encoder.hpp
$(SOURCES_DIR)/rot13.o : $(INCLUDES_DIR)/rot13.hpp $(INCLUDES_DIR)/caesar_encryption.hpp $(INCLUDES_DIR)/message.hpp $(INCLUDES_DIR)/encoder.hpp
$(SOURCES_DIR)/lisper.o : $(INCLUDES_DIR)/lisper.hpp $(INCLUDES_DIR)/message.hpp $(INCLUDES_DIR)/encoder.hpp
$(SOURCES_DIR)/scytale.o : $(INCLUDES_DIR)/scytale.hpp $(INCLUDES_DIR)/lisper.hpp $(INCLUDES_DIR)/message.hpp $(INCLUDES_DIR)/encoder.hpp

# target
utest.o: $(INCLUDES_DIR)/console_source.hpp $(INCLUDES_DIR)/console_destination.hpp $(INCLUDES_DIR)/precious_stone.hpp $(INCLUDES_DIR)/scytale.hpp $(INCLUDES_DIR)/lisper.hpp $(INCLUDES_DIR)/rot13.hpp $(INCLUDES_DIR)/text_message.hpp $(INCLUDES_DIR)/uppercase.hpp $(INCLUDES_DIR)/astrix_replacer.hpp $(INCLUDES_DIR)/leet_code.hpp $(INCLUDES_DIR)/caesar_encryption.hpp $(INCLUDES_DIR)/mu_test.h
