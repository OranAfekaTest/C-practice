#include "UI.h"
#include <stdio.h>
#define NAMESIZE 16

struct UI
{
    Player* m_user;
    Card* m_cardToPlay;
};

int PrintScore(void* _player, size_t _index, void* _context);

UI* ActivateUI(Player* _player)
{
    UI* this = malloc(sizeof(UI));
    if(!this)
    {
        return NULL;
    }
    this->m_user = _player;
    return this;
}

char* InsertPlayerName(size_t _num)
{
    char* input = malloc(NAMESIZE);
    printf("Insert a name for player No.%ld, 15 characters MAX\n", _num + 1);
    scanf("%s", input);
    return input;
}

int InsertIsHuman(void)
{
    int input;
    puts("Enter 1 for human player, 0 for computer");
    scanf("%d", &input);
    return input;
}

int ChooseCard(void)
{
    int input;
    puts("Choose a legal card to play");
    scanf("%d", &input);
    return input - 1;
}

void AnounceWinner(Player* _winner)
{
    printf("The winner is %s\n", GetPlayerName(_winner));
}

void TrickDetermination(Player* _leadPlayer, Card* _leadCard)
{
    printf("\n%s took the table with %s\n\n", GetPlayerName(_leadPlayer), GetCardName(_leadCard));
}
    
void CardPlay(Player* _player, Card* _card)
{
    printf("%s played the %s\n", GetPlayerName(_player), GetCardName(_card));
}

int PrintCard(void* _card, size_t _index, void* _context)
{
    printf("%ld) %s \n", _index + 1, GetCardName((Card*) _card));
    return 1;
}

void PrintScores(Vector* _players)
{
    VectorForEach(_players, PrintScore, NULL);
}

int PrintScore(void* _player, size_t _index, void* _context)
{
    if(!_player)
    {
        return 0;
    }
    printf("%s score:%d\n", GetPlayerName((Player*)_player), GetPlayerScore((Player*)_player));
    return 1;
}

void PreGiftStage(void)
{
    puts("Choose 3 cards to gift");
}
        
void PrintTrickNumber(size_t _num)
{
    printf("Trick No.%ld\n", _num + 1);
}

void PrintRoundStart(size_t _num)
{
    printf("Starting round %ld\n", _num + 1);
}
