#include "paddle.hpp"

#include "game.hpp"

Paddle::Paddle(float a_speed, sf::Vector2f a_start_pos, sf::RenderWindow& a_window)
: Pawn(new sf::RectangleShape(sf::Vector2f(80, 20)), a_window)
, m_speed{a_speed}
{
    m_shape->setOrigin(get_half_size());
    m_shape->setFillColor(sf::Color::Blue);
    m_shape->setPosition(a_start_pos);
}

sf::Vector2f Paddle::get_half_size() const
{
    float x = ((sf::RectangleShape*)m_shape)->getSize().x / 2;
    float y = ((sf::RectangleShape*)m_shape)->getSize().y / 2;

    return sf::Vector2f(x ,y);
}

void Paddle::on_collision(Pawn const& a_other)
{
    (void)a_other;
}

void Paddle::update(float a_delta_time)
{
    float movement = 0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        if(m_shape->getPosition().x + get_half_size().x < m_window.getSize().x)
        {
            movement += m_speed * a_delta_time;
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        if(m_shape->getPosition().x - get_half_size().x > 0)
        {
            movement -= m_speed * a_delta_time;
        }
    }

    m_shape->move(movement, 0);

}
