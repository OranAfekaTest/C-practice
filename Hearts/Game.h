#ifndef __GAME_H__
#define __GAME_H__
#include "Round.h"
#include "Player.h"
#include "Status.h"
#include "MyVector.h"

typedef struct Game Game;

Game* CreateGame(int _numOfPlayers);
void DestroyGame(Game** _game);
Status RunGame(Game* _game);


#endif /* __GAME_H__ */