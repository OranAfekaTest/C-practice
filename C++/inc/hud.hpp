#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp> // all sf::thingies

class HUD
{
public:
    HUD(sf::RenderWindow& a_window, sf::Font const& a_font, unsigned int a_text_size);
    ~HUD();

    void draw();
    void update(float a_delta_time, int a_points, uint8_t a_lives);
    void write_to_screen(std::string const& a_text ,sf::Color const& a_color);

private:
    sf::RenderWindow& m_window;
    sf::RectangleShape m_sheet;
    sf::Text m_score;
    sf::Text m_timer;
    sf::Text m_lives;
};

#endif // HUD_HPP