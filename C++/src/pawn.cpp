#include "pawn.hpp"

#include <iostream> // cout

#include "game.hpp"

Pawn::Pawn(sf::Shape* a_shape, sf::RenderWindow& a_window)
: m_shape{a_shape}
, m_window{a_window}
{
}

Pawn::~Pawn()
{
    delete m_shape;
}

sf::Shape& Pawn::get_shape() const
{
    return *m_shape;
}

void Pawn::draw()
{
    m_window.draw(*m_shape);
}

bool Pawn::collision(Pawn& a_other)
{
    if(&a_other != this)
    {

        float deltaX = a_other.m_shape->getPosition().x - m_shape->getPosition().x;
        float deltaY = a_other.m_shape->getPosition().y - m_shape->getPosition().y;

        float intersectX = abs(deltaX) - (a_other.get_half_size().x + get_half_size().x);
        float intersectY = abs(deltaY) - (a_other.get_half_size().y + get_half_size().y);

        if(intersectX < 0 and intersectY < 0)
        {
            // std::cout << "delta: (" << deltaX << " ," << deltaY << ") intersect: (" << intersectX << ", " << intersectY << ')' << '\n';
            // on_collision(sf::Vector2f(deltaX, deltaY), sf::Vector2f(intersectX, intersectY));
            // m_collisionData.m_delta = {deltaX, deltaY};
            // m_collisionData.m_intersect = {intersectX, intersectY};


			on_collision(a_other);
            a_other.on_collision(*this);
            // m_collisionData.m_delta = {0 , 0};
            // m_collisionData.m_intersect = {0 , 0};
            return true;
        }
    }

    return false;
}
