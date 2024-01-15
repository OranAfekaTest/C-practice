#ifndef PAWN_HPP
#define PAWN_HPP


#include <SFML/Graphics.hpp>

struct CollisionData
{
    sf::Vector2f m_delta;
    sf::Vector2f m_intersect;
};

class Pawn
{
public:
    virtual ~Pawn();
    Pawn(sf::Shape* a_shape, sf::RenderWindow& m_window);

    virtual void draw();
    virtual bool collision(Pawn& a_other);
    virtual void on_collision(Pawn const& a_other) = 0;
    virtual void update(float a_delta_time) = 0;

    virtual sf::Vector2f get_half_size() const = 0;
    sf::Shape& get_shape() const;

protected:
    sf::Shape* m_shape;
    CollisionData m_collisionData;
    sf::RenderWindow& m_window;
};


#endif // PAWN_HPP
