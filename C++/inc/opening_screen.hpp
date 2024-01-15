#ifndef OPENING_SCREEN_HPP
#define OPENING_SCREEN_HPP

#include "button.hpp"
#include "button_functions.hpp"
#include "state_machine.hpp"

#include <SFML/Graphics.hpp> // all sf::thingies

class OpeningScreen/* : State*/
{
public:
    OpeningScreen(sf::RenderWindow& a_window, sf::Texture& a_bg_image, sf::Texture& a_button_texture, sf::Font const& a_font, float a_button_offset);
    ~OpeningScreen();

    void render();

private:
    sf::RenderWindow& m_window;
    sf::RectangleShape m_background;
    sf::Text m_logo;
    Button<PlayFunction> m_play_button;
    Button<QuitFunction> m_quit_button;
    bool m_button_clicked = false;
};

#endif // OPENING_SCREEN_HPP
