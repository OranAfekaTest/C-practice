#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "pawn.hpp"

class Paddle : public Pawn
{
public:
    Paddle(float a_speed, sf::Vector2f a_start_pos, sf::RenderWindow& a_window);
    ~Paddle() = default;

    void update(float a_delta_time) override;
    sf::Vector2f get_half_size() const override;
    void on_collision(Pawn const& a_other) override;

private:
    float m_speed;
};

#endif // PADDLE_HPP