#ifndef BOREDER_HPP
#define BOREDER_HPP

#include "pawn.hpp"

#include <iostream>

class Border : public Pawn
{
public:
    Border(sf::Vector2f a_start_pos, sf::Vector2f a_size, sf::RenderWindow& a_window);
    ~Border() = default;

    void update(float a_delta_time) override;
    sf::Vector2f get_half_size() const override;
    void on_collision(sf::FloatRect const& a_boundries) override;
};

#endif // BOREDER_HPP
