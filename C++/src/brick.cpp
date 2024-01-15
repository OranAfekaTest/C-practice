#include "brick.hpp"
#include "utilities.hpp"

#include <SFML/Graphics.hpp>

Brick::Brick(sf::RenderWindow& a_window, sf::Vector2f a_size, sf::Vector2f a_pos, sf::Color a_color, uint8_t a_lives)
: Pawn{new sf::RectangleShape(a_size), a_window}
, m_lives{a_lives}
{
    m_shape->setOrigin(get_half_size());
    m_shape->setFillColor(a_color);
    m_shape->setPosition(a_pos);
}

sf::Vector2f Brick::get_half_size() const
{
    float x = ((sf::RectangleShape*)m_shape)->getSize().x / 2;
    float y = ((sf::RectangleShape*)m_shape)->getSize().y / 2;

    return sf::Vector2f(x ,y);
}

Brick::Brick(Brick const& a_other)
: Pawn(a_other.m_shape, a_other.m_window)
, m_worth{a_other.m_worth}
, m_exploded(a_other.m_exploded)
, m_lives{a_other.m_lives}
{}
    
Brick& Brick::operator=(Brick const& a_other)
{
    if(this != &a_other)
    {
        m_shape = a_other.m_shape;
        m_worth = a_other.m_worth;
        m_exploded = a_other.m_exploded;
        m_lives = a_other.m_lives;
    }

    return *this;
}

Brick::Brick(Brick&& a_other)
: Pawn(a_other.m_shape, a_other.m_window)
, m_worth{a_other.m_worth}
, m_lives{a_other.m_lives}
{
    a_other.m_exploded = true;
    a_other.m_shape = nullptr;
    a_other.m_worth = 0;
    a_other.m_lives = 0;
}

Brick& Brick::operator=(Brick&& a_other)
{
    if(this != &a_other)
    {
        m_shape = a_other.m_shape;
        m_worth = a_other.m_worth;
        m_exploded = a_other.m_exploded;
        m_lives = a_other.m_lives;

        a_other.m_exploded = true;
        a_other.m_shape = nullptr;
        a_other.m_worth = 0;
        a_other.m_lives = 0;
    }

    return *this;
}

void Brick::on_collision(Pawn const& a_other)
{
    (void)a_other;
    if(m_lives > 0)
    {
        --m_lives;
    }
}

int Brick::worth()
{
    return m_worth;
}

bool Brick::exploded()
{
    return m_exploded;
}

void Brick::update(float a_delta_time)
{
    (void)a_delta_time;
    if(m_lives == 0)
    {
        m_exploded = true;
    }
}

