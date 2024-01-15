#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "brick.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "hud.hpp"
#include "utilities.hpp"
#include "masonry.hpp"
#include "state_machine.hpp"

#include <SFML/Graphics.hpp> // all sf::thingies
#include <vector>

class Level/* : public State*/
{
    friend class Masonry;

public:
    Level(sf::RenderWindow& a_window, float a_ball_speed, float a_ball_size, float a_paddle_speed, sf::Vector2f a_paddle_start_pos, sf::Font const& a_font);
    ~Level();

    bool win();
    // void render() override;
    utils::Score play();

private:
    void begin_play();
    void pause_play();
    void continue_play();
    bool completed();

private:
    sf::RenderWindow& m_window;
    std::vector<Brick> m_bricks;
    Paddle m_paddle;
    Ball m_ball;
    HUD m_hud;
    sf::Clock m_timer_clock;
    uint8_t m_lives = 3;
    utils::Score m_score;
    bool m_started = false;
    bool m_paused = false;
    bool m_win;
};

#endif // LEVEL_HPP