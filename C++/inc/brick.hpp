#ifndef BRICK_HPP
#define BRICK_HPP

#include "pawn.hpp"

class Brick : public Pawn
{
public:
    Brick(sf::RenderWindow& a_window, sf::Vector2f a_size, sf::Vector2f a_pos, sf::Color a_color, uint8_t a_lives = 1);
    ~Brick() = default;

    Brick(Brick const& a_other);
    Brick& operator=(Brick const& a_other);

    Brick(Brick&& a_other);
    Brick& operator=(Brick&& a_other);

    void update(float a_delta_time) override;
    sf::Vector2f get_half_size() const override;
    void on_collision(Pawn const& a_other) override;

    int worth();
    bool exploded();

    void kill() // X cheat
    {
        m_exploded = true;
    }

private:
    int m_worth = 40;
    bool m_exploded = false;
    uint8_t m_lives;
};



#endif // BRICK_HPP
