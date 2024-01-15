#include "border.hpp"

Border::Border(sf::Vector2f a_start_pos, sf::Vector2f a_size, sf::RenderWindow& a_window)
: Pawn(new sf::RectangleShape(a_size), a_window)
{
    m_shape->setOrigin(get_half_size());
    m_shape->setPosition(a_start_pos);
}

sf::Vector2f Border::get_half_size() const
{
    float x = ((sf::RectangleShape*)m_shape)->getSize().x / 2;
    float y = ((sf::RectangleShape*)m_shape)->getSize().y / 2;

    return sf::Vector2f(x ,y);
}

void Border::on_collision(sf::FloatRect const& a_boundries)
{
    (void)a_boundries;
}

void Border::update(float a_delta_time)
{
    (void)a_delta_time;
}
