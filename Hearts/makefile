# Hearts game makefile 

TARGET= hearts.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= MyVector.o Status.o Card.o Deck.o Player.o UI.o Round.o Game.o HeartsMain.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
	
MyVector.o: MyVector.c MyVector.h
	$(CC) $(CFLAGS) -c MyVector.c

Status.o: Status.c Status.h
	$(CC) $(CFLAGS) -c Status.c

Card.o: Card.c Card.h
	$(CC) $(CFLAGS) -c Card.c

Deck.o: Deck.c Deck.h Card.h Status.h MyVector.h
	$(CC) $(CFLAGS) -c Deck.c

Player.o: Player.c Player.h Card.h MyVector.h
	$(CC) $(CFLAGS) -c Player.c

UI.o: UI.c UI.h Player.h Card.h
	$(CC) $(CFLAGS) -c UI.c

Round.o: Round.c Round.h Deck.h Card.h Status.h Player.h UI.h
	$(CC) $(CFLAGS) -c Round.c

Game.o: Game.c Game.h Round.h Player.h Status.h MyVector.h UI.h
	$(CC) $(CFLAGS) -c Game.c

HeartsMain.o: HeartsMain.c Game.h
	$(CC) $(CFLAGS) -c HeartsMain.c
	
clean:
	rm -f $(TARGET) $(OBJS)
