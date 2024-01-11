#include "Game.h"
#include "UI.h"


struct Game
{
    Round* m_round;
    Vector* m_players;
};

static const int GOAL_SCORE = 100;
static size_t WinCondition(Game* _game);

Game* CreateGame(int _numOfPlayers)
{
    Game* game = malloc(sizeof(Game));
    if(!game)
    {
        return NULL;
    }
    game->m_players = VectorCreate(_numOfPlayers, 0);
    game->m_round = CreateRound();
    return game;
}

void DestroyGame(Game** _game)
{
    if(*_game)
    {
        VectorDestroy(&((*_game)->m_players), DestroyPlayer);
        DestroyRound(&((*_game)->m_round));
        free(*_game);
        *_game = NULL;
    }
}

size_t WinCondition(Game* _game)
{
    size_t winnerIndex;
    if(!_game)
    {
        puts("NULL game pointer at WinCondition");
        return -1;
    }
    return winnerIndex = VectorForEach(_game->m_players, CheckForWinner, (void*)&GOAL_SCORE);
}

Status InitializePlayers(Game* _game)
{
    size_t i, size = VectorCapacity(_game->m_players);
    char* name = NULL;
    int isHuman;
    for(i = 0; i < size; i++)
    {
        name = InsertPlayerName(i);
        isHuman = InsertIsHuman();
        HandleVectorResult(VectorAppend(_game->m_players, (void*)CreatePlayer(isHuman, name)));
        free(name);
    }
    
    return OK;
}

Status RunGame(Game* _game)
{
    Status status;
    size_t winnerIndex = GetNumOfPlayers(_game->m_round);
    Player* winner = NULL;
    puts("Running game");
    InitializePlayers(_game);
    while(GetNumOfPlayers(_game->m_round) <= winnerIndex)
    {  
        status = StartRound(_game->m_round, _game->m_players);
        if(status != OK)
        {
            StatusHandler(status, "from StartRound at RunGame");
            return status;
        }
        winnerIndex = WinCondition(_game);
    }
    /* the actual winner XD not the loser's index*/
    winnerIndex = VectorGetByCriteria(_game->m_players, WinComparator, (void**)&winner);
    AnounceWinner(winner);
    return OK;
}