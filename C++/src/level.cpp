#include "level.hpp"
#include "ball.hpp"
#include "paddle.hpp"
#include "brick.hpp"
#include "utilities.hpp"

#include <unistd.h> //sleep

Level::Level(sf::RenderWindow& a_window, float a_ball_speed, float a_ball_size, float a_paddle_speed, sf::Vector2f a_paddle_start_pos, sf::Font const& a_font)
: m_window{a_window}
, m_paddle{a_paddle_speed, a_paddle_start_pos, a_window}
, m_ball{a_ball_speed, a_ball_size, a_paddle_start_pos, a_window}
, m_hud{a_window, a_font, 32}
{
}

Level::~Level()
{
}

void Level::begin_play()
{
    //m_timer_clock.restart();
    m_ball.launch();
    m_started = true;
}

void Level::pause_play()
{
    m_paused = true;
}

void Level::continue_play()
{
    m_paused = false;
}

bool Level::completed()
{
    if(m_bricks.empty())
    {
        m_win = true;
        m_hud.write_to_screen("You Win!", sf::Color::Green);
        sleep(2);
        m_ball.reset(m_paddle.get_shape().getPosition());
        m_started = false;
        return true;
    }
    if(m_ball.lost())
    {
        if(--m_lives == 0)
        {
            m_win = false;
            m_hud.write_to_screen("Game Over!!", sf::Color::Red);
            sleep(5);
            return true;
        }
        m_started = false;
        m_ball.reset(m_paddle.get_shape().getPosition());
    }
    return false;
}

bool Level::win()
{
    return m_win;
}

// void Level::render()
// {
//     play();
// }

utils::Score Level::play()
{
    float delta_time = 0;
    sf::Clock clock;
    m_timer_clock.restart();

    while(not completed())
    {
        delta_time = clock.restart().asSeconds();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        
        while (m_window.pollEvent(event))
        {
            if(event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    return m_score;
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                {
                    if(not m_started)
                    {
                        // launch ball
                        begin_play();
                    }
                    else if(m_paused)
                    {
                        continue_play();
                    }
                    else
                    {
                        pause_play();
                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::X))
                {
                    for(Brick& b : m_bricks)
                    {
                        b.kill();
                    }
                }
            }

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                m_window.close();
        }
        
        // check for collisions
        for(Brick& b : m_bricks)
        {
            m_ball.collision(b);
        }
        m_ball.collision(m_paddle);

        // update pawns
        for(Brick& b : m_bricks)
        {
            b.update(delta_time);
            if(b.exploded())
            {
                m_score.m_points += b.worth();
                m_score.m_time = m_timer_clock.getElapsedTime().asMilliseconds();
            }
        }
        auto it = std::remove_if(m_bricks.begin(), m_bricks.end(), [](Brick& b){
            return b.exploded();
        });
        m_bricks.erase(it, m_bricks.end());
        
        if(m_started and not m_paused)
        {
            m_ball.update(delta_time);
            m_paddle.update(delta_time);
        }
        m_hud.update(m_timer_clock.getElapsedTime().asSeconds(), m_score.m_points, m_lives);

        // clear the window with dark green color
        m_window.clear(sf::Color(0, 30, 0));

        // draw everything here...
        for(Brick& b : m_bricks)
        {
            if(not b.exploded())
            {
                b.draw();
            }
        }
        m_ball.draw();
        m_paddle.draw();
        m_hud.draw();
        if(m_paused)
        {
            m_hud.write_to_screen("paused", sf::Color::Black);
        }

        // end the current frame
        m_window.display();
    }
    return m_score;
}
