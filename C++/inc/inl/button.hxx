#ifndef BUTTON_HXX
#define BUTTON_HXX

#include "button.hpp"

#include <iostream>

template<typename Action>
Button<Action>::Button(sf::RenderWindow &a_window, sf::Vector2f a_pos, std::string const &a_text, sf::Font const &a_font, sf::Texture &a_texture)
: m_window{a_window}
, m_body{a_texture}
, m_text{a_text, a_font}
{
    m_body.setOrigin(m_body.getGlobalBounds().width / 2, m_body.getGlobalBounds().height / 2);
    m_body.setPosition(a_pos);
    m_body.setScale(0.3, 0.3);
    m_original_color = m_body.getColor();

    m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
    m_text.setPosition(m_body.getPosition().x, m_body.getPosition().y - 10);
    m_text.setFillColor(sf::Color::Magenta);
    m_text.setOutlineColor(sf::Color::White);
    m_text.setOutlineThickness(3);
}

template<typename Action>
bool Button<Action>::update()
{
    if (m_body.getGlobalBounds().contains((sf::Vector2f)sf::Mouse::getPosition(m_window)))
    {
        m_body.setColor({200, 200, 200});
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            m_action(m_window);
            return true;
        }
    }
    else
    {
        m_body.setColor(m_original_color);
    }
    return false;
}

template<typename Action>
Button<Action>::~Button()
{
}

template<typename Action>
void Button<Action>::draw()
{
    m_window.draw(m_body);
    m_window.draw(m_text);
}

#endif // BUTTON_HXX