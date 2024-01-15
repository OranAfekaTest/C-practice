#include "game.hpp"

int main()
{
    const unsigned WIDTH = 800;
    const unsigned HIGHT = 600;
    Game game{WIDTH, HIGHT};
    game.start();
    return 0;
}
