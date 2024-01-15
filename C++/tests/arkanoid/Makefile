
TARGET = sfml-app
CC = g++
CXXFLAGS = -pedantic -Wall -Werror -Wextra -g3 -std=c++17
CPPFLAGS = -I$(INCLUDES_DIR)
SFMLFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = masonry.o text_box.o opening_screen.o top_ten.o utilities.o hud.o game.o level.o pawn.o paddle.o brick.o ball.o arkanoid.o

INCLUDES_DIR = ../../inc
SOURCES_DIR = ../../src

$(TARGET): $(OBJS)
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -o $(TARGET) $(OBJS) $(SFMLFLAGS)

masonry.o: $(SOURCES_DIR)/masonry.cpp $(INCLUDES_DIR)/masonry.hpp $(INCLUDES_DIR)/level.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/masonry.cpp  $(CPPFLAGS)

text_box.o: $(SOURCES_DIR)/text_box.cpp $(INCLUDES_DIR)/text_box.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/text_box.cpp  $(CPPFLAGS)

opening_screen.o: $(SOURCES_DIR)/opening_screen.cpp $(INCLUDES_DIR)/opening_screen.hpp $(INCLUDES_DIR)/button.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/opening_screen.cpp  $(CPPFLAGS)

top_ten.o: $(SOURCES_DIR)/top_ten.cpp $(INCLUDES_DIR)/top_ten.hpp $(INCLUDES_DIR)/text_box.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/top_ten.cpp  $(CPPFLAGS)

utilities.o: $(SOURCES_DIR)/utilities.cpp $(INCLUDES_DIR)/utilities.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/utilities.cpp  $(CPPFLAGS)

hud.o: $(SOURCES_DIR)/hud.cpp $(INCLUDES_DIR)/hud.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/hud.cpp  $(CPPFLAGS)

pawn.o: $(SOURCES_DIR)/pawn.cpp $(INCLUDES_DIR)/pawn.hpp $(INCLUDES_DIR)/game.hpp $(INCLUDES_DIR)/utilities.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/pawn.cpp  $(CPPFLAGS)

ball.o: $(SOURCES_DIR)/ball.cpp $(INCLUDES_DIR)/ball.hpp $(INCLUDES_DIR)/pawn.hpp $(INCLUDES_DIR)/utilities.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/ball.cpp  $(CPPFLAGS)

brick.o: $(SOURCES_DIR)/brick.cpp $(INCLUDES_DIR)/brick.hpp $(INCLUDES_DIR)/pawn.hpp $(INCLUDES_DIR)/utilities.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/brick.cpp  $(CPPFLAGS)

paddle.o: $(SOURCES_DIR)/paddle.cpp $(INCLUDES_DIR)/paddle.hpp $(INCLUDES_DIR)/pawn.hpp $(INCLUDES_DIR)/utilities.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/paddle.cpp  $(CPPFLAGS)

level.o: $(SOURCES_DIR)/level.cpp $(INCLUDES_DIR)/level.hpp $(INCLUDES_DIR)/ball.hpp $(INCLUDES_DIR)/brick.hpp $(INCLUDES_DIR)/paddle.hpp $(INCLUDES_DIR)/masonry.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/level.cpp  $(CPPFLAGS)

game.o: $(SOURCES_DIR)/game.cpp $(INCLUDES_DIR)/game.hpp $(INCLUDES_DIR)/level.hpp $(INCLUDES_DIR)/top_ten.hpp $(INCLUDES_DIR)/opening_screen.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/game.cpp  $(CPPFLAGS)

arkanoid.o: $(SOURCES_DIR)/arkanoid.cpp $(INCLUDES_DIR)/game.hpp
	$(CC) $(CXXFLAGS) -c $(SOURCES_DIR)/arkanoid.cpp  $(CPPFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)