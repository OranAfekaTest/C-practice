#include "Round.h"
#include "UI.h"
#define CARDS_TO_DEAL 13
#define CARDS_TO_GIFT 3
#define PASS_LEFT 0
#define PASS_RIGHT 1
#define PASS_INFRONT 2
#define PASS_NONE 3

struct Round
{
    Deck* m_deck;
    size_t m_roundNum;
};

typedef struct TrickContext
{
    Card* m_table[PLAYERS_IN_GAME];
    Suit m_trickSuit;
    size_t m_leadPlayerIndex;
    int m_isHeartBroken;
    int m_isPreGift;
    int m_firstTrick;
    int m_hasSuitInHand;
}TrickContext;

static Status DealCards(Deck* _deck, Vector* _players);
static Status PreGift(Round* _round, Vector* _players, TrickContext* _tCon);
static void Trick(Vector* _players, TrickContext* _tCon);
static size_t HighestRankIndex(Vector* _cards, int* _legalIndexes, size_t _legalIndexesSize);
static Status DeterminTrick(TrickContext* _tCon, Vector* _players);
static void InitTrick(TrickContext* _tCon, Vector* _players);
static void EndTrick(Round* _round, Vector* _players, TrickContext* _tCon);

Round* CreateRound(void)
{
    Round* round = malloc(sizeof(Round));
    if(!round)
    {
        return NULL;
    }
    round->m_deck = CreateDeck();
    if(!round->m_deck)
    {
        free(round);
        return NULL;
    }
    round->m_roundNum = 0;
    return round;
}

void DestroyRound(Round** _round)
{
    if(*_round)
    {
        DestroyDeck(&((*_round)->m_deck));
        free(*_round);
        *_round = NULL;
    }
}

Status StartRound(Round* _round, Vector* _players)
{
    Status status;
    size_t trickIndex;
    TrickContext* tCon = malloc(sizeof(TrickContext));
    if(!_round || !_players)
    {
        return NOT_INITIALIZED;
    }
    StatusHandler(ShuffleDeck(_round->m_deck, CARDS_TO_GIFT), "from ShuffleDeck at StartRound");
    PrintRoundStart(_round->m_roundNum);
    status = DealCards(_round->m_deck, _players);
    if(status != OK)
    {
        StatusHandler(status, "from DealCards at StartRound");
        return status;
    }

    InitTrick(tCon, _players);
    VectorForEach(_players, SortHand, NULL);
    VectorForEach(_players, PrintAllHands, NULL);

    if(_round->m_roundNum % 4 != PASS_NONE)
    {
        PreGiftStage();
        PreGift(_round, _players, tCon);
        VectorForEach(_players, SortHand, NULL);
        VectorForEach(_players, PrintAllHands, NULL);
    }
    tCon->m_isPreGift = FALSE;
    
    for(trickIndex = 0; trickIndex < CARDS_TO_DEAL; trickIndex++)
    {
        PrintTrickNumber(trickIndex);
        Trick(_players, tCon);
        StatusHandler(DeterminTrick(tCon, _players), "from DeterminTrick at Trick, lead suit doesn't match lead card");
        EndTrick(_round, _players, tCon);
        VectorForEach(_players, PrintAllHands, NULL);
    }

    PrintScores(_players);
    _round->m_roundNum++;
    free(tCon);
    return OK;
}

void EndTrick(Round* _round, Vector* _players, TrickContext* _tCon)
{
    Card* card = NULL;
    size_t i;
    Player* leadPlayer = NULL;
    VectorGet(_players, _tCon->m_leadPlayerIndex, (void**)&leadPlayer);
    for(i = 0; i < PLAYERS_IN_GAME; i++)
    {
        card = _tCon->m_table[i];
        if(GetCardSuit(card) == HEARTS)
        {
            StatusHandler(AddPoints(leadPlayer, 1), "at adding heart points to lead player");
        }
        if(GetCardSuit(card) == SPADES && GetCardRank(card) == DAMMA)
        {
            StatusHandler(AddPoints(leadPlayer, 13), "at adding damma of spades points to lead player");
        }
        StatusHandler(ReturnCardToDeck(_round->m_deck, card), "from ReturnCardToDeck at EndTrick");
        _tCon->m_table[i]= NULL;
    }
    _tCon->m_firstTrick = FALSE;
}

void Trick(Vector* _players, TrickContext* _tCon)
{
    size_t i, playerIndex;
    Player* player = NULL;
    Card* cardToPlay = NULL;
    
    for(i = 0; i < PLAYERS_IN_GAME; i++)
    {
        playerIndex = (i + _tCon->m_leadPlayerIndex) % PLAYERS_IN_GAME;
        HandleVectorResult(VectorGet(_players, playerIndex, (void**)&player));
        _tCon->m_hasSuitInHand = PlayerHasSuitInHand(player, _tCon->m_trickSuit);
        if(PlayerOnlyHasHeartsInHand(player))
        {
            _tCon->m_isHeartBroken = TRUE;
        }
        /*printf("Player No.%ld %s %s suit in hand\n", playerIndex + 1, _tCon->m_hasSuitInHand?"has":"has'nt", SuitNames[_tCon->m_trickSuit]);*/
        StatusHandler(PlayCard(player, &cardToPlay, Strategy, Rules, _tCon), "from PlayCard at Trick");
        if( i == 0 )
        {
            _tCon->m_trickSuit = GetCardSuit(cardToPlay);
        }
        _tCon->m_table[playerIndex] = cardToPlay;
        if(GetCardSuit(cardToPlay) == HEARTS)
        {
            _tCon->m_isHeartBroken = TRUE;
        }
        CardPlay(player, cardToPlay);
    }
}

void InitTrick(TrickContext* _tCon, Vector* _players)
{
    size_t i;
    for(i = 0; i < PLAYERS_IN_GAME; i++)
    {
        _tCon->m_table[i] = NULL;
    }
    _tCon->m_isPreGift = TRUE;
    _tCon->m_isHeartBroken = FALSE;
    _tCon->m_firstTrick = TRUE;
    _tCon->m_trickSuit = SPADES;
    _tCon->m_hasSuitInHand = TRUE;
    _tCon->m_leadPlayerIndex = VectorForEach(_players, WhoHasTwoOfSpades, NULL);
}

Status DeterminTrick(TrickContext* _tCon, Vector* _players)
{
    size_t i;
    Card* leadCard = NULL;
    Player* leadPlayer = NULL;
    for(i = 0; i < PLAYERS_IN_GAME; i++)
    {
        if(GetCardSuit(_tCon->m_table[i]) == _tCon->m_trickSuit && (!leadCard || GetCardRank(leadCard) < GetCardRank(_tCon->m_table[i])))
        {
            leadCard = _tCon->m_table[i];
            _tCon->m_leadPlayerIndex = i;
        }
    }
    HandleVectorResult(VectorGet(_players, _tCon->m_leadPlayerIndex, (void*)&leadPlayer));
    TrickDetermination(leadPlayer, leadCard);
    return OK;
}

size_t HighestRankIndex(Vector* _cards, int* _legalIndexes, size_t _legalIndexesSize)
{
    size_t i, result = _legalIndexes[0];
    Card* bestCard = NULL, *cmpCard = NULL;
    HandleVectorResult(VectorGet(_cards, _legalIndexes[result], (void**)&bestCard));
        for(i = 1; i < _legalIndexesSize; i++)
        {
            HandleVectorResult(VectorGet(_cards, _legalIndexes[i], (void**)&cmpCard));
            if(GetCardRank(bestCard) < GetCardRank(cmpCard))
            {
                bestCard = cmpCard;
                result = _legalIndexes[i];
            }
        }
    return result;
}

Card* Strategy(Vector* _cards, int* _legalIndexes, size_t _legalIndexesSize, void* _tCon)
{
    Card* card = NULL;
    size_t bestIndex;
    if(((TrickContext*)_tCon)->m_isPreGift)
    {
        bestIndex = HighestRankIndex(_cards, _legalIndexes, _legalIndexesSize);
        HandleVectorResult(VectorRemoveByIndex(_cards, bestIndex, (void**)&card));
        return card;
        /*VectorGetByCriteria(_cards, GetHighestRank, _best);*/
    }
    if(((TrickContext*)_tCon)->m_firstTrick)
    {
        bestIndex = 0; /* will be two of spades*/
        VectorRemoveByIndex(_cards, _legalIndexes[bestIndex], (void**)&card);
        return card;
    }
    /* temporary strategy just to get things going */
    bestIndex = HighestRankIndex(_cards, _legalIndexes, _legalIndexesSize);
    HandleVectorResult(VectorRemoveByIndex(_cards, bestIndex, (void**)&card));

    return card;
}

int Rules(Card* _card, void* _tCon)
{
    TrickContext* tCon = _tCon;
    if(!_card || !_tCon)
    {
        return FALSE;
    }
    if(tCon->m_isPreGift)/* all cards are legl in pregift */
    {
        return TRUE;
    }
    if(tCon->m_firstTrick && !tCon->m_table[tCon->m_leadPlayerIndex])/* first card of first round */
    {
        if(GetCardRank(_card) == TWO && GetCardSuit(_card) == SPADES)/* has to b3 2 of spades*/
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    if(!tCon->m_table[tCon->m_leadPlayerIndex])/* first card of in-game trick */
    {
        if(GetCardSuit(_card) == HEARTS && !tCon->m_isHeartBroken)/* can't be a heart if hearts havn't been broken yet*/
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    if(GetCardSuit(_card) == tCon->m_trickSuit) /* card has to be from same suit as the lead card */
    {
        return TRUE;
    }
    else if(!tCon->m_hasSuitInHand)
    {
        return TRUE;
    }
    return FALSE;
}

Status PreGift(Round* _round, Vector* _players, TrickContext* _tCon)
{
    Card* GiftHolder[PLAYERS_IN_GAME][CARDS_TO_GIFT];
    Status status;
    Player* player = NULL;
    Card* card = NULL;
    size_t i, j, getFrom;

    for(i = 0; i < PLAYERS_IN_GAME; i++)
    {
        HandleVectorResult(VectorGet(_players, i, (void**)&player));
        if(!player)
        {
            return NOT_INITIALIZED;
        }
        for(j = 0; j < CARDS_TO_GIFT; j++)
        {
            status = PlayCard(player, &card, Strategy, Rules, (void*)_tCon);
            if(status != OK)
            {
                return status;
            }
            PrintHand(player);
            GiftHolder[i][j] = card;
        }
    }
    
    for(i = 0; i < PLAYERS_IN_GAME; i++)
    {
        HandleVectorResult(VectorGet(_players, i, (void**)&player));
        switch (_round->m_roundNum % 4)
        {
        case PASS_LEFT:
            getFrom = (i == 0 ? PLAYERS_IN_GAME - 1 : i - 1);
            break;

        case PASS_RIGHT:
            getFrom = (i + 1) % PLAYERS_IN_GAME;
            break;

        case PASS_INFRONT:
            getFrom = (i + 2) % PLAYERS_IN_GAME;
            break;
    
        case PASS_NONE:
            /* pass none */
            break;

        default:
            break;
        }
        for(j = 0; j < CARDS_TO_GIFT; j++)
        {
            printf("adding %s to hand from player No.%ld to player No.%ld\n", GetCardName(GiftHolder[getFrom][j]), getFrom, i);
            status = AddCardToHand(player, GiftHolder[getFrom][j]);
            if(status != OK)
            {
                 return status;
            }
        }
    }
    return OK;
}

Status DealCards(Deck* _deck, Vector* _players)
{
    size_t result, i;
    for(i = 0; i < CARDS_TO_DEAL; i++)
    {
        result = VectorForEach(_players, TakeCardFromDeck, _deck);
    }
    if(result != PLAYERS_IN_GAME)
    {
        return GENERAL;
    }
    return OK;
}

size_t GetNumOfPlayers(Round* _round)
{
    if(!_round)
    {
        return 0;
    }
    return PLAYERS_IN_GAME;
}