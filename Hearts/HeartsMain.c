#include "Game.h"

int main(void)
{
    Game* game = CreateGame(PLAYERS_IN_GAME);
    RunGame(game);
    DestroyGame(&game);

    return 0;
}