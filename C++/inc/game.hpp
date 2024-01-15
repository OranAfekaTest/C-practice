#ifndef GAME_HPP
#define GAME_HPP

#include "pawn.hpp"
#include "utilities.hpp" // Score

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game(const unsigned a_width, const unsigned a_hight);
    ~Game();

    sf::RenderWindow& window();
    std::vector<Pawn*>& pawns();
    
    void start();

private:
    void load_resources();

private:
    sf::RenderWindow m_window;
    utils::Score m_score;
    sf::Font m_font;
    sf::Texture m_bg_image;
    sf::Texture m_button_texture;

};

#endif // GAME_HPP