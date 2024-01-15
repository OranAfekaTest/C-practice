#include "ball.hpp"
#include "utilities.hpp" // operator<< for Vector2f

#include <SFML/Graphics.hpp>
#include <iostream> // cout

using namespace utils;

#include "game.hpp"


Ball::Ball(float a_speed, float a_radius, sf::Vector2f a_start_pos, sf::RenderWindow& a_window)
: Pawn{new sf::CircleShape(a_radius), a_window}
, m_velocity{0, 0}
, m_speed{a_speed}
{
    m_shape->setOrigin(get_half_size());
    m_shape->setFillColor(sf::Color::Green);
    m_shape->setPosition(a_start_pos.x, a_start_pos.y - 1 - 2 * a_radius);
}

void Ball::reset(sf::Vector2f a_paddle_pos)
{
    m_shape->setPosition(a_paddle_pos.x, a_paddle_pos.y - 1 - 2 * get_half_size().y);
    m_lose = false;
}

Ball::Ball(Ball const& a_other)
: Pawn(new sf::CircleShape(15), a_other.m_window)
, m_velocity{a_other.m_velocity}
, m_speed{a_other.m_speed}
{
    m_shape->setOrigin(get_half_size());
    m_shape->setFillColor(sf::Color::Green);
    m_shape->setPosition(a_other.m_shape->getPosition());
}

Ball& Ball::operator=(Ball const& a_other)
{
    if(this != &a_other)
    {
        m_shape = new sf::CircleShape(15);
        m_velocity = a_other.m_velocity;
        m_speed = a_other.m_speed;

        m_shape->setOrigin(get_half_size());
        m_shape->setFillColor(sf::Color::Green);
        m_shape->setPosition(a_other.m_shape->getPosition());
    }

    return *this;
}

Ball::Ball(Ball&& a_other)
: Pawn(a_other.m_shape, a_other.m_window)
, m_velocity{a_other.m_velocity}
, m_speed{a_other.m_speed}
{
    a_other.m_shape = nullptr;
    a_other.m_velocity = {0 , 0};
    a_other.m_speed = 0;
}

Ball& Ball::operator=(Ball&& a_other)
{
    if(this != &a_other)
    {
        m_shape = a_other.m_shape;
        m_velocity = a_other.m_velocity;
        m_speed = a_other.m_speed;

        a_other.m_shape = nullptr;
        a_other.m_velocity = {0 , 0};
        a_other.m_speed = 0;
    }

    return *this;
}

void Ball::launch()
{
    if(m_velocity.x == 0 and m_velocity.y == 0)
        {
            m_velocity.x = 0.3;
            m_velocity.y = -1;
        }
}

bool Ball::lost() const
{
    return m_lose;
}

void Ball::update(float a_delta_time)
{
    if(m_shape->getPosition().x - get_half_size().x < 0 or m_shape->getPosition().x + get_half_size().x > m_window.getSize().x)
    {
        m_velocity.x *= -1;
    }
    if(m_shape->getPosition().y - get_half_size().y < 0)
    {
        m_velocity.y *= -1;
    }
    if(m_shape->getPosition().y > m_window.getSize().y)
    {
        m_lose = true;
    }
    m_shape->move(m_velocity * m_speed * a_delta_time);
}

sf::Vector2f Ball::get_half_size() const
{
    float rad = ((sf::CircleShape*)m_shape)->getRadius();

    return sf::Vector2f(rad ,rad);
}

void Ball::on_collision(Pawn const& pawn)
{
    sf::FloatRect boundries = pawn.get_shape().getGlobalBounds();
    // hit top side
    if(m_shape->getPosition().y < boundries.top)
    {
        m_velocity.y *= -1;
    }
    // hit bottom side
    else if(m_shape->getPosition().y > boundries.height)
    {
        m_velocity.y *= -1;
    }
    // hit left side
    else if(m_shape->getPosition().x < boundries.left)
    {
        m_velocity.x *= -1;
    }
    // hit right side
    else if(m_shape->getPosition().x > boundries.width)
    {
        m_velocity.x *= -1;
    }
    // if(m_collisionData.m_delta.x < 0)
    // {
    //     normalize_vector(m_collisionData.m_intersect);
    //     if(m_collisionData.m_delta.y < 0)
    //     {
    //         m_velocity.x *= -1;
    //         m_velocity.y *= -1;
    //     }
    //     else
    //     {
    //         m_velocity.x *= -1;
    //         m_velocity.y *= 1;
    //     }
    // }
    // else
    // {
    //     if(m_collisionData.m_delta.y < 0)
    //     {
    //         m_velocity.x *= 1;
    //         m_velocity.y *= -1;
    //     }
    //     else
    //     {
    //         m_velocity.x *= -1;
    //         m_velocity.y *= -1;
    //     }
    // }
    // std::cout << "current velocity: (" << m_velocity << " intersect: " << m_collisionData.m_intersect << " _delta:" << m_collisionData.m_delta << '\n';
}
