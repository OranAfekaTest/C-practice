#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

template<typename Action>
class Button
{
public:
    Button(sf::RenderWindow& a_window, sf::Vector2f a_pos, std::string const& a_text, sf::Font const& a_font, sf::Texture& a_texture);
    ~Button();

    void draw();
    bool update(); // returns true if cilcked

private:
    sf::RenderWindow& m_window;
    sf::Vector2f m_pos;
    sf::Sprite m_body;
    sf::Color m_original_color;
    sf::Text m_text;
    Action m_action;
};

#include "inl/button.hxx"

#endif // BUTTON_HPP
