
TARGET= example
CC= g++
CXXFLAGS= -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = sfml-app -lsfml-graphics -lsfml-window -lsfml-system
OBJS= example.o

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(CPPFLAGS)

example.o: example.cpp
	$(CC) $(CXXFLAGS) -c example.cpp

clean:
	rm -f $(TARGET) $(OBJS)
