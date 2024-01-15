#ifndef BUTTON_FUNCTIONS
#define BUTTON_FUNCTIONS

#include <SFML/Graphics.hpp> // sf::RenderWindow

class PlayFunction
{
public:
    void operator()(sf::RenderWindow& a_window)
    {
        (void)a_window;
    }
};

class QuitFunction
{
public:
    void operator()(sf::RenderWindow& a_window)
    {
        a_window.close();
    }
};

#endif // BUTTON_FUNCTIONS