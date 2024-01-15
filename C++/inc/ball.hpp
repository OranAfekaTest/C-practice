#ifndef BALL_HPP
#define BALL_HPP

#include "pawn.hpp"

class Ball : public Pawn
{
public:
    Ball(float a_speed, float a_radius, sf::Vector2f a_start_pos, sf::RenderWindow& a_window);
    ~Ball() = default;

    Ball(Ball const& a_other);
    Ball& operator=(Ball const& a_other);

    Ball(Ball&& a_other);
    Ball& operator=(Ball&& a_other);

    void update(float a_delta_time) override;
    sf::Vector2f get_half_size() const override;
    void on_collision(Pawn const& a_other) override;

    void reset(sf::Vector2f a_paddle_pos);
    void launch();
    bool lost() const;

private:
    sf::Vector2f m_velocity;
    float m_speed;
    bool m_lose = false;
};

#endif // BALL_HPP
