#comment
TARGET=SimpleDebugging
#COMMAND=g++
COMMAND=gcc
#FLAGS= -g3 -ansi -pedantic  -Wall -Werror -std=c++03
FLAGS= -g3 -ansi -pedantic  -Wall -Werror -std=c99
$(TARGET): $(TARGET).c
	@echo Compiling $(TARGET)
#	gcc  -g3 -ansi -pedantic  -Wall -Werror -std=c99 -o SimpleDebugging SimpleDebugging.c
	$(COMMAND)  $(FLAGS) -o $(TARGET) $(TARGET).c
clean:
	rm $(TARGET) 
